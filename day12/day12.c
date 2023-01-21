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
    int row_len = 0; int col_len = 0;
    q_el starting_values_head;
    for ( ;; ) {
        char line[120];
        fgets(line, 120, fp);
        if (feof( fp )) break;

        col_len = strlen(line) -1;
        for (int i = 0; i <= strlen(line); i++) {
            if (line[i] == '\n') { 
                break; 
            } else {
                
                Point* p;
                p = (Point*)malloc(sizeof(Point));
                p->letter[0] = line[i];
                p->row = row_len;
                p->col = i;
                p->dist = -1;
                p->visited = -1;

                if (line[i] == 'S' || line[i] == 'a') {
                    p->value = 1;
                    enqueue(&starting_values_head, p);
                } else if (line[i] == 'E') {
                    p->value = 26;
                } else {
                    p->value = (int)(line[i]) - 96;
                }
                map[row_len][i] = p;
            }
        }
        row_len++;
    }
    fclose(fp);

    int solution = BUFFSIZE * BUFFSIZE;

    while (starting_values_head.item != NULL) {
        //clear grid
        for (int row = 0; row < row_len; row++) {
            for (int col = 0; col < col_len; col++) {
                map[row][col]->dist = -1;
                map[row][col]->visited = -1;
            }
        }
        //add Point to queue
        q_el head = { .item = starting_values_head.item, .next = NULL};
        head.item->visited = 1;
        head.item->dist = 0;
        dequeue(&starting_values_head);
        // run BFS search
        while (head.item != NULL) {
            Point* current = head.item;
            dequeue(&head);

            if (current->letter[0] == 'E') {
                if (current->dist < solution) {
                    solution = current->dist;
                }
                break;
            } else {
                Point* point_arr[4]; 
                current->col - 1 >= 0   ? point_arr[0]  = map[current->row][current->col-1] : NULL; // left
                current->col + 1 < col_len ? point_arr[1]  = map[current->row][current->col+1] : NULL; // right
                current->row - 1 >= 0   ? point_arr[2]  = map[current->row-1][current->col] : NULL; // top
                current->row + 1 < row_len ? point_arr[3]  = map[current->row+1][current->col] : NULL; // bottom

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
    printf("Solution: %d", solution);
}

