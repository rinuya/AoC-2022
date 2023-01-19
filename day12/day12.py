#Note: Doing it in python first to get the idea down since I haven't used BFS much yet

class Point:
    def __init__(self, letter, row, col) -> None:
        self.letter = letter
        self.row = row
        self.col = col
        self.dist = None
        self.visited = False

        if letter == 'S':
            self.value = 1
        elif letter == 'E':
            self.value = ord('z') - 96 
        else:
            self.value = ord(letter) - 96 

class Map:
    def __init__(self) -> None:
        self.grid = []
        self.q = []
        self.start_val_q = []
        self.pathLengths = []
    
    def clearGrid(self):
        for row in range(len(self.grid)):
            for col in range(len(self.grid[0])):
                self.grid[row][col].dist = None
                self.grid[row][col].visited = False

f = open("input.txt", "r")
line_arr = [list(line[0:-1]) for line in f.readlines()]
f.close()

map = Map()
#generate map.grid
for row in range(len(line_arr)):
    grid_row, visited_row = [], []
    
    for col in range(len(line_arr[0])):
        p = Point(line_arr[row][col], row, col)
        if line_arr[row][col] == 'S' or line_arr[row][col] == 'a':
            map.start_val_q.append(p)

        grid_row.append(p)
 
    map.grid.append(grid_row)

# go through every possible starting val
while map.start_val_q:
    map.clearGrid()

    new_start = map.start_val_q.pop(0)
    new_start.dist = 0
    map.q = [new_start]
    map.grid[new_start.row][new_start.col].visited = True

    #Dijkstra BFS search
    while map.q:
        el = map.q.pop(0)
        if el.letter == 'E':
            map.pathLengths.append(el.dist)
            break
        else:
            # check if neighbor el (left, top, right, bottom) are viable and not visited, then add distance that has been walked up to that node and then add to q
            possibleDirections = [
                map.grid[el.row][el.col-1] if el.col-1 >= 0 else None, 
                map.grid[el.row-1][el.col] if el.row-1 >= 0 else None, 
                map.grid[el.row][el.col+1] if el.col+1 < len(map.grid[0]) else None, 
                map.grid[el.row+1][el.col] if el.row+1 < len(map.grid) else None,
            ]
            for d in possibleDirections:
                if d and map.grid[d.row][d.col].visited == False and d.value - el.value <= 1:
                    if d.dist == None or d.dist > el.dist + 1:
                        d.dist = el.dist + 1
                    map.q.append(d)
                    map.grid[d.row][d.col].visited = True

print(min(map.pathLengths))