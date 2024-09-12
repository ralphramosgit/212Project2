project_debug: llist.o user_interface.o
	g++ -o project_debug llist.o user_interface.o

llist.o: llist.cpp llist.h
	g++ -ansi -pedantic-errors -Wall -c -D DEBUGMODE llist.cpp

user_interface.o: user_interface.cpp
	g++ -ansi -pedantic-errors -Wall -c -D DEBUGMODE user_interface.cpp

clean:
	rm -f project_debug llist.o user_interface.o
