CC = gcc

CFLAGS = -g -I ./pcb/ -I ./linked_list/ -I ./dispatcher/ -I ./

ifeq ($(DEBUG), 1)
    CFLAGS += -DDEBUG
endif

SRCS = ./main.c pcb/pcb.c linked_list/linked_list.c dispatcher/dispatcher.c
OBJS = $(SRCS:.c=.o)

TARGET = run_me

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean
