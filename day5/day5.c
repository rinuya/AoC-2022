#include <stdio.h>
#include <string.h>

typedef struct Stack {
    char data[100];
    int top;
} Stack;

void push_on_stack(Stack* target, int amount, char* value) {
    for (int i = 0; i < amount; i++){
        target->top++;
        target->data[target->top] = value[i];
    } 
}

void pop_from_stack(Stack* target, int amount, char* returnvalue) {
    if (target->top < 0) {
        printf("Error, stack is empty\n");
    }
    for (int i = 0; i < amount; i++) {
        returnvalue[amount-i-1] = target->data[target->top];
        target->top--;
    }
}

void split_string_and_assign (char* str, Stack** stacks) {
    char newStr[25];
    for (int i = 5; i < strlen(str); i++) {
        newStr[i-5] = str[i];
    }
    char* p;
    char* q;
    int amt, int_from, int_to;
    p = strtok(newStr, " ");
    sscanf(p, "%d", &amt);
    p = strtok(NULL, " ");
    p = strtok(NULL, " ");
    sscanf(p, "%d", &int_from);
    p = strtok(NULL, " ");
    p = strtok(NULL, " ");
    sscanf(p, "%d", &int_to);

    char value[100];
    pop_from_stack(stacks[int_from-1], amt, value);
    push_on_stack(stacks[int_to-1], amt, value);
}

void assign_starting_input (Stack* one, Stack* two, Stack* three, Stack* four, Stack* five, Stack* six, Stack* seven, Stack* eight, Stack* nine) {
    char arr_one[12] = {'H', 'T', 'Z', 'D'};
    one->top = -1;
    push_on_stack(one, 4, arr_one);

    char arr_two[12] = {'Q', 'R', 'W', 'T', 'G', 'C', 'S'};
    two->top = -1;
    push_on_stack(two, 7, arr_two);

    char arr_three[12] = {'P', 'B', 'F', 'Q', 'N', 'R', 'C', 'H'};
    three->top = -1;
    push_on_stack(three, 8, arr_three);

    char arr_four[12] = {'L', 'C', 'N', 'F', 'H', 'Z'};
    four->top = -1;
    push_on_stack(four, 6 ,arr_four);

    char arr_five[12] = {'G', 'L', 'F', 'Q', 'S'};
    five->top = -1;
    push_on_stack(five, 5, arr_five);

    char arr_six[12] = {'V', 'P', 'W', 'Z', 'B', 'R', 'C', 'S'};
    six->top = -1;
    push_on_stack(six, 8, arr_six);

    char arr_seven[12] = {'Z', 'F', 'J'};
    seven->top = -1;
    push_on_stack(seven, 3, arr_seven);

    char arr_eight[12] = {'D', 'L', 'V', 'Z', 'R', 'H', 'Q'};
    eight->top = -1;
    push_on_stack(eight, 7, arr_eight);

    char arr_nine[12] = {'B', 'H', 'G', 'N', 'F', 'Z', 'L', 'D'};
    nine->top = -1;
    push_on_stack(nine, 8, arr_nine);
}

int main () {
    FILE* fp = fopen("input.txt", "r");
    Stack one, two, three, four, five, six, seven, eight, nine;
    Stack* Stacks[9] = {&one, &two, &three, &four, &five, &six, &seven, &eight, &nine};
    assign_starting_input(Stacks[0], Stacks[1], Stacks[2], Stacks[3], Stacks[4], Stacks[5], Stacks[6], Stacks[7], Stacks[8]);

    for ( ;; ) {
        char line[30];
        fgets(line, 30, fp);
        if (feof( fp )) break;

        split_string_and_assign(line, Stacks);
    }
    if (feof(fp)) {
        printf("1 || %c\n", one.data[one.top]);
        printf("2 || %c\n", two.data[two.top]);
        printf("3 || %c\n", three.data[three.top]);
        printf("4 || %c\n", four.data[four.top]);
        printf("5 || %c\n", five.data[five.top]);
        printf("6 || %c\n", six.data[six.top]);
        printf("7 || %c\n", seven.data[seven.top]);
        printf("8 || %c\n", eight.data[eight.top]);
        printf("9 || %c\n", nine.data[nine.top]);
    }
    fclose(fp);
    return 0;
}