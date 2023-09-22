all: fifo sjf rr

fifo: ./main.o ./pcb.o ./scheduler.o ./loader.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

sjf: ./main.o ./pcb.o ./scheduler.o ./loader.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

rr: ./main.o ./pcb.o ./scheduler.o ./loader.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^
	
clean: 
	rm -f all ./*.o
	rm -f ./fifo
	rm -f ./sjf
	rm -f ./rr