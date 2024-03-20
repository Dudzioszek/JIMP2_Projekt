CFLAGS = -Wall
TITLE = app

all:
	@cc $(CFLAGS) -c main.c load_maze.c algorytm.c queue.c
	@cc main.o load_maze.o algorytm.o queue.o -o $(TITLE)
	@echo Program został skompilowany jako: $(TITLE)
	@rm main.o load_maze.o algorytm.o queue.o

clear:
	@rm $(TITLE)