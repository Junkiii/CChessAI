CC = gcc
CFLAGS = -O3 -march=native -flto -funroll-loops -finline-functions -fno-strict-aliasing #-save-temps
LDFLAGS = -flto

TARGET = cchess
SRCDIR = .
SRCS = $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/*/*.c)
OBJS = $(SRCS:.c=.o)
ASMS = $(SRCS:.c=.s)
PRES = $(SRCS:.c=.i)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS) $(ASMS) $(PRES)