EXENAME = main
SRCNAME = src/Eonia.cpp
OBJS = main.o

CXX = g++
CXXFLAGS = -std=c++14 -Iinclude -lssl -lcrypto -Wall -lboost_system -pthread

main.o: $(SRCNAME)
	$(CXX) $(SRCNAME) -o $(OBJS) $(CXXFLAGS)

clean:
	-rm -f *.o $(EXENAME)
