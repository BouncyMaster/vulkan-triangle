LDFLAGS = -L/usr/local/lib
LIBS = -lglfw -lvulkan
INCS = -I/usr/local/include -I/usr/X11R6/include
CFLAGS = -O2

triangle: main.c
	${CC} ${CFLAGS} ${INCS} ${LDFLAGS} ${LIBS} -o $@ main.c
