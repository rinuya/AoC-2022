#include <stdio.h>
#include <string.h>

int main () {
    char str[4100];
    int result = 0;
    FILE* fp = fopen("input.txt", "r");
    fgets(str, 4100, fp);
    for (int i = 3; i < strlen(str); i++){
        char buffer[] = {str[i], str[i-1], str[i-2], str[i-3]};
        int duplicates = 0;
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
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