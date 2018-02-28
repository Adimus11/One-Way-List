#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

struct List{
    int size;
    struct Node *start;
};

struct Node{
    int value;
    struct Node *next;
};

struct List *newList(){
    struct List *l = malloc(sizeof(struct List));
    l->start = NULL;
    l->size = 0;

    return l;
}

void addToList(struct List *l, int value){
    struct Node *temp = l->start;

    if(l->size == 0){
        l->start = malloc(sizeof(struct Node));
        l->start->value = value;
        l->start->next = NULL;
        l->size = 1;
    }
    else{

        while(temp->next != NULL){
            temp = temp->next;
        }

        temp->next = malloc(sizeof(struct List));
        temp->next->next = NULL;
        temp->next->value = value;
        l->size++;
    }
}

int getElementAt(struct List *l, int position){
    int iterator = 0;
    if(position >= l->size){
        printf("Such index do not exists, printing 0...\n");
            return 0;
    }

    struct Node *temp = l->start;

    while(iterator < position){
        iterator++;
        temp = temp->next;
    }

    return temp->value;
}

void deleteElementAt(struct List *l, int position){
    int iterator = 0;

    if(position >= l->size){
        printf("Such index do not exists...\n");
            return ;
    }

    if(position == 0){
        struct Node *temp = l->start;
        l->start = temp->next;
        l->size--;
        free(temp);
        return ;
    }

    struct Node *temp = l->start;
    struct Node *prev = NULL;

    while(iterator < position){
        iterator++;
        prev = temp;
        temp = temp->next;
    }

    prev->next = temp->next;
    l->size--;
    free(temp);
}

int getElementPosition(struct List *l, int element){

    if(l->size == 0){
        printf("List is empty...\n");
        return -1;
    }

    struct Node *temp = l->start;
    int iterator = 0;

    while(temp->value != element){
        temp = temp->next;
        iterator++;
        if(temp == NULL){
            printf("Such element does not ezists...\n");
            return -1;
        }
    }

    return iterator;
}

void printList(struct List *l){
    struct Node *temp = l->start;
    printf("[ ");
    
    while(temp->next != NULL){
        printf("%d, ", temp->value);
        temp = temp->next;
    }

    printf("%d ]\n", temp->value);
}

struct List *megre(struct List *a, struct List *b){
    struct List *cList = newList();
    struct Node *temp = a->start;

    while(temp != NULL){
        addToList(cList, temp->value);
        temp = temp->next;
    }

    temp = b->start;

    while(temp != NULL){
        addToList(cList, temp->value);
        temp = temp->next;
    }

    return cList;
}

int main(){
    srand(time(NULL));
    
    struct List *list = newList();
    addToList(list, 14);
    addToList(list, 120);
    addToList(list, 130);
    addToList(list, 1);

    printf("Element selection test:\n");
    printList(list);

    printf("%d\n", getElementAt(list, 3));
    printf("%d\n", getElementAt(list, 100));

    printf("Delete test:\n");

    deleteElementAt(list, 4);
    printList(list);

    deleteElementAt(list, 2);
    printList(list);

    deleteElementAt(list, 0);
    printList(list);

    struct List *list2 = newList();
    addToList(list2, 334);
    addToList(list2, 1204);
    addToList(list2, 1302);
    addToList(list2, 11);

    printf("Index selection test:\n");
    printf("%d\n", getElementPosition(list2, 334));
    printf("%d\n", getElementPosition(list2, 11));
    printf("%d\n", getElementPosition(list2, 69));

    struct List *newL = megre(list, list2);

    printList(newL);

    struct List *bigList = newList();
    int i;
    for(i = 0; i < 1000; i++){
        addToList(bigList, rand()%1001);
    }

    double start, end;
    int selected;
    struct timeval  tv1, tv2;

    gettimeofday(&tv1, NULL);
    for(i = 0; i < 1000; i++){
        selected = getElementAt(bigList, 512);
    }
    gettimeofday(&tv2, NULL);

    printf ("Selecting the same element lasts %f seconds\n",
            (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
            (double) (tv2.tv_sec - tv1.tv_sec));

    gettimeofday(&tv1, NULL);
    for(i = 0; i < 1000; i++){
        selected = getElementAt(bigList, rand()%1000);
    }
    gettimeofday(&tv2, NULL);

    printf ("Selecting random element lasts %f seconds\n",
            (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +
            (double) (tv2.tv_sec - tv1.tv_sec));

    return 0;
}