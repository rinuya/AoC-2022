#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int GRID_DIM = 99;

int main (void) {
    FILE* fp = fopen("input.txt", "r");
    int grid[GRID_DIM][GRID_DIM];
    int line_counter = 0;
    int result = 0;
    //assign grid
    for ( ;; ) {
        char line[250];
        fgets(line, 250, fp);
        if (feof( fp )) break;
        for (int i = 0; i < GRID_DIM; i++) {
            grid[line_counter][i] = line[i] - '0';
        }
        line_counter++;
    }
    //check score
    for (int row = 1; row < GRID_DIM - 1; row++) {
        for (int col = 1; col < GRID_DIM -1; col++) {
            int curr_element = grid[row][col];
            int visible[4] = { 1, 1, 1, 1};
            int vis_counter = 1;
            //left
            if (grid[row][col-1] < curr_element){
                for (int left = col - 2; left >= 0; left--) {
                    if (grid[row][left] < curr_element) {
                        visible[0] = visible[0]+1;
                    } else {
                        visible[0] = visible[0]+1;
                        break;
                    }
                }
            }
            //right
            if (grid[row][col+1] < curr_element){
                for (int right = col + 2; right < GRID_DIM; right++) {
                    if (grid[row][right] < curr_element) {
                        visible[1] = visible[1]+1;
                    } else {
                        visible[1] = visible[1]+1;
                        break;
                    }
                }
            }
            //top
            if (grid[row-1][col] < curr_element){
                for (int top = row - 2; top >= 0; top--) {
                    if (grid[top][col] < curr_element) {
                        visible[2] = visible[2]+1;
                    } else {
                        visible[2] = visible[2]+1;
                        break;
                    }
                }
            }
            //bottom
            if (grid[row+1][col] < curr_element){
                for (int bot = row + 2; bot < GRID_DIM; bot++) {
                    if (grid[bot][col] < curr_element) {
                        visible[3] = visible[3]+1;
                    } else {
                        visible[3] = visible[3]+1;
                        break;
                    }
                }
            }
            for (int c = 0; c < 4; c++){ 
                vis_counter = vis_counter * visible[c];
            }
            if (vis_counter > result){
                result = vis_counter;
            };
        }
    }
    printf("Result: %d", result);

    return 0;
}