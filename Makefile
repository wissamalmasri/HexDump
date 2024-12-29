

CC=g++





CCCFLAGS = -std=c++11 -Wall

xed:xed.cpp
	$(CCC) $(CCCFLAGS) xed.cpp -o xed

.PHONY: clean
clean: 
	rm -f xed

