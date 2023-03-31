# Generic OpenMPI Makefile
# Ostermann - Mar 15, 2022
CXX=mpicxx -Wall -Werror -O2

TARGET=hamcycle

CCSOURCES=${wildcard *.cc}
HEADERS=${wildcard *.h}
OBJECTS=${CCSOURCES:.cc=.o}

all: ${TARGET}

${TARGET}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${TARGET}

${OBJECTS}: ${HEADERS}

test: ${TARGET}
	mpiexec -n 1 ${TARGET} star5.data
	mpiexec -n 1 ${TARGET} small_6.data
	mpiexec -n 1 ${TARGET} small_6.data
	mpiexec -n 1 ${TARGET} small_8.data
	mpiexec -n 1 ${TARGET} small_10.data
	mpiexec -n 1 ${TARGET} small_12.data
	mpiexec -n 1 ${TARGET} small_14.data
	mpiexec -n 1 ${TARGET} small_16.data
	mpiexec -n 1 ${TARGET} small_18.data
	mpiexec -n 1 ${TARGET} bigloaner10.data
	mpiexec -n 1 ${TARGET} bigloaner15.data

clean:
	rm -f  *.o ${TARGET}
