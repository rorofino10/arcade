CC = gcc
CFLAGS = -g -IC:/raylib/include        
LDFLAGS = -LC:/raylib/lib              
LDLIBS = -lraylib -lopengl32 -lgdi32 -lwinmm 

CODEDIRS = src

CFILES=$(foreach D,$(CODEDIRS),$(wildcard $(D)/*.c))
OBJECTS=$(patsubst %.c,%.o,$(CFILES))
BINDIR = bin
BINNAME = game
BINARY = ${BINDIR}/${BINNAME}.exe

all: ${BINARY}

${BINARY}: ${OBJECTS} | ${BINDIR}
	${CC} -o $@ $^ ${LDFLAGS} ${LDLIBS}

${BINDIR}:
	mkdir -p ${BINDIR}

test:
	./${BINARY}

clean:
	rm -rf ${BINARY} ${OBJECTS}
