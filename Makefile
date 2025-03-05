#Makefile
CC = g++
TARGET = sum-nbo
OBJS = main.o

all: $(TARGET)

$(TARGET): $(OBJS)
	g++ -o sum-nbo main.o

$(OBJS): main.cpp
	$(CC) -c -o main.o main.cpp

clean:
	rm -f $(OBJS)
	rm -f $(TARGET)
