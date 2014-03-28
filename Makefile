


all : ssbros


objects : 
	g++ -g -c GameManager.cpp
	g++ -g -c Pursuer.cpp
	g++ -g -c OtherActors.cpp
	g++ -g -c GraphMap.cpp
	g++ -g -c Actor.cpp

ssbros : ssbros.cpp OtherActors.o
	g++ -g -Wall -o ssbros ssbros.cpp Actor.o GraphMap.o GameManager.o OtherActors.o Pursuer.o -lncurses

OtherActors.o: OtherActors.cpp
	g++ -g -Wall -c OtherActors.cpp

# Modify the clean target to remove YOUR .o files...
clean:
	rm ssbros OtherActors.o

tarball:
	make clean
	tar czf project2.tar.gz Makefile *.hpp ssbros.cpp OtherActors.cpp *.o maps/*.txt README

