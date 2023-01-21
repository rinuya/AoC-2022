#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static int BUFFSIZE = 100;

typedef struct Point {
    char letter[1];
    int row;
    int col; 
    int dist; // -1 for None
    int value; 
    int visited; // -1 for false, 1 for True
} Point;

typedef struct q_el {
    Point* item;
    struct q_el* next;
} q_el;

void enqueue(q_el* head, Point* p) {
    if (head->item == NULL) {
        head->item = p;
    } else {
        q_el* new;
        new = malloc(sizeof(q_el));
        new->item = p;
        new->next = NULL;
        while (head->next != NULL) {
            head = head->next;
        }
        head->next = new;
    }
}

void dequeue(q_el* head) { 
    if (head->item == NULL) {
        return;
    } else if (head->next == NULL) {
        head->item = NULL;
    } else {
        head->item = head->next->item;
        head->next = head->next->next;
    }  
}

int main () {
    FILE* fp = fopen("input.txt", "r");
    Point* map[BUFFSIZE][BUFFSIZE];
    int start_row; int start_col; int row_counter = 0;

    for ( ;; ) {
        char line[120];
        fgets(line, 120, fp);
        if (feof( fp )) break;

        for (int i = 0; i <= strlen(line); i++) {
            if (line[i] == '\n') { 
                break; 
            } else {
                
                Point* p;
                p = (Point*)malloc(sizeof(Point));
                p->letter[0] = line[i];
                p->row = row_counter;
                p->col = i;
                p->dist = -1;
                p->visited = -1;

                if (line[i] == 'S') {
                    p->value = 1;
                    start_row = row_counter;
                    start_col = i;
                } else if (line[i] == 'E') {
                    p->value = 26;
                } else {
                    p->value = (int)(line[i]) - 96;
                }
                map[row_counter][i] = p;
            }
        }
        row_counter++;
    }
    fclose(fp);

    size_t size = sizeof(map[0]);
    q_el head = { .item = map[start_row][start_col], .next = NULL};
    head.item->visited = 1;
    head.item->dist = 0;

    while (head.item != NULL) {
        Point* current = head.item;
        dequeue(&head);
        if (current->letter[0] == 'E') {
            printf("Distance is %d \n", current->dist);
            break;
        } else {
            Point* point_arr[4]; 
            current->col - 1 >= 0   ? point_arr[0]  = map[current->row][current->col-1] : NULL; // left
            current->col + 1 < size ? point_arr[1]  = map[current->row][current->col+1] : NULL; // right
            current->row - 1 >= 0   ? point_arr[2]  = map[current->row-1][current->col] : NULL; // top
            current->row + 1 < size ? point_arr[3]  = map[current->row+1][current->col] : NULL; // bottom

            for (int i = 0; i < 4; i++) {
                if (point_arr[i] != NULL && point_arr[i]->visited != 1 && point_arr[i]->value - current->value <= 1) {
                    if (point_arr[i]->dist == -1) {
                        point_arr[i]->dist = current->dist +1;
                    }
                    point_arr[i]->visited = 1;
                    enqueue(&head, point_arr[i]);
                }
            }
        }
    }
}