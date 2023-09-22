all: scheduler loader

scheduler: ./main.o ./pcb.o ./scheduler.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

loader: ./main.o ./pcb.o ./loader.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

clean: 
	rm -f all ./*.o