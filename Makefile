# This file is part of Alienwave, a game by Alessandro Pira

CC = gcc
OBJS = main.o blit.o aliens.o xzarna.o fire.o shield.o levels.o util.o
# CFLAGS = -c -O2 -Wall -DDEBUG_LEV
CFLAGS = -c -O2 -Wall
LIB = -lncurses

# Uncomment this if you want random waves
# CFLAGS += -DRANDOM_LEVELS

# Uncomment one of these lines if you want. Default level is medium.
# Level only affects the chances of killing Xzarna.
# CFLAGS += -DLEV_EASY
# CFLAGS += -DLEV_HARD


alienwave: $(OBJS)
	$(CC) $(OBJS) $(LIB) -o alienwave
	strip alienwave

main.o: main.c

blit.o: blit.c

aliens.o: aliens.c

xzarna.o: xzarna.c

fire.o: fire.c

shield.o: shield.c

levels.o: levels.c

util.o: util.c

clean:
	rm -f ./*.o

distclean: clean
	rm -f alienwave

