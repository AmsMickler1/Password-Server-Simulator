C11= -std=c++11 -Wall -pedantic

proj5.x: proj5.o passserver.o
	g++ $(C11) -o $@ proj5.o passserver.o -lcrypt

proj5.o: proj5.cpp passserver.h hashtable.h hashtable.hpp
	g++ $(C11) -c $<

passserver.o: passserver.cpp passserver.h
	g++ $(C11) -c $<

clean:
	rm -f *.o proj5.x
