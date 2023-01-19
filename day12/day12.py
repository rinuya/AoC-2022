'''
Note: Doing it in python first to get the idea down since I haven't used BFS much yet
'''
class Point:
    def __init__(self, letter, row, col) -> None:
        self.letter = letter
        self.row = row
        self.col = col
        self.dist = None

        if letter == 'S':
            self.value = 1
            self.dist = 0
        elif letter == 'E':
            self.value = ord('z') - 96 
        else:
            self.value = ord(letter) - 96 

class Map:
    def __init__(self) -> None:
        self.grid = []

class Solution:
    def __init__(self) -> None:
        self.grid = []
        self.found = False
        self.q = []

f = open("input.txt", "r")
line_arr = [list(line[0:-1]) for line in f.readlines()]
f.close()

map, solution = Map(), Solution()

#generate map.grid and solution.grid
for row in range(len(line_arr)):
    grid_row, visited_row = [], []
    
    for col in range(len(line_arr[0])):
        p = Point(line_arr[row][col], row, col)
        if line_arr[row][col] == 'S':
            solution.start = [row, col]
            p.dist = 0
            visited_row.append(True)
        else:
            visited_row.append(False)

        grid_row.append(p)
 
    map.grid.append(grid_row)
    solution.grid.append(visited_row)

#add start S to q
solution.q.append(map.grid[solution.start[0]][solution.start[1]])

#Dijkstra BFS search
while solution.found == False:
    el = solution.q.pop(0)
    if el.letter == 'E':
        solution.found = True
        print(f"The distance is {el.dist}")
    else:
        # check if neighbor el (left, top, right, bottom) are viable and not visited, then add distance that has been walked up to that node and then add to q
        l = map.grid[el.row][el.col-1] if el.col-1 >= 0 else None
        t = map.grid[el.row-1][el.col] if el.row-1 >= 0 else None
        r = map.grid[el.row][el.col+1] if el.col+1 < len(map.grid[0]) else None
        b = map.grid[el.row+1][el.col] if el.row+1 < len(map.grid) else None

        if l and solution.grid[l.row][l.col] == False and l.value - el.value <= 1:
            if l.dist == None or l.dist > el.dist + 1:
                l.dist = el.dist + 1
            solution.q.append(l)
            solution.grid[l.row][l.col] = True

        if t and solution.grid[t.row][t.col] == False and t.value - el.value <= 1:
            if t.dist == None or t.dist > el.dist + 1:
                t.dist = el.dist + 1
            solution.q.append(t)
            solution.grid[t.row][t.col] = True

        if r and solution.grid[r.row][r.col] == False and r.value - el.value <= 1:
            if r.dist == None or r.dist > el.dist + 1:
                r.dist = el.dist + 1
            solution.q.append(r)
            solution.grid[r.row][r.col] = True

        if b and solution.grid[b.row][b.col] == False and b.value - el.value <= 1:
            if b.dist == None or b.dist > el.dist + 1:
                b.dist = el.dist + 1
            solution.q.append(b)
            solution.grid[b.row][b.col] = True