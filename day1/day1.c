#include <stdio.h>
#include <stdlib.h>

int main () 
{
    FILE* fp;
    fp = fopen("input.txt", "r");

    char ch[20];
    int num;
    int current = 0;
    int first = 0;
    int second = 0;
    int third = 0;
    
    while (!feof(fp))
    {
        fgets(ch, 20, fp);
        num = atoi(ch);
        if (num) {
            current += num;
        } else {
            if (current > third) {
                if (current > second) {
                    if (current > first) {
                        third = second;
                        second = first;
                        first = current;
                    } else {
                        third = second;
                        second = current;
                    }
                } else {
                    third = current;
                }
            }
            current = 0;
        }
    }
    int result = first + second + third;

    if (feof(fp)) {
        printf("First: %d\n", first);
        printf("Second: %d\n", second);
        printf("Third: %d\n", third);
        printf("Top 3 have %d calories together\n", result);
    } else {
        printf("Something went wrong");
    }

    fclose(fp);

    return 0;
}