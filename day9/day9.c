#include <stdio.h>
#include <stdlib.h>
int GRID_VALUE = 124;   //value that "fills" the grid, should not be 1 (buggy behaviour)

typedef struct Knot {
    int x;
    int y;
    int prev_x;
    int prev_y;
} Knot;

// modern compilers can pass matrices into functions by defining size_t's of their axes
void check_on_move(size_t x_val, size_t y_val, int grid[x_val][y_val], Knot* head, Knot* tail){
    if (abs(head->x - tail->x) > 1){
        tail->prev_x = tail->x;
        tail->prev_y = tail->y;
        tail->x = head->prev_x;
        tail->y = head->prev_y;
        grid[tail->x][tail->y] = GRID_VALUE;
    } else if (abs(head->y - tail->y) > 1){
        tail->prev_x = tail->x;
        tail->prev_y = tail->y;
        tail->x = head->prev_x;
        tail->y = head->prev_y;
        grid[tail->x][tail->y] = GRID_VALUE;
    }
}

int main(){
    // first figure out grid dimensions
    FILE* fp = fopen("input.txt", "r");
    int result = 0, max_left = 0, max_right = 0, max_up = 0, max_down = 0, pos_x = 0, pos_y = 0;
    for ( ;; ) {
        char line[10];
        fgets(line, 10, fp);
        if (feof( fp )) break;

        char direction[1]; 
        int amount;
        sscanf(line, "%c %d\n", direction, &amount);
        switch (direction[0])
        {
        case 'L':
            for (int i = 0; i < amount; i++) {
                pos_x-=1;
                if (pos_x < max_left) max_left = pos_x;
            }
            break;
        case 'R':
            for (int i = 0; i < amount; i++) {
                pos_x+=1;
                if (pos_x > max_right) max_right = pos_x;
            }
            break;
        case 'U':
            for (int i = 0; i < amount; i++) {
                pos_y+=1;
                if (pos_y > max_up) max_up = pos_y;
            }
            break;
        case 'D':
            for (int i = 0; i < amount; i++) {
                pos_y-=1;
                if (pos_y < max_down) max_down = pos_y;
            }
            break;
        default:
            break;
        }

    }
    fclose(fp);
    int margin = 10; //grid margin (for illustrational purposes)
    int x_width = abs(max_left)+max_right+(2 * margin);
    int y_width = abs(max_down)+max_up+(2 * margin);
    int grid[x_width][y_width];

    Knot head = {
        x: abs(max_left)+margin,
        y: abs(max_down)+margin,
        prev_x: abs(max_left)+margin,
        prev_y: abs(max_down)+margin,
    };
    Knot tail = {
        x: abs(max_left)+margin,
        y: abs(max_down)+margin,
    };
    grid[tail.x][tail.y] = GRID_VALUE;

    FILE* fp2 = fopen("input.txt", "r");
    for ( ;; ) {
        char line[10];
        fgets(line, 10, fp2);
        if (feof( fp2 )) break;
 
        char direction[1]; 
        int amount;
        sscanf(line, "%c %d\n", direction, &amount);
        switch (direction[0])
        {
        case 'L':
            for (int i = 0; i < amount; i++) {
                head.prev_y = head.y;
                head.prev_x = head.x;
                head.x-=1;
                check_on_move(x_width, y_width, grid, &head, &tail);
            }
            break;
        case 'R':
            for (int i = 0; i < amount; i++) {
                head.prev_y = head.y;
                head.prev_x = head.x;
                head.x+=1;
                check_on_move(x_width, y_width, grid, &head, &tail);
            }
            break;
        case 'U':
            for (int i = 0; i < amount; i++) {
                head.prev_y = head.y;
                head.prev_x = head.x;
                head.y+=1;
                check_on_move(x_width, y_width, grid, &head, &tail);
            }
            break;
        case 'D':
            for (int i = 0; i < amount; i++) {
                head.prev_y = head.y;
                head.prev_x = head.x;
                head.y-=1;
                check_on_move(x_width, y_width, grid, &head, &tail);
            }
            break;
        }    
    }
    fclose(fp2);

    for (int x = 0; x < x_width; x++){
        for (int y = 0; y < y_width; y++){
            if (grid[x][y] == GRID_VALUE) result++;
        }
    }
    printf("Marked spots: %d", result);

    return 0;
}