class Map():
    def __init__(self) -> None:
        self.grid = [['.' for el in range(1000)] for row in range(500)]
        self.sand_amt = 0
        self.sand_row = 0
        self.sand_col = 500
        self.lowest_point = 1
        self.end = False


    def addHashtag(self, l):
        pos = 0
        while pos + 1 < len(l):
            xy1 = list(map(int, l[pos].split(',')))
            xy2 = list(map(int, l[pos+1].split(',')))

            if xy1[1] > self.lowest_point:
                self.lowest_point = xy1[1]
            if xy2[1] > self.lowest_point:
                self.lowest_point = xy2[1]

            if xy1[0] == xy2[0]:
                hashes = sorted([xy1[1], xy2[1]])
                for i in range(hashes[1]-hashes[0]+1):
                    self.grid[hashes[0]+i][xy1[0]] = '#'
            else:
                hashes = sorted([xy1[0], xy2[0]])
                for i in range(hashes[1]-hashes[0]+1):
                    self.grid[xy1[1]][hashes[0]+i] = '#'

            pos = pos+1

    def dropSand(self):
        if self.sand_row > self.lowest_point:
            self.end = True
            self.sand_row = None
            self.sand_col = None

        elif self.grid[self.sand_row+1][self.sand_col] == '.': 
            self.sand_row = self.sand_row + 1

        elif self.grid[self.sand_row + 1][self.sand_col - 1] == '.':    
            self.sand_row = self.sand_row + 1
            self.sand_col = self.sand_col - 1

        elif self.grid[self.sand_row + 1][self.sand_col + 1] == '.':
            self.sand_row = self.sand_row + 1
            self.sand_col = self.sand_col + 1

        else:
            self.grid[self.sand_row][self.sand_col] = 'o'
            self.sand_row = None
            self.sand_col = None

    def sandMove(self):
        while self.end == False:
            self.sand_row, self.sand_col, self.sand_amt = 1, 500, self.sand_amt + 1
            while self.sand_row != None and self.sand_col != None:
                self.dropSand()
             
        print(f"The solution is:{self.sand_amt -1}")


wf = Map()
f = open("input.txt", "r")
line_arr = [line[0:-1].split(' -> ') for line in f.readlines()]
f.close()
for line in line_arr:
    wf.addHashtag(line)

wf.sandMove()