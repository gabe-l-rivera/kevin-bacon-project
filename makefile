HEDERS = Graph.h Matrix.h
OBJECTS = main.o Graph.o Matrix.o
EXEC = main.cpp

#build executable program
$(EXEC): $(OBJECTS)
	g++ $^ -o $@
##build objective files from source files
%.o: %.cpp $(HEADERS)
	g++ -c $< -o $@
#clean up the mess
clean:
	rm -i *.o


