a.out: test.cpp
	g++ -g -Wall -std=c++11 -o a.out test.cpp

clean:
	rm a.out
