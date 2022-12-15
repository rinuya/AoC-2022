#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t {
    struct node_t* parent;
    char* name;
    int memory;
    struct node_t* children[100];
    int top;
} node_t;

typedef struct node_stack {
    struct node_t* elements[500];
    int top;
} node_stack;

void create_node(node_t* parent_node, char* str, int memory){
    node_t* new_node;
    new_node = (node_t*)malloc(sizeof(node_t));
    new_node->parent = parent_node;
    new_node->name = strdup(str);
    new_node->memory = memory;
    new_node->top = -1;
    parent_node->top++;
    parent_node->children[parent_node->top] = new_node;
}

void add_file(node_t* target, int memory_inc){
    node_t* new_target = target;
    while ( new_target != NULL) {
        new_target->memory+=memory_inc;
        new_target = new_target->parent;
    }
}

void calculate_result (node_t* ptr, node_stack* options, int cut_out) {
    if (ptr->memory >= cut_out) {
        options->top++;
        options->elements[options->top] = ptr;
    }
    for (int i = 0; i <= ptr->top; i++) {
        calculate_result(ptr->children[i], options, cut_out);
    }
}

int main () {
    FILE* fp = fopen("input.txt", "r");
    node_t root = { .parent = NULL, .name = "/", .memory = 0, .top = -1, };
    char str[255];
    node_t* current_element = &root;
    fgets(str, 255, fp);

    for ( ;; ) {
        fgets(str, 255, fp);
        if (feof( fp )) break;

        if (str[0] == '$') {
            if (str[2] == 'l' && str[3] == 's') {
                continue;
            } else {
                char newStr[10];
                char* p;
                p = strtok(str, " ");
                p = strtok(NULL, " ");
                p = strtok(NULL, " ");
                sscanf(p, "%s", newStr);
                if (newStr[0] == '.' && newStr[1] == '.') {
                    current_element = current_element->parent;
                } else {
                    for (int i = 0; i <= current_element->top; i++) {
                        node_t* loop_node = current_element->children[i];
                        int are_same = strcmp(loop_node->name, newStr);
                        if (are_same == 0){
                            current_element = loop_node;
                            break;
                        }
                    }
                }
            }
        }
        if (isalpha(str[0])) {
            char newStr[20];
            char* p;
            p = strtok(str, " ");
            p = strtok(NULL, " ");
            sscanf(p, "%s", &newStr);
            create_node(current_element, newStr, 0);
        }
        if (isdigit(str[0])) {
            int memory_inc;
            char* p;
            p = strtok(str, " ");
            sscanf(p, "%d", &memory_inc);
            add_file(current_element, memory_inc);
        }
    }
    int cut_out = 30000000 - (70000000 - root.memory);
    node_stack options; 
    options.top = -1;
    calculate_result(&root, &options, cut_out);

    node_t* result = options.elements[0];
    for (int i = 1; i <= options.top; i++) {
        if (result->memory > options.elements[i]->memory) {
            result = options.elements[i];
        }
    }
    printf("result is the pointer %p with a memory of %d\n", result, result->memory);
    fclose(fp);
    return 0;
}