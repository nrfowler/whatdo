Debug: 
    all
all: 
	g++ -Wall -o whatdo whatdo.cpp
whatdo.o: whatdo.cpp whatdo.h
	g++ -Wall -c whatdo.cpp
clean:
	rm -f  *.o whatdo



