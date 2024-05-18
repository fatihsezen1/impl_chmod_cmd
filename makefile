CC = gcc
CFLAGS = -Wall -Wextra -g

SRCS = main.c calc-permissions.c csd_grp.c
OBJS = $(SRCS:.c=.o)
HEADERS = calc-permissions.h csd_grp.h

TARGET = chmod

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)