all:  fifo sjf rr

fifo: ./main.o ./pcb.o ./fifo/FIFO.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

sjf: ./main.o ./pcb.o ./sjf/SJF.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

rr: ./main.o ./pcb.o ./rr/RR.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

clean: 
	rm -f all ./fifo/*.o
	rm -f all ./sjf/*.o
	rm -f all ./rr/*.o
	rm -f all ./*.o