SRCFILES := $(shell find . -mindepth 1 -maxdepth 3 -name "*.c")
HDRFILES := $(shell find . -mindepth 1 -maxdepth 3 -name "*.h")
OBJFILES := $(patsubst %.c,%.o,$(SRCFILES))
DEPFILES := $(patsubst %.c,%.d,$(SRCFILES))

.PHONY: all clean rebuild

CFLAGS += -Wall -Wextra -Werror -g

all: 12magic

12magic: $(OBJFILES)
	$(CC) $(CFLAGS) -o 12magic $(OBJFILES)

clean:
	-rm 12magic *.o *.d

rebuild: clean all

-include $(DEPFILES)

%.o: %.c Makefile
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@
