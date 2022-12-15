#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int GRID_DIM = 99;

int main (void) {
    FILE* fp = fopen("input.txt", "r");
    int grid[GRID_DIM][GRID_DIM];
    int line_counter = 0;
    int visible_counter = 0;
    for ( ;; ) {
        char line[250];
        fgets(line, 250, fp);
        if (feof( fp )) break;
        for (int i = 0; i < GRID_DIM; i++) {
            grid[line_counter][i] = line[i] - '0';
        }
        line_counter++;
    }
    //add outside ones
    visible_counter += (GRID_DIM*2 + (GRID_DIM-2)*2);
    //check if visible
    for (int row = 1; row < GRID_DIM - 1; row++) {
        for (int col = 1; col < GRID_DIM -1; col++) {
            int curr_element = grid[row][col];
            int visible[4] = { 1, 1, 1, 1};
            int vis_counter = 0;
            //left
            for (int left = 0; left < col; left++) {
                if (grid[row][left] >= curr_element) {
                    visible[0] = 0;
                }
            }
            //right
            for (int right = GRID_DIM-1; right > col; right--) {
                if (grid[row][right] >= curr_element) {
                    visible[1] = 0;
                }
            }
            //top
            for (int top = 0; top < row; top++) {
                if (grid[top][col] >= curr_element) {
                    visible[2] = 0;
                }
            }
            //bottom
            for (int bot = GRID_DIM-1; bot > row; bot--) {
                if (grid[bot][col] >= curr_element) {
                    visible[3] = 0;
                }
            }
            for (int c = 0; c < 4; c++){
                if (visible[c] == 1){
                    vis_counter = 1;
                }
            }
            visible_counter += vis_counter;
        }
    }


    printf("got thru, result : %d", visible_counter);

    return 0;
}