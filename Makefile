TARGET = gerenciador
CC = g++
OBJS = main.o processo.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

main.o: main.c processo.h
	$(CC) -c main.c

processo.o: processo.c processo.h
	$(CC) -c processo.c

clean:
	rm -rf $(OBJS) $(TARGET)
