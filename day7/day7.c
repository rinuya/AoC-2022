#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Tree-Nodes need to have following elements 
// Directories:
// 1.:parent    pointer     => Every element has that, If null, you are in / (root)
// 2.:name      char   => Identifying name
// 3.memory     int         => file has static memory, parents of file have ... either (NULL) or sum of child-memory
// 4.children   Node*[]     => Array of pointers to child elements
// 5.top        int         => Top of children array
// write function to add elements to nodes, write function to move in tree (change active element)

typedef struct node_t {
    struct node_t* parent;
    char* name;
    int memory;
    struct node_t* children[100];
    int top;
} node_t;


void create_node(node_t* parent_node, char* str, int memory){
    node_t* new_node;
    new_node = (node_t*)malloc(sizeof(node_t));
    new_node->parent = parent_node;
    // Learning: strdup allocates memory and copies string. use this to copy a string to a 
    // memory allocated struct, otherwise it will use the same address and therefore each 
    // struct will use the same string as their attribute "name"
    new_node->name = strdup(str);
    new_node->memory = memory;
    new_node->top = -1;
    parent_node->top++;
    parent_node->children[parent_node->top] = new_node;
    printf("Added %s (pointer: %p) to %s (pointer: %p)\n", new_node->name, new_node, parent_node->name, parent_node);
}

void add_file(node_t* target, int memory_inc){
    node_t* new_target = target;
    while ( new_target != NULL) {
        printf("Increased %s from %d", new_target->name, new_target->memory);
        new_target->memory+=memory_inc;
        printf(" to %d\n", new_target->memory);
        new_target = new_target->parent;
    }
}

int calculate_result (node_t* root) {
    int max;
    max = 100000;
    int result = 0;
    if (root->memory <= max) {
        result += root->memory;
    }
    for (int i = 0; i <= root->top; i++) {
        result += calculate_result(root->children[i]);
    }
    return result;
}

int main () {
    FILE* fp = fopen("input.txt", "r");

    node_t root = { 
        .parent = NULL, 
        .name = "/",  
        .memory = 0, 
        .top = -1,
    };
    char str[255];
    int result = 0;
    node_t* current_element = &root;
    fgets(str, 255, fp);

    for ( ;; ) {
        fgets(str, 255, fp);
        if (feof( fp )) break;

        if (str[0] == '$') {
            if (str[2] == 'l' && str[3] == 's') {
                continue;
            } else {
                // must be cd
                char newStr[10];
                char* p;
                p = strtok(str, " ");
                p = strtok(NULL, " ");
                p = strtok(NULL, " ");
                sscanf(p, "%s", newStr);
                if (newStr[0] == '.' && newStr[1] == '.') {
                    printf("Going from %s (pointer: %p)", current_element->name, current_element);
                    current_element = current_element->parent;
                    printf(" to %s (pointer: %p) \n", current_element->name, current_element);
                } else {
                    for (int i = 0; i <= current_element->top; i++) {
                        node_t* loop_node = current_element->children[i];
                        int are_same;
                        are_same = strcmp(loop_node->name, newStr);
                        if (are_same == 0){
                            current_element = loop_node;
                            printf("target directory found, switching now to %s", current_element->name);
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
        printf("\n");
    }
    result = calculate_result(&root);
    printf("The result is %d", result);
    fclose(fp);
    return 0;
}