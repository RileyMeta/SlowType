CC = gcc
CFLAGS = -Wall -g

TARGET = slowtype
SRCS = main.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

# Link Object files into Executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Compile C source files into Object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(TARGET) $(OBJS)
