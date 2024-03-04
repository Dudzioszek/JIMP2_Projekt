CFLAGS = -Wall
TITLE = app

all:
	@cc $(CFLAGS) -c main.c load_maze.c
	@cc main.o load_maze.o -o $(TITLE)
	@echo Program został skompilowany jako: $(TITLE)
	@rm main.o load_maze.o

clear:
	@rm $(TITLE)