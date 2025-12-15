p5 : p5.cpp script.o queue.o stack.o
	g++ p5.cpp script.o queue.o stack.o -std=c++11 -Wall -Werror -g -o p5

script.o : script.h script.cpp queue.o stack.o
	g++ -c script.cpp -std=c++11 -Wall -Werror -g

queue.o : queue.h queue.cpp
	g++ -c queue.cpp -std=c++11 -Wall -Werror -g

stack.o : stack.h stack.cpp
	g++ -c stack.cpp -std=c++11 -Wall -Werror -g

clean:
	rm -f *.exe
	rm -f *.o
	rm -rf launch_base

