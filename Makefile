CFLAGS = -Wall
TITLE = app

all:
	@cc $(CFLAGS) -c main.c load_maze.c char_stack.c algorytm.c int_stack.c short_stack.c
	@cc main.o load_maze.o char_stack.o algorytm.o int_stack.o short_stack.o -o $(TITLE)
	@echo Program został skompilowany jako: $(TITLE)
	@rm main.o load_maze.o char_stack.o algorytm.o int_stack.o short_stack.o

clear:
	@rm $(TITLE)