#include <stdio.h>
#include <stdlib.h>

typedef struct character{
    char data;
    struct character* prev;
    struct character* next;
} character;

int main(void)
{
    char t;
    character* head = (character*)malloc(sizeof(character));
    head->data = '[';
    head->prev = head->next = NULL;
    character* cur = head;
    while((t = getchar()) != '\n'){
        character* New = (character*)malloc(sizeof(character));
        New->data = t;
        New->prev = cur;
        New->next = NULL;
        if(cur) cur->next = New;
        cur = New;
    }

    int M;
    scanf(" %d", &M);


    for(int i = 1; i <= M; i++){
        
        /*printf("%c\n", cur->data);
        character* trav = head->next;
        while(trav){
            printf("%c", trav->data);
            trav = trav->next;
        }
        printf("\n");*/

        char c;
        scanf(" %c", &c);
        switch(c){
            case 'L':{
                if(cur->prev) cur = cur->prev;
                break;
            }
            case 'D':{
                if(cur->next) cur = cur->next;
                break;
            }
            //가리키는 노드 삭제
            case 'B':{
                if(cur->prev) {
                    character* del = cur;
                    cur = del->prev;
                    if(del->prev) del->prev->next = del->next;
                    if(del->next) del->next->prev = del->prev;
                    del->prev = del->next = NULL;
                    free(del);
                }
                break;
            }
            //가리키는 노드 뒤에 추가
            case 'P':{
                char N;

                scanf(" %c", &N);

                //printf("%c\n", N);

                character* newNode = (character*)malloc(sizeof(character));
                newNode->data = N;
                newNode->prev = cur;
                if(cur->next){
                    newNode->next = cur->next;
                    cur->next->prev = newNode;
                }
                cur->next = newNode;
                cur = cur->next;
                break;
            }
        }
    }
    character* trav = head->next;
    while(trav){
        printf("%c", trav->data);
        trav = trav->next;
    }
}