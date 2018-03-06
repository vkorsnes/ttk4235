# Which compiler to use
CC = clang-3.8 

# Compiler flags go here.
CFLAGS = -g -Wall

# Linker flags go here.
LDFLAGS = -lcomedi -lm

# list of sources
ELEVSRC = elev.c io.c main.c buttons.c doors.c elevator_controller.c order_system.c

# program executable file name.
TARGET = heis.out

# top-level rule, to compile everything.
all: clean $(TARGET)

# Define all object files.
ELEVOBJ = $(ELEVSRC:.c=.o)

# rule to link the program
$(TARGET): $(ELEVOBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

# Compile: create object files from C source files.
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

# rule for cleaning re-compilable files.
clean:
	rm -f $(TARGET) $(ELEVOBJ)

rebuild:	clean all

.PHONY: all rebuild clean


#Martin Korsgaard, 2006
