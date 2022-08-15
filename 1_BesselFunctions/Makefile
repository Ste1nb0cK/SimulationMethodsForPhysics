CXX = g++
CXXFLAGS = -fopenmp
main.x: main.cpp Bisection.cpp Simpson.cpp Bessel.cpp
	${CXX}  ${CXXFLAGS} Bisection.cpp Simpson.cpp Bessel.cpp $< -o $@
