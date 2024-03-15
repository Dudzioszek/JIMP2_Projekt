import random

def generate_maze(width, height):
    maze = [['X' for _ in range(width)] for _ in range(height)]
    maze[1][1] = ' '
    stack = [(1, 1)]
    while stack:
        cx, cy = stack[-1]
        maze[cy][cx] = ' '

        neighbors = []
        for dx, dy in [(1, 0), (-1, 0), (0, 1), (0, -1)]:
            nx, ny = cx + dx*2, cy + dy*2
            if 0 < nx < width - 1 and 0 < ny < height - 1 and maze[ny][nx] == 'X':
                neighbors.append((nx, ny))

        if neighbors:
            nx, ny = random.choice(neighbors)
            wall_x, wall_y = (cx + nx) // 2, (cy + ny) // 2
            maze[wall_y][wall_x] = ' '
            stack.append((nx, ny))
        else:
            stack.pop()

    maze[1][0] = 'P'
    maze[height - 2][width - 1] = 'K'
    return maze

def save_maze_to_file(maze, filename):
    with open(filename, 'w') as f:
        for row in maze:
            f.write(''.join(row) + '\n')

# Wymiary labiryntu (muszą być nieparzyste)
width =	1025
height = 1025

maze = generate_maze(width, height)

filename = 'maze.txt'
save_maze_to_file(maze, filename)
print(f"Maze saved to {filename}")
