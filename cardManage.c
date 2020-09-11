#include "cardManage.h"

CARD* init_card(){
    FILE* fp=fopen("namecard.txt","rb");
    if(fp==NULL){
        puts("cannot read namecard.txt");
        return -1;
    }

    CARD buf; int index=0;
    CARD* crdList=(CARD*)malloc(sizeof(CARD)*CARDLIST_SIZE);
    while(fread((void*)&buf,sizeof(buf),1,fp)!=0){ // sizeof(buf)바이트 데이터 1개를 fp로부터 읽어서 buf에 저장
        crdList[index]=buf; index++;                 // while(!feof(fp))는 틀림 in order to trigger feof pinter need to pass EOF https://stackoverflow.com/questions/5431941/why-is-while-feof-file-always-wrong
    }
    listSize=index;
    fclose(fp);
    puts("data loaded sucessfully");
    return crdList;
}

void input_card(CARD* crdList){
    CARD c;
    fputs("name-> ",stdout);fgets(c.name,NAME_SIZE,stdin);
    fputs("company-> ",stdout);fgets(c.company,NAME_SIZE,stdin);
    fputs("telephone-> ",stdout);fgets(c.telephone,TEL_SIZE,stdin);
    crdList[listSize]=c; //listSize = end index+1
    listSize++;
    printf("updated listSize: %d\n",listSize);
}


/**quick sort algorithm*/
int partition(CARD* crdList,int start,int end){
    char pivot[NAME_SIZE];
    strcpy(pivot,crdList[end].name); //take last index element as pivot

    int swapIndex=start;
    int i;  CARD tmp;
    for(i=start;i<end;i++){
        if(strcmp(pivot,crdList[i].name)>0){ //when pivot is bigger than crdList[i].name
            SWAP(tmp,crdList[i],crdList[swapIndex]);
            swapIndex++;
        }
    }
    SWAP(tmp,crdList[swapIndex],crdList[end]);
    return swapIndex; //this is where pivot is now
}
void sortCardList(CARD* crdList,int start,int end){ //recursive method
    if(start<end){
        int pivot=partition(crdList,start,end);
        sortCardList(crdList,pivot+1,end);
        sortCardList(crdList,start,pivot-1);
    }
}

void save_card(CARD* crdList){
    sortCardList(crdList,0,listSize-1); //sort cardList before saving
    FILE* fp=fopen("namecard.txt","wb");
    if(fp==NULL){
        puts("cannot read namecard.txt");
        return -1;
    }

    fwrite((void*)crdList,sizeof(CARD),listSize,fp);
    fclose(fp);
}

void search(CARD* crdList){
    char name[NAME_SIZE]; fputs("name to search-> ",stdout);
    fgets(name,NAME_SIZE,stdin); //scanf 쓰면 띄어쓰기 불가능

    int i;
    for(i=0;i<=listSize-1;i++){
        if(strncmp(crdList[i].name,name,NAME_SIZE)==0){
            printf("At index:%d\ncompany->%stel->%s\n",i,crdList[i].company,crdList[i].telephone);
            return;
        }
    }
    puts("NO CARD FOUND\n");

    /** BINARY SEARCH (ONLY WHEN LIST IS SORTED)
    int start=0, end=listSize-1, mid;
    while(start<=end){
        mid=(start+end)/2;
        if(strcmp(name,crdList[mid].name)>0){ //when name is bigger than crdList[mid].name
            start=mid+1;
        }else if(strcmp(name,crdList[mid].name)<0){
            end=mid-1;
        }else{
            printf("At Index:%d\ncompany->%stel->%s\n",mid,crdList[mid].company,crdList[mid].telephone);
            return;
        }
    }
    puts("NO CARD FOUND\n"); */
}

void searchAll(CARD* crdList){
    char name[NAME_SIZE]; fputs("name to search-> ",stdout);
    fgets(name,NAME_SIZE,stdin);

    int i; BOOLEAN b=false;
    for(i=0;i<=listSize-1;i++){
        if(strncmp(crdList[i].name,name,NAME_SIZE)==0){
            b=true;
            printf("At index:%d\ncompany->%stel->%s\n",i,crdList[i].company,crdList[i].telephone);
        }
    }
    if(!b){puts("NO CARD FOUND\n");}
}

void delCard(CARD* crdList){ //search card then delete
    char name[NAME_SIZE]; fputs("card name to delete-> ",stdout);
    fgets(name,NAME_SIZE,stdin);

    int i;
    for(i=0;i<=listSize-1;i++){
        if(strncmp(crdList[i].name,name,NAME_SIZE)==0){
            for(i;i<=listSize-1;i++){
                crdList[i]=crdList[i+1];
            }
            listSize--;
            printf("updated listSize: %d\n",listSize);
            return;
        }
    }
    puts("NO CARD FOUND\n");
}
