CC			= gcc
CFLAGS	= -W -Wall
TARGET	= test

all : $(TARGET)

$(TARGET) : test.o linked_list.o
	$(CC) $(CFLAGS) -o $@ $^

test.o : test.c
	$(CC) $(CFLAGS) -c -o $@ $^

linked_list.o : linked_list.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean :
	rm -rf *.o test 
