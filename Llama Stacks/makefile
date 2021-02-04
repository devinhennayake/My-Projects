CXX = g++
CXXFLAGS = -Wall

proj2: Llama.cpp Driver.cpp
	$(CXX) $(CXXFLAGS) Llama.cpp Driver.cpp -o proj1

run:
	./proj1

clean:
	rm *~

val:
	valgrind ./proj1
