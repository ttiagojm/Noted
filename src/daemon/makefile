CC=gcc
CFLAGS=-I./includes
DEPS=daemon.h auth.h config.h
OBJ=main.o daemon.o auth.o
OBJTEST=tests/test_main.o daemon.o auth.o
RM=rm
EXECNAME=noted
DELIM=/
# rm and / path delimiter don't work on Windows
ifeq ($(OS), Windows_NT)
	RM=del
	DELIM=$(strip \)
endif


all: $(EXECNAME) clean

# For unit tests
test: make_test clean

# Rule that define each .o file needs to compile .c and DEPS files first
# $@ means to put the output into the file named on the left of the :
# $< means first item on DEPS, making all .c files being recompiled if that DEP was modified
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# $@ means output go to file named in left of the :
# $^ means output go to file named in right of the :
$(EXECNAME): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)


make_test: $(OBJTEST)
	$(CC) -o $@ $^ $(CFLAGS)


.PHONY: clean
clean:
	$(RM) -f *.o tests$(DELIM)*.o