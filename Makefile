EXENAME = main
OBJS = main.o

CXX = g++
CXXFLAGS = -std=c++14 -lssl -lcrypto -Wall -lboost_systemv -pthread

main.o: main.cpp
	$(CXX) main.cpp -o $(OBJS) $(CXXFLAGS)

clean:
	-rm -f *.o $(EXENAME)
