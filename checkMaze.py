from PIL import Image, ImageDraw

# Define colors
wall_color = (0, 0, 0)       # Black
path_color = (255, 255, 255) # White
start_color = (0, 255, 0)    # Green (start)
end_color = (255, 0, 0)      # Red (end)

# Size of maze cells
cell_size = 20

# Read maze from file
with open("maze.txt", "r") as file:
    maze_text = file.read()

maze_lines = maze_text.strip().split('\n')
maze_width = len(maze_lines[0])
maze_height = len(maze_lines)

# Create image
maze_image = Image.new("RGB", (maze_width * cell_size, maze_height * cell_size))

# Create drawing object
draw = ImageDraw.Draw(maze_image)

# Draw maze
for y, line in enumerate(maze_lines):
    for x, char in enumerate(line):
        if char == 'X':
            draw.rectangle([(x * cell_size, y * cell_size), ((x + 1) * cell_size, (y + 1) * cell_size)], fill=wall_color)
        elif char == 'P':
            draw.rectangle([(x * cell_size, y * cell_size), ((x + 1) * cell_size, (y + 1) * cell_size)], fill=start_color)
        elif char == '-':
            draw.rectangle([(x * cell_size, y * cell_size), ((x + 1) * cell_size, (y + 1) * cell_size)], fill=end_color)
        else:
            draw.rectangle([(x * cell_size, y * cell_size), ((x + 1) * cell_size, (y + 1) * cell_size)], fill=path_color)

# Save image as JPG
maze_image.save("maze.jpg")
print("Done")