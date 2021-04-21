it: compile

compile: main.o
	@g++ -g -O0 -Wall build/main.o -o bin/iaspie

main.o: src/main.cpp
	@g++ -g -O0 -Wall -c src/main.cpp -o build/main.o

clean:
	@rm build/*.o bin/iaspie
