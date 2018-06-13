#Makefile for ABY examples
#This file should be included as symlink in subdirectories of src/examples/

#DO NOT MODIFY THIS FILE, unless you know what you're doing

#You should not need to call this makefile separately. It will be called from the Makefile in the root directory

#relative project folders
BIN = ../../../bin
SRC = ../..
CORE=${SRC}/abycore

SOURCES := $(shell find . -type f -name '*.cpp')
OBJECTS := $(patsubst %.cpp, %.o, ${SOURCES})

# all source files and corresponding object files in abycore
SOURCES_CORE := $(shell find ${CORE} -type f -name '*.cpp' -not -path '*/ENCRYPTO_utils/Miracl/*' -not -path '*/ot/external/*')
OBJECTS_CORE := $(SOURCES_CORE:.cpp=.o)

# directory for the Miracl library
MIRACL_LIB_DIR=${CORE}/ENCRYPTO_utils/miracl_lib
OBJECTS_MIRACL=${MIRACL_LIB_DIR}/*.o

# compiler settings
CC=g++

#BATCH=

CFLAGS=

LIBRARIES=-lgmp -lgmpxx -lpthread ${CORE}/ENCRYPTO_utils/miracl_lib/miracl.a -L /usr/lib -lssl -lcrypto -lrt

#take the current directory's name as name for the executable in ${BIN}
EXAMPLE = $(lastword $(subst /, ,${CURDIR}))

all: ${BIN}/${EXAMPLE}.exe

${BIN}/${EXAMPLE}.exe: ${OBJECTS} ${OBJECTS_CORE} ${OBJECTS_MIRACL}
	${CC} ${ABY_COMPILER_OPTIONS} ${CFLAGS} $^ ${LIBRARIES} -o $@

%.o: %.cpp %.h
	${CC} $< ${ABY_COMPILER_OPTIONS} -c ${INCLUDE} ${CFLAGS} ${BATCH} -o $@

%.o: %.cpp
	${CC} $< ${ABY_COMPILER_OPTIONS} -c ${INCLUDE} ${CFLAGS} ${BATCH} -o $@

.PHONY: clean

clean:
	rm ${OBJECTS}
