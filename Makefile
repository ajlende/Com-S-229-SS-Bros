# Makefile for the Super Stolee Bros program
# 
#   Contents:
#    1. Default make command
#    2. clean command
#    3. tarball command
#

CXX = g++
CXXFLAGS = -g -Wall
LIBS = -lncurses


MY_DEPS = 
DEPS = $(MY_DEPS) Actor.hpp GameManager.hpp GraphMap.hpp OtherActors.hpp Pursuer.hpp


MY_OBJ = 
OBJ = $(MY_OBJ) Actor.o GameManager.o GraphMap.o OtherActors.o Pursuer.o ssbros.o


.PHONY : all clean tarball


# 1. Default make command to compile all the files
all : ssbros

%.o : %.cpp $(DEPS)
	$(CXX) -c $(CXXFLAGS) -o $@ $<

ssbros : $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)


# 2. This will clean out any non-source files from the directory
clean :
	rm -f ssbros $(MY_OBJ)


# 3. This will clean the project, and then make a tarball from the files for submission
tarball :
	rm -f ssbros $(MY_OBJ) # This ensures that nothing from MY_OBJ is in the submission
	tar czf ajlende.tar.gz README Makefile *.cpp *.hpp *.o

