CXX = g++
Plot_File_Name = OrbitPlot.pdf
OBJECTS = Body.o Planet_Vector.o vector.o
Python = python3

${Plot_File_Name}: foo Plotter.py data.dat
	${Python} Plotter.py

foo: ${OBJECTS}
	${CXX} ${OBJECTS} -o foo


data.dat: foo
	./foo > data.dat



clean:
	rm *.o
	rm foo
