main: main.o process.o  analysis.o calculate.o
	g++ -o main main.o process.o analysis.o calculate.o -g

main.o: main.cc 
	g++ -c -o main.o main.cc 
process.o: process.cc 
	g++ -c -o process.o process.cc 
analysis.o: analysis.cc
	g++ -c -o analysis.o analysis.cc
calculate.o: calculate.cc
	g++ -c -o calculate.o calculate.cc
clean: 
	rm *.o main 