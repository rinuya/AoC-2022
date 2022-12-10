#include <stdio.h>
#include <string.h>

typedef struct range {
    int min;
    int max;
} range;

void transfer_string (char* str, char* destination, int length) {
    for (int i = 0; i < length; i++) {
        char curr[1];
        curr[0] = str[i];
        if (curr[0] == '\0') {
            destination[i] = '\0';
            break;
        } else {
            destination[i] = str[i];
        }
    }
}

void assign_ranges(char* str, range* first, range* second) {
    // split up at ","
    char* token;
    token = strtok(str, ",");
    char first_half[7];
    transfer_string(token, first_half, strlen(token));
    token = strtok(NULL, ",");
    char second_half[7];
    transfer_string(token, second_half, strlen(token));

    // split at "-" and assign values to struct "first"
    char* f_h_token;
    f_h_token = strtok(first_half, "-");
    int buff_1 = atoi(f_h_token);
    f_h_token = strtok(NULL, "-");
    int buff_2 = atoi(f_h_token);

    if (buff_1 > buff_2) {
        first->min = buff_2;
        first->max = buff_1;
    } else {
        first->min = buff_1;
        first->max = buff_2;
    }

    // split at "-" and assign values to struct "second"
    char* s_h_token;
    s_h_token = strtok(second_half, "-");
    buff_1 = atoi(s_h_token);
    s_h_token = strtok(NULL, "-");
    buff_2 = atoi(s_h_token);

    if (buff_1 > buff_2) {
        second->min = buff_2;
        second->max = buff_1;
    } else {
        second->min = buff_1;
        second->max = buff_2;
    }
}

void check_if_overlaps (range* first, range* second, int* counter) {
    if ((first->min <= second->min && first->max >= second->min) || (first->min <= second->max && first->max >= second->max) || (second->min <= first->min && second->max >= first->min) || (second->max <= first->max && second->max >= first->min)) {
        *counter += 1;
    }
}

int main () {

    FILE* fp = fopen("input.txt", "r");
    int result = 0;
    for ( ;; ) {
        char line[13];
        range first;
        range second;

        fgets(line, 13, fp);
        if (feof( fp )) break;

        assign_ranges(line, &first, &second);
        check_if_overlaps(&first, &second, &result);
    }

    if (feof(fp)) {
        printf("The solution is %d:\n", result);
    }
    fclose(fp);
    return 0;
}