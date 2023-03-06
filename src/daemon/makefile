CC=gcc
CFLAGS=-I./includes
DEPS=daemon.h auth.h
OBJ=main.o daemon.o auth.o
RM=rm
EXECNAME=noted
# rm don't work on Windows
ifeq ($(OS), Windows_NT)
	RM=del
endif


all: $(EXECNAME) clean

# Rule that define each .o file needs to compile .c and DEPS files first
# $@ means to put the output into the file named on the left of the :
# $< means first item on DEPS, making all .c files being recompiled if that DEP was modified
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# $@ means output go to file named in left of the :
# $^ means output go to file named in right of the :
$(EXECNAME): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	$(RM) -f *.o