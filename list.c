#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

struct List{
    int value;
    struct List *next;
};

struct List *newList(int value){
    struct List *l = malloc(sizeof(struct List));
    l->next = NULL;
    l->value = value;

    return l;
}

void printList(struct List *l){
    printf("[ ");
    
    while(l->next != NULL){
        printf("%d, ", l->value);
        l = l->next;
    }

    printf("%d ]\n", l->value);
}

void addToList(struct List *l, int value){

    while(l->next != NULL){
        l = l->next;
    }

    l->next = malloc(sizeof(struct List));
    l->next->next = NULL;
    l->next->value = value;
}

int getElementAt(struct List *l, int position){
    int iterator = 0;

    while(iterator < position){
        iterator++;
        if(l == NULL){
            printf("Such index do not exists, printing 0...\n");
            return 0;
        }

        l = l->next;
    }

    if(l == NULL){
        printf("Such index do not exists, printing 0...\n");
        return 0;
    }

    return l->value;
}

void deleteElementAt(struct List **l, int position){
    int iterator = 0;
    struct List *prev = NULL;
    struct List *next = NULL;
    struct List *temp = *l;

    while(iterator < position){
        iterator++;
        if(temp == NULL){
            printf("Such index do not exists...\n");
            return ;
        }
        prev = temp;
        temp = temp->next;
    }

    if(temp == NULL){
        printf("Such index do not exists...\n");
        return ;
    }

    if(prev == NULL){
        temp = (*l)->next;
        free(*l);
        *l = temp;
        return ;
    }

    if(temp->next == NULL){
        prev->next = NULL;
        free(temp);
        return ;
    }

    prev->next = temp->next;
    free(temp);
}

struct List *megre(struct List **a, struct List **b){
    struct List *newList = *a;
    struct List *temp = *a;

    while(temp->next != NULL){
        temp = temp->next;
    }

    temp->next = *b;

    *a = NULL;
    *b = NULL;

    return newList;
}

int main(){
    srand(time(NULL));
    
    struct List *list = newList(10);
    addToList(list, 14);
    addToList(list, 120);
    addToList(list, 130);
    addToList(list, 1);

    printList(list);

    printf("%d\n", getElementAt(list, 3));
    printf("%d\n", getElementAt(list, 100));

    deleteElementAt(&list, 4);
    printList(list);

    deleteElementAt(&list, 2);
    printList(list);

    deleteElementAt(&list, 0);
    printList(list);

    struct List *list2 = newList(54);
    addToList(list, 334);
    addToList(list, 1204);
    addToList(list, 1302);
    addToList(list, 11);

    struct List *newL = megre(&list, &list2);

    printList(newL);

    struct List *bigList = newList(rand()%1001);
    int i;
    for(i = 0; i < 999; i++){
        addToList(bigList, rand()%1001);
    }

    double start, end;
    int selected;

    selected = getElementAt(bigList, 512);
    struct timeval  tv1, tv2;

    gettimeofday(&tv1, NULL);
    selected = getElementAt(bigList, 512);
    gettimeofday(&tv2, NULL);

    printf ("Selecting the same element lasts %f seconds\n",
            (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
            (double) (tv2.tv_sec - tv1.tv_sec));

    gettimeofday(&tv1, NULL);
    selected = getElementAt(bigList, rand()%1000);
    gettimeofday(&tv2, NULL);

    printf ("Selecting random element lasts %f seconds\n",
            (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
            (double) (tv2.tv_sec - tv1.tv_sec));

    return 0;
}