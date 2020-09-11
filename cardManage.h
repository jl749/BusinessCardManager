#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE 20
#define TEL_SIZE 15
#define CARDLIST_SIZE 100

#define SWAP(A,B,C) ((A)=(B),(B)=(C),(C)=(A))

typedef enum {false, true} BOOLEAN; //size of enum=int (false=0,true=1, ...)

typedef struct card{
    char name[NAME_SIZE];
    char company[NAME_SIZE];
    char telephone[TEL_SIZE];
}CARD;

int listSize;

CARD* init_card();
void input_card(CARD* crdList);
int partition(CARD* crdList,int start,int end);
void sortCardList(CARD* crdList,int start,int end);
void save_card(CARD* crdList);
void search(CARD* crdList);
void searchAll(CARD* crdList);
void delCard(CARD* crdList);
