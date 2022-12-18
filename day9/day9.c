#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int GRID_VALUE = 9;

typedef struct Knot {
    int x;
    int y;
} Knot;

void create_knot(Knot* knot_array[], int index, int x_pos, int y_pos){
    Knot* new_knot;
    new_knot = (Knot*)malloc(sizeof(Knot));
    new_knot->x = x_pos;
    new_knot->y = y_pos;
    knot_array[index] = new_knot;
}
// modern compilers can pass matrices into functions by defining size_t's of their axes
void check_on_move(size_t x_val, size_t y_val, int grid[x_val][y_val], Knot* head, Knot* tail, int leave_mark){
    if ((head->x - tail->x) > 1 && head->y == tail->y){
        tail->x++;
        if (leave_mark == 1) grid[tail->x][tail->y] = GRID_VALUE;
    } else if ((head->x - tail->x) < -1 && head->y == tail->y){
        tail->x--;
        if (leave_mark == 1) grid[tail->x][tail->y] = GRID_VALUE;
    } else if ((head->y - tail->y) > 1 && head->x == tail->x){
        tail->y++;
        if (leave_mark == 1) grid[tail->x][tail->y] = GRID_VALUE;
    } else if ((head->y - tail->y) < -1 && head->x == tail->x){
        tail->y--;
        if (leave_mark == 1) grid[tail->x][tail->y] = GRID_VALUE;
    } else if (((head->x - tail->x) > 1 && (head->y - tail->y) >= 1) || ((head->y - tail->y) > 1 && (head->x - tail->x) >= 1)){
        tail->x++;
        tail->y++;
        if (leave_mark == 1) grid[tail->x][tail->y] = GRID_VALUE;
    } else if (((head->x - tail->x) < -1 && (head->y - tail->y) >= 1) || ((head->y - tail->y) > 1 && (head->x - tail->x) <= -1)){
        tail->x--;
        tail->y++;
        if (leave_mark == 1) grid[tail->x][tail->y] = GRID_VALUE;
    } else if (((head->x - tail->x) > 1 && (head->y - tail->y) <= -1) || ((head->y - tail->y) < -1 && (head->x - tail->x) >= 1)){
        tail->x++;
        tail->y--;
        if (leave_mark == 1) grid[tail->x][tail->y] = GRID_VALUE;
    } else if (((head->x - tail->x) < -1 && (head->y - tail->y) <= -1) || ((head->y - tail->y) < -1 && (head->x - tail->x) <= -1)){
        tail->x--;
        tail->y--;
        if (leave_mark == 1) grid[tail->x][tail->y] = GRID_VALUE;
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

    int margin = 10;
    int x_width = abs(max_left)+max_right+(2 * margin);
    int y_width = abs(max_down)+max_up+(2 * margin);
    int grid[x_width][y_width];
    Knot head = {
        x: abs(max_left)+margin,
        y: abs(max_down)+margin,
    };
    Knot* knot_array[9];
    for (int i = 0; i < 9; i++){
        create_knot(knot_array, i, abs(max_left)+margin, abs(max_down)+margin);
    }
    grid[head.x][head.y] = GRID_VALUE;

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
            for (int a = 0; a < amount; a++) {
                head.x-=1;
                for (int i = 0; i < 9; i++) {
                    if (i == 0){
                        check_on_move(x_width, y_width, grid, &head, knot_array[0], 0);
                    } else if (i == 8) {
                        check_on_move(x_width, y_width, grid, knot_array[i-1], knot_array[i], 1);
                    } else {
                        check_on_move(x_width, y_width, grid, knot_array[i-1], knot_array[i], 0);
                    }
                }
                
            }
            break;
        case 'R':
            for (int a = 0; a < amount; a++) {
                head.x+=1;
                for (int i = 0; i < 9; i++) {
                    if (i == 0){
                        check_on_move(x_width, y_width, grid, &head, knot_array[0], 0);
                    } else if (i == 8) {
                        check_on_move(x_width, y_width, grid, knot_array[i-1], knot_array[i], 1);
                    } else {
                        check_on_move(x_width, y_width, grid, knot_array[i-1], knot_array[i], 0);
                    }
                }
            }
            break;
        case 'U':
            for (int a = 0; a < amount; a++) {
                head.y+=1;
                for (int i = 0; i < 9; i++) {
                    if (i == 0){
                        check_on_move(x_width, y_width, grid, &head, knot_array[0], 0);
                    } else if (i == 8) {
                        check_on_move(x_width, y_width, grid, knot_array[i-1], knot_array[i], 1);
                    } else {
                        check_on_move(x_width, y_width, grid, knot_array[i-1], knot_array[i], 0);
                    }
                }
            }
            break;
        case 'D':
            for (int a = 0; a < amount; a++) {
                head.y-=1;
                for (int i = 0; i < 9; i++) {
                    if (i == 0){
                        check_on_move(x_width, y_width, grid, &head, knot_array[0], 0);
                    } else if (i == 8) {
                        check_on_move(x_width, y_width, grid, knot_array[i-1], knot_array[i], 1);
                    } else {
                        check_on_move(x_width, y_width, grid, knot_array[i-1], knot_array[i], 0);
                    }
                }
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