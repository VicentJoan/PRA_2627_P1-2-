bin/testListArray:testListArray.cpp ListArray.h List.h
	mkdir -p bin
	g++ -Wall -g -o bin/testListArray testListArray.cpp

bin/testNode:testNode.cpp Node.h
	mkdir -p bin
	 g++ -o bin/testNode testNode.cpp
clean:
	 rm -rf bin

