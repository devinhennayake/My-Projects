CXX = g++
CXXFLAGS = -Wall -g


proj2: Indexer.o Word.o driver.cpp BinarySearchTree.h 
	$(CXX) $(CXXFLAGS) Indexer.o Word.o BinarySearchTree.h driver.cpp -o proj2

Indexer.o: Word.o Indexer.h Indexer.cpp BinarySearchTree.h
	$(CXX) $(CXXFLAGS) -c Indexer.cpp

Word.o: Word.h Word.cpp
	$(CXX) $(CXXFLAGS) -c Word.cpp

clean:
	rm *~
	rm *.o*
run:
	./proj2 $(FILTER) $(DATA)

val: valgrind ./proj2
