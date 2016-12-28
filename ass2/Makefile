all: EuclideanVectorTester test1 test2 test3 test4 test5 test6

EuclideanVectorTester: EuclideanVectorTester.o EuclideanVector.o
	g++ -fsanitize=address EuclideanVectorTester.o EuclideanVector.o -o EuclideanVectorTester
test1: test1.o EuclideanVector.o
	g++ -fsanitize=address test1.o EuclideanVector.o -o test1
test2: test2.o EuclideanVector.o
	g++ -fsanitize=address test2.o EuclideanVector.o -o test2
test3: test3.o EuclideanVector.o
	g++ -fsanitize=address test3.o EuclideanVector.o -o test3
test4: test4.o EuclideanVector.o
	g++ -fsanitize=address test4.o EuclideanVector.o -o test4
test5: test5.o EuclideanVector.o
	g++ -fsanitize=address test5.o EuclideanVector.o -o test5
test6: test6.o EuclideanVector.o
	g++ -fsanitize=address test6.o EuclideanVector.o -o test6

EuclideanVectorTester.o: EuclideanVectorTester.cpp EuclideanVector.h
	g++ -std=c++14 -Wall -Werror -O2 -fsanitize=address -c EuclideanVectorTester.cpp

test1.o: test1.cpp util.h
	g++ -std=c++14 -Wall -Werror -O2 -fsanitize=address -c test1.cpp
test2.o: test2.cpp util.h
	g++ -std=c++14 -Wall -Werror -O2 -fsanitize=address -c test2.cpp
test3.o: test3.cpp util.h
	g++ -std=c++14 -Wall -Werror -O2 -fsanitize=address -c test3.cpp
test4.o: test4.cpp util.h
	g++ -std=c++14 -Wall -Werror -O2 -fsanitize=address -c test4.cpp
test5.o: test5.cpp util.h
	g++ -std=c++14 -Wall -Werror -O2 -fsanitize=address -c test5.cpp
test6.o: test5.cpp util.h
	g++ -std=c++14 -Wall -Werror -O2 -fsanitize=address -c test6.cpp

EuclideanVector.o: EuclideanVector.cpp EuclideanVector.h
	g++ -std=c++14 -Wall -Werror -O2 -fsanitize=address -c EuclideanVector.cpp



clean:
	rm *o EuclideanVectorTester