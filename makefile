CC = g++ -Wall -g

go: main.o BotBrain.o BotBody.o BotOne.o
	$(CC) main.o BotBrain.o BotBody.o BotOne.o -o go

test: tests.o BotBrain.o BotBody.o BotOne.o
	$(CC) tests.o BotBrain.o BotBody.o BotOne.o -o test

cmp: go	
	./go

utest: test
	./test

main.o: main.cpp
	$(CC) -c main.cpp

tests.o: tests.cpp
	$(CC) -c tests.cpp

BotBrain.o: BotBrain.cpp
	$(CC) -c BotBrain.cpp

BotBody.o: BotBody.cpp
	$(CC) -c BotBody.cpp

BotOne.o: BotOne.cpp
	$(CC) -c BotOne.cpp

clean:
	rm *.o go test