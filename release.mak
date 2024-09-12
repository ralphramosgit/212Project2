project: llist.o user_interface.o
	g++ -o project llist.o user_interface.o

llist.o: llist.cpp llist.h
	g++ -ansi -pedantic-errors -Wall -c llist.cpp

user_interface.o: user_interface.cpp
	g++ -ansi -pedantic-errors -Wall -c user_interface.cpp

clean:
	rm project user_interface.o llist.o
