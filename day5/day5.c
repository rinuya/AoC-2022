#include <stdio.h>
#include <string.h>

typedef struct Stack {
    char data[50];
    int top;
} Stack;

void push_on_stack(Stack* target, char value) {
    target->top++;
    target->data[target->top] = value;
}

char pop_from_stack(Stack* target) {
    if (target->top < 0) {
        printf("Error, stack is empty\n\n\n");
        return -1;
    }
    target->top--;
    return target->data[target->top+1];
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

    printf("We move %d from the struct %d to the struct %d\n", amt, int_from, int_to);
    // printf("Check if I can access the stack: 1 element 3 : %c\n", stacks[0]->data[2]);
    for (int i = 0; i < amt; i++) {
        char value[1];
        value[0] = pop_from_stack(stacks[int_from-1]);
        printf("Popped value %c\n", value[0]);
        push_on_stack(stacks[int_to-1], value[0]);
    }
}

void assign_starting_input (Stack* one, Stack* two, Stack* three, Stack* four, Stack* five, Stack* six, Stack* seven, Stack* eight, Stack* nine) {
    char arr_one[4] = {'H', 'T', 'Z', 'D'};
    one->top = -1;
    for (int i=0; i < sizeof(arr_one); i++) {
        push_on_stack(one, arr_one[i]);
    }
    char arr_two[7] = {'Q', 'R', 'W', 'T', 'G', 'C', 'S'};
    two->top = -1;
    for (int i=0; i < sizeof(arr_two); i++) {
        push_on_stack(two, arr_two[i]);
    }
    char arr_three[8] = {'P', 'B', 'F', 'Q', 'N', 'R', 'C', 'H'};
    three->top = -1;
    for (int i=0; i < sizeof(arr_three); i++) {
        push_on_stack(three, arr_three[i]);
    }
    char arr_four[6] = {'L', 'C', 'N', 'F', 'H', 'Z'};
    four->top = -1;
    for (int i=0; i < sizeof(arr_four); i++) {
        push_on_stack(four, arr_four[i]);
    }
    char arr_five[5] = {'G', 'L', 'F', 'Q', 'S'};
    five->top = -1;
    for (int i=0; i < sizeof(arr_five); i++) {
        push_on_stack(five, arr_five[i]);
    }
    char arr_six[8] = {'V', 'P', 'W', 'Z', 'B', 'R', 'C', 'S'};
    six->top = -1;
    for (int i=0; i < sizeof(arr_six); i++) {
        push_on_stack(six, arr_six[i]);
    }
    char arr_seven[3] = {'Z', 'F', 'J'};
    seven->top = -1;
    for (int i=0; i < sizeof(arr_seven); i++) {
        push_on_stack(seven, arr_seven[i]);
    }
    char arr_eight[7] = {'D', 'L', 'V', 'Z', 'R', 'H', 'Q'};
    eight->top = -1;
    for (int i=0; i < sizeof(arr_eight); i++) {
        push_on_stack(eight, arr_eight[i]);
    }
    char arr_nine[8] = {'B', 'H', 'G', 'N', 'F', 'Z', 'L', 'D'};
    nine->top = -1;
    for (int i=0; i < sizeof(arr_nine); i++) {
        push_on_stack(nine, arr_nine[i]);
    }
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
        printf("solution %c:%c:%c:%c:%c:%c:%c:", pop_from_stack(&one),  pop_from_stack(&two),  pop_from_stack(&three),  pop_from_stack(&four),  pop_from_stack(&five),  pop_from_stack(&six),  pop_from_stack(&seven));
        printf("%c:%c\n", pop_from_stack(&eight), pop_from_stack(&nine));
    }
    fclose(fp);
    return 0;
}