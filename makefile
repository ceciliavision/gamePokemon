# define variables
HDRDIR  = ./

# set options for this machine
# specify which compilers to use for c and linking
CXX	= g++
LD	= g++

# compiler flags to be used (set to compile with debugging on)
CXXFLAGS = -I$(HDRDIR) -O3 -pg

# link flags to be used 
LDFLAGS	= -pg -O3

# detect the unix type
UNAME := $(shell uname -s)

# libraries to be linked in
ifeq ($(UNAME),Darwin)
# for MAC OS X
CXXFLAGS += -D__MAC_OS=1
LIBS =  -framework GLUT -framework OpenGL 
else
LIBS	= -lglut -lGL -lGLU -lm 
endif


# types of files we are going to construct rules for
.SUFFIXES: .cpp

# rule for .cpp files
.cpp.o:
	$(CXX) $(CXXFLAGS) -o $*.o -c $*.cpp

# list of objects to be compiled
OBJS    = scene.o texture.o tga.o



scene:$(OBJS)   gamehead.hpp snake.hpp house.hpp tree.hpp car.hpp read_obj.hpp
	$(LD)  $(LDFLAGS) -o scene $(OBJS) $(LIBS); 
	



# what to do if user types "make clean"
clean :
	rm -r $(OBJS) scene


