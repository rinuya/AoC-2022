#include <stdio.h>
#include <stdlib.h>
int GRID_VALUE = 10;

void check_and_switch_row (int* cycle, int* row) {
    if ((*cycle) % 40 == 0) {
        (*cycle) = 0;
        (*row)--;
    }
}

void add_pixel (int grid[40][6], int x_register, int pos_x, int row) {
    if (abs(x_register - pos_x) <= 1) {
        grid[pos_x][row] = GRID_VALUE;
    }
}

int main () {
    FILE* fp = fopen("input.txt", "r");
    int cycle_count = 0, row = 5, x_register = 1;
    int grid[40][6]; 

    for ( ;; ) {
        char line[10];
        fgets(line, 10, fp);
        if (feof( fp )) break;

        char noop_or_addx[4];
        int line_amount;
        sscanf(line, "%s %d", noop_or_addx, &line_amount);

        if (noop_or_addx[0] == 'n'){
            add_pixel(grid, x_register, cycle_count, row);
            cycle_count++;
            check_and_switch_row(&cycle_count, &row);
        } else {
            add_pixel(grid, x_register, cycle_count, row);
            cycle_count++;
            check_and_switch_row(&cycle_count, &row);

            add_pixel(grid, x_register, cycle_count, row);
            cycle_count++;
            check_and_switch_row(&cycle_count, &row);
            x_register += line_amount;
        }
    }
    for (int i = 5; i >= 0; i--){
        for (int j = 0; j<40; j++){
            if (grid[j][i] == GRID_VALUE) {
                printf("#");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
    fclose(fp);
    return 0;
}