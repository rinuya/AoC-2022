#include <stdio.h>
#include <string.h>

int main () {
    char str[4100];
    int result = 0;
    FILE* fp = fopen("input.txt", "r");
    fgets(str, 4100, fp);
    for (int i = 13; i < strlen(str); i++){
        char buffer[16];
        for (int start = 0; start < 14; start++){
            buffer[start] = str[i-start];
        }
        int duplicates = 0;
        for (int j = 0; j < 14; j++) {
            for (int k = 0; k < 14; k++) {
                if (j != k){
                    if (buffer[j] == buffer[k]) {
                        duplicates++;
                    }
                }
            }
        }
        if (duplicates == 0) {
            result = i+1;
            break;
        }
    }
    printf("The result is %d", result);
    fclose(fp);
    return 0;
}