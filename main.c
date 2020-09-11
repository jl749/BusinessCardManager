#include "cardManage.h"

int main()
{
    CARD* crdList=init_card();printf("listSize: %d\n",listSize);
    puts("BUSINESS_CARD MANAGER");
    puts("1.Insert New");
    puts("2.Delete");
    puts("3.Search");
    puts("4.Search All");
    puts("5.Terminate");
    int slct;
    while(slct!=5){
        scanf("%d%*c",&slct);
        switch(slct){
            case 1:
                input_card(crdList);
                break;
            case 2:
                delCard(crdList);
                break;
            case 3:
                search(crdList);
                break;
            case 4:
                searchAll(crdList);
                break;
        }
    }
    save_card(crdList);
    free(crdList);
    return 0;
}
