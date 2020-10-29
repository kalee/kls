CC = g++
CFLAGS = -O

OBJS = jumble.o

jumble: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o jumble
	rm -f ${OBJS}

jumble.o: jumble.cpp 
	${CC} ${CFLAGS} -c jumble.cpp

clean:
	rm -f jumble ${OBJS}
	@echo "all cleaned up!"

