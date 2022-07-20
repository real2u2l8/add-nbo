#Makefile
CC = g++
TARGET = add-nbo
OBJS = main.o

all: $(TARGET)

$(TARGET): $(OBJS)
	g++ -o add-nbo main.o

$(OBJS): main.cpp
	$(CC) -c -o main.o main.cpp

clean:
	rm -f $(OBJS)
