#include <stdio.h>
#include <string.h>

void transfer_string (char* str, char* destination) {
    for (int i = 0; i < strlen(str); i++) {
        if (i == strlen(str)-1) {
            destination[i] = '\0';
        } else {
            destination[i] = str[i];
        }
    }
}

void find_common_item (char* first, char* second, char* third, char* common_item) {
    for (int a = 0; a < strlen(first); a++) {
        for (int b = 0; b < strlen(second); b++) {
            for (int c = 0; c < strlen(third); c++) {
                if (first[a] == second[b] && first[a] == third[c]) {
                    *common_item = first[a];
                }
            }
        }
    }
}

void add_priority (int* total, char* common_item, char* letters) {
    for (int i = 0; i < 52; i++) {
        if (letters[i] == common_item[0]) {
            *total += (i + 1);
        }
    }
}

char letters[52] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z','A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

int main ()
{
    FILE* fp = fopen("input.txt", "r");
    int total = 0;
    char first[50];
    char second[50];
    char third[50];
    int counter = 1;
    char common_item[1];

    for ( ;; ) {
        char line[50];
    
        fgets(line, 50, fp);
        if (feof( fp )) break;
        
        switch (counter) {
            case 1:
                transfer_string(line, first);
                counter++;
                break;
            case 2:
                transfer_string(line, second);
                counter++;
                break;
            case 3:
                transfer_string(line, third);
                find_common_item(first, second, third, common_item);
                add_priority(&total, common_item, letters);
                counter = 1;
                break;
        }        
    }

    if (feof(fp)) {
        printf("The solution is %d:\n", total);
    } else {
        printf("Something went wrong\n");
    }
    fclose(fp);

    return 0;
}