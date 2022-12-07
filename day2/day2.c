#include <stdio.h>
#include <string.h>

void play_round (int* total, char opponent, char player) {
    switch (player) {
        case 'X':
            *total += 1;
            switch (opponent) {
                case 'A':
                    *total += 3;
                    break;
                case 'B':
                    *total += 0;
                    break;
                case 'C':
                    *total += 6;
                    break;
            }
            break;
        case 'Y':
            *total += 2;
            switch (opponent) {
                case 'A':
                    *total += 6;
                    break;
                case 'B':
                    *total += 3;
                    break;
                case 'C':
                    *total += 0;
                    break;
            }
            break;
        case 'Z':
            *total += 3;
            switch (opponent) {
                case 'A':
                    *total += 0;
                    break;
                case 'B':
                    *total += 6;
                    break;
                case 'C':
                    *total += 3;
                    break;
            }
            break;
    }
}

void choose_strategy (char* choice, char opponent, char player) {
    switch (player) {
        case 'X':
            switch (opponent) {
                case 'A':
                    *choice = 'Z';
                    break;
                case 'B':
                    *choice = 'X';
                    break;
                case 'C':
                    *choice = 'Y';
                    break;
            }
            break;
        case 'Y':
            switch (opponent) {
                case 'A':
                    *choice = 'X';
                    break;
                case 'B':
                    *choice = 'Y';
                    break;
                case 'C':
                    *choice = 'Z';
                    break;
            }
            break;
        case 'Z':
            switch (opponent) {
                case 'A':
                    *choice = 'Y';
                    break;
                case 'B':
                    *choice = 'Z';
                    break;
                case 'C':
                    *choice = 'X';
                    break;
            }
            break;
    }
}

int main ()
{
    FILE* fp = fopen("input.txt", "r");;
    char line[5];
    int total = 0;
    char choice[1];

    while (!feof(fp)) {
        fgets(line, 5, fp);
        choose_strategy(&choice[0], line[0], line[2]);
        play_round(&total, line[0],  choice[0]);
    }

    if (feof(fp)) {
        printf("The solution is: %d\n", total);
    } else {
        printf("Something went wrong\n");
    }
    fclose(fp);

    return 0;
}