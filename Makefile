.PHONY=clean


all: event.o movement.o render.o food.o combat.o
	gcc game.c event.o movement.o render.o food.o combat.o -lSDL2main -lSDL2 -lSDL2_image -lm -o tanks

event.o: event.c event.h game.h
	gcc -c event.c

movement.o: movement.c movement.h game.h
	gcc -c movement.c

food.o: food.c food.h game.h
	gcc -c food.c

combat.o: combat.c combat.h game.h
	gcc -c combat.c

render.o: render.c render.h food.c food.h game.h
	gcc -c render.c

run: all
	./tanks

clean:
	rm tanks *.o