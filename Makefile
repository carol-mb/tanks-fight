.PHONY=clean


all: event.o movement.o render.o food.o combat.o collision.o
	gcc game.c event.o movement.o render.o food.o combat.o collision.o -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lm -o tanks

event.o: event.c game.h
	gcc -c event.c

movement.o: movement.c game.h
	gcc -c movement.c

food.o: food.c game.h
	gcc -c food.c

combat.o: combat.c game.h
	gcc -c combat.c

render.o: render.c food.c game.h
	gcc -c render.c

collision.o: collision.c game.h
	gcc -c collision.c

run: all
	./tanks

clean:
	rm tanks *.o