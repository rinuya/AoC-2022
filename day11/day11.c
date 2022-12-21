#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int AMOUNT_OF_MONKEYS = 8;

typedef struct Monkey {
    int id;
    long long int items[50];
    int current_item_index;
    int operation_type; //1 == + ; 2 == * ; 3 == old*old
    int operation_factor; 
    long long int test;
    struct Monkey* true;
    struct Monkey* false;
    int total_inspections;
} Monkey;

void create_monkey(Monkey* new_monkey, int items[8], int operation_type, int operation_factor, int test, Monkey* true, Monkey* false){
    new_monkey->current_item_index = -1;
    for (int i = 0; i < 8; i++){
        if (items[i] != 0){
            new_monkey->current_item_index++;
            long long int value = 0;
            value += items[i];
            new_monkey->items[new_monkey->current_item_index] = value;
        }
    }
    new_monkey->operation_type = operation_type;
    new_monkey->operation_factor = operation_factor;
    new_monkey->test = test;
    new_monkey->true = true;
    new_monkey->false  = false;
    new_monkey->total_inspections = 0;
}

void cycle_items(Monkey* monkey, int modulo){
    int length = monkey->current_item_index;
    for (int i = 0; i <= length; i++){
        monkey->total_inspections++;
        long long int current_item = monkey->items[i];

        if (monkey->operation_type == 1) {
            current_item += monkey->operation_factor;
        } else if (monkey->operation_type == 2) {
            current_item *= monkey->operation_factor;
        } else if (monkey->operation_type == 3) {
            current_item *= current_item;
        }
        current_item = current_item % modulo;
       
        if (current_item % monkey->test == 0){
            monkey->true->current_item_index++;
            monkey->true->items[monkey->true->current_item_index] = current_item;
        } else {
            monkey->false->current_item_index++;
            monkey->false->items[monkey->false->current_item_index] = current_item;
        }
        for (int j = 0; j< monkey->current_item_index; j++){
            monkey->items[i] = monkey->items[i+1];
        }
        monkey->current_item_index--;
    }
}

int main () {
    FILE* fp = fopen("input.txt", "r");
    Monkey monkey_0 = {.id = 0}, monkey_1 = {.id = 1}, monkey_2 = {.id = 2}, monkey_3 = {.id = 3}, monkey_4 = {.id = 4}, monkey_5 = {.id = 5}, monkey_6 = {.id = 6}, monkey_7 = {.id = 7};
    Monkey* monkey_array[] = { &monkey_0, &monkey_1, &monkey_2, &monkey_3, &monkey_4, &monkey_5, &monkey_6, &monkey_7 };
    int modulo = 1;
    for ( ;; ) {
        char line1[10], line2[50], line3[50],line4[50], line5[50], line6[50], line7[50];
        fgets(line1, 50, fp);
        if (feof( fp )) break;

        int id, operation_type, operation_factor, test, true, false, index_for_true_monkey, index_for_false_monkey;
        int items[8] = { 0 };

        sscanf(line1, "Monkey %d", &id);
        fgets(line2, 50, fp);
        char* new_line2 = line2 + 18;
        char* has_comma = strchr(new_line2,', ');
        if (has_comma == NULL) {
            items[0] = atoi(new_line2);
        } else {
            char* token;
            token = strtok(new_line2, ", ");
            int token_index = 0;
            
            while (token != NULL) {
                items[token_index] = atoi(token);
                token_index++;
                token = strtok(NULL, ",");
            }
        }
        fgets(line3, 50, fp);
        if (line3[25] == 'o') {
            operation_type = 3;
            operation_factor = 0;
        } else {
            char operation[1];
            sscanf(line3, "  Operation: new = old %c %d", operation, &operation_factor);
            if (line3[23] == '+'){
                operation_type = 1;
            } else {
                operation_type = 2;
            } 
        }
        fgets(line4, 50, fp);
        sscanf(line4, "  Test: divisible by %d", &test);
        modulo *= test;
        fgets(line5, 50, fp);
        sscanf(line5, "    If true: throw to monkey %d", &true);
        for (int i = 0; i < AMOUNT_OF_MONKEYS; i++){
            if (monkey_array[i]->id == true) {
                index_for_true_monkey = i;
                break;
            }
        }
        fgets(line6, 50, fp);
        sscanf(line6, "    If false: throw to monkey %d", &false);
        for (int i = 0; i < AMOUNT_OF_MONKEYS; i++){
            if (monkey_array[i]->id == false) {
                index_for_false_monkey = i;
                break;
            }
        }
        fgets(line7, 50, fp);
        create_monkey(monkey_array[id], items, operation_type, operation_factor, test, monkey_array[index_for_true_monkey], monkey_array[index_for_false_monkey]);
    }
    fclose(fp);

    for (int round = 0; round < 10000; round++) {
        for (int i = 0; i < AMOUNT_OF_MONKEYS; i++) {
            cycle_items(monkey_array[i], modulo);
        }
    }
    long long int high = 0, sec_high = 0;
    for (int i = 0; i < AMOUNT_OF_MONKEYS; i++){
        if (monkey_array[i]->total_inspections > sec_high) {
            if (monkey_array[i]->total_inspections > high) {
                sec_high = high;
                high = monkey_array[i]->total_inspections;
            } else {
                sec_high = monkey_array[i]->total_inspections;
            }
        }
    }
    printf("Finished %lld\n", high  * sec_high);
    return 0;
}