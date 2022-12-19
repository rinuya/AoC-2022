#include <stdio.h>
#include <stdlib.h>

void check_and_add_signal (int* array, int* index, int current_register, int cycle_count) {
    if (cycle_count == 20 || ((cycle_count-20) % 40 == 0)) {
        array[*index] = (current_register * cycle_count);
        (*index)++;
    }
}

int main () {
    FILE* fp = fopen("input.txt", "r");
    int cycle_count = 0, result = 0, x_register = 1, index = 0;
    int signal_strengths[6]; 

    for ( ;; ) {
        char line[10];
        fgets(line, 10, fp);
        if (feof( fp )) break;

        char noop_or_addx[4];
        int line_amount;
        sscanf(line, "%s %d", noop_or_addx, &line_amount);
        if (noop_or_addx[0] == 'n'){
            cycle_count++;
            check_and_add_signal(&signal_strengths, &index, x_register, cycle_count);
        } else {
            cycle_count++;
            check_and_add_signal(&signal_strengths, &index, x_register, cycle_count);
            cycle_count++;
            check_and_add_signal(&signal_strengths, &index, x_register, cycle_count);
            x_register += line_amount;
        }
    }
    for (int i = 0; i < index; i++) {
        result += signal_strengths[i];
    }
    printf("Result is: %d", result);
    fclose(fp);
    return 0;
}