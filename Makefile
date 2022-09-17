LDFLAGS = -L/usr/local/lib
LIBS = -lglfw -lvulkan
INCS = -I/usr/local/include -I/usr/X11R6/include
CFLAGS_DEBUG = -O0 -ggdb -Wall -Werror=vla
CFLAGS_RELEASE = -Ofast -DNDEBUG

debug: main.c
	@echo "Making debug build:"
	${CC} ${CFLAGS_DEBUG} ${INCS} ${LDFLAGS} ${LIBS} -o $@ main.c

release: main.c
	@echo "Making release build:"
	${CC} ${CFLAGS_RELEASE} ${INCS} ${LDFLAGS} ${LIBS} -o $@ main.c

clean:
	rm -f debug release
