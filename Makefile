all: my_find

my_find: my_find.cpp
	g++ -std=c++14 -Wall -Werror -o my_find my_find.cpp

clean:
	rm -f my_find