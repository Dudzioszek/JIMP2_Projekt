CFLAGS = -Wall
TITLE = app

all:
	@cc $(CFLAGS) -c main.c load_maze.c char_stack.c dfs.c int_stack.c short_stack.c binary.c manage.c bfs.c queue.c
	@cc main.o load_maze.o char_stack.o dfs.o int_stack.o short_stack.o binary.o manage.o bfs.o queue.o -o $(TITLE)
	@echo Program został skompilowany jako: $(TITLE)
	@rm main.o load_maze.o char_stack.o dfs.o int_stack.o short_stack.o binary.o manage.o bfs.o queue.o

clear:
	@rm $(TITLE)