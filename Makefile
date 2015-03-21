all: snif.o
	g++ class_sniff.o main.o StatisticAnalysis.o -lpcap -o snif
    
class_sniff.o: class_sniff.c
	g++ class_sniff.c

main.o: main.c
	g++ main.c

StatisticAnalysis.o: StatisticAnalysis.cpp
	g++ StatisticAnalysis.cpp
    
clean:
	rm *.o snif
