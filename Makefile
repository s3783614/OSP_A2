all:  fifo sjf rr

scheduler: ./main.o ./pcb.o 
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

loader: ./main.o ./pcb.o 
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

clean: 
	rm -f all ./*.o