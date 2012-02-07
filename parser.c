#include <ctype.h>
#include <stdio.h>
#include "parser.h"

value_t number(const char *word);
int next_word(FILE *fd, char *word, int break_on_newline);

/*
 * ~~ a brief interlude about the parser ~~
 *
 * The parser is passed a file descriptor (which could be a file, stdin,
 * whatever) and a dict corresponding to the current scope. THIS DICT
 * WILL PROBABLY BE MODIFIED. The parser itself doesn't modify it, but it will
 * be given to macros, which may choose to add to it.
 *
 * Here is the parser algorithm:
 * 1. Get the next word. If there is no next word, end.
 * 2. Look up the word in the dictionary.
 *   b. if it's in the dictionary, copy the entry to the output list
 *   c. if it's not in the dictionary, pass it to number().
 *     1. if it's a number, place it in the output list as a literal
 *     2. if it's not a number, print an error and return NULL
 * 3. Go to 1
 *
 * Words have a maximum length of 255 bytes. UTF-8 characters will take more
 * space. Words longer than 255 bytes will be truncated. 
 *
 * Returns a REVERSED program. It has to be passed through the macro processor
 * before it can be run.
 */

cons_t *parse(FILE *fd, dict_t **scope, int break_on_newline) {
	char word[256];
	cons_t *prog = NULL;
	dict_t *entry;
	value_t val;

	while (next_word(fd, word, break_on_newline)) {
		entry = dict_get(*scope, word);
		if (entry != NULL) {
			list_push(&prog, wrap_symbol(entry));
		} else {
			val = number(word);
			if (!null_p(val)) {
				list_push(&prog, val);
			} else {
				*scope = dict_add(*scope, word, null());
				list_push(&prog, wrap_symbol(*scope));
			}
		}
	}

	return prog;
}

int char2digit(char c, int radix) {
	int val = -1;
	if (isdigit(c)) {
		val = c - '0';
	} else if ('a' <= c && c <= 'f') {
		val = 10 + (c - 'a');
	} else if ('A' <= c && c <= 'F') {
		val = 10 + (c - 'A');
	}
	if (val < radix) {
		return val;
	}
	return -1;
}

enum state {
	NUM_ST_BEGIN,  /* no numbers eaten yet */
	NUM_ST_SIGN,   /* sign eaten (further signs invalid) */
	NUM_ST_ZERO,   /* one zero eaten, plus any signs */
	NUM_ST_RADIX,  /* radix set */
	NUM_ST_DIGITS  /* eaten two or more digits. more non-digit chars invalid */
};

/*
 * Tries to parse a word as a number.
 * At the moment it only handles integers.
 *
 * if word is a valid integer, return a numeric value
 * if word is not a valid number, return a null value
 *
 * integer format:
 * [+-]?(0[XxBbDdOo])?[\d]+
 *  radices:
 *    x = hex (digits 0-9, A-F, a-f)
 *    b = binary (valid 0, 1)
 *    d = decimal (valid 0-9)
 *    o = octal (valid 0-7)
 */
value_t number(const char *word) {
	long acc = 0;
	int sign = 1, radix = default_radix, digit;
	unsigned long k = 0;
	char c;
	enum state st = NUM_ST_BEGIN;

	while ((c = word[k++]) != '\0') {
		switch (st) {
			case NUM_ST_BEGIN:
				if (c == '+' || c == '-') {
					sign = c == '-' ? -1 : 1;
					st = NUM_ST_SIGN;
				} else if (c == '0') {
					st = NUM_ST_ZERO;
				} else if ((digit = char2digit(c, radix)) != -1) {
					acc = digit; /* acc was zero */
					st = NUM_ST_DIGITS;
				} else {
					return null();
				}
				break;
			case NUM_ST_SIGN:
				if (c == '0') {
					st = NUM_ST_ZERO;
				} else if ((digit = char2digit(c, radix)) != -1) {
					acc = digit; /* acc was zero */
					st = NUM_ST_DIGITS;
				} else {
					return null();
				}
				break;
			case NUM_ST_ZERO:
				if (c == 'x' || c == 'X') {
					radix = 16;
					st = NUM_ST_RADIX;
				} else if (c == 'b' || c == 'B') {
					radix = 2;
					st = NUM_ST_RADIX;
				} else if (c == 'd' || c == 'D') {
					radix = 10;
					st = NUM_ST_RADIX;
				} else if (c == 'o' || c == 'O') {
					radix = 8;
					st = NUM_ST_RADIX;
				} else if ((digit = char2digit(c, radix)) != -1) {
					acc = digit; /* acc was zero */
					st = NUM_ST_DIGITS;
				} else {
					return null();
				}
				break;
			case NUM_ST_RADIX:
				st = NUM_ST_DIGITS;
			case NUM_ST_DIGITS:
				if ((digit = char2digit(c, radix)) != -1) {
					acc = acc * radix + digit;
				} else {
					return null();
				}
		}
	}

	return wrap_number(sign * acc);
}

int is_end(int c, int break_on_newline) {
	return c == EOF || (break_on_newline && c == '\n');
}

int next_word(FILE *fd, char *word, int break_on_newline) {
	int c, k = 0;
	/* eat up any whitespace */
	while (!is_end(c = fgetc(fd), break_on_newline) && isspace(c)) {
	}
	if (is_end(c, break_on_newline)) {
		return 0; /* no more words :c */
	}
	/* c now contains the first character of the word */
	do {
		word[k++] = c; /* fill in the word */
	} while (k < 255 && !is_end(c = fgetc(fd), break_on_newline) && !isspace(c));
	/*
	 * at this point, if we ran up against the k limit, then c contains the
	 * last character in the word. if we didn't, it contains the first space
	 * after the word.
	 */
	if (!is_end(c, break_on_newline) && !isspace(c)) /* if we ran out of word space */
		while (is_end(c = fgetc(fd), break_on_newline) && !isspace(c)); /* then ignore rest */

	word[k] = '\0'; /* add a terminator */

	if (break_on_newline && c == '\n') {
		ungetc('\n', fd);
	}

	/*
	 * c now contains either EOF or a blank, which we can safely ignore.
	 * if it's an EOF, the next call to this function will return zero
	 * and end the parse loop.
	 */

	return 1; 
}
