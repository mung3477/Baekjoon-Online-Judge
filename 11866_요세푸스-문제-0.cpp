#include <stdio.h>
#include <stdlib.h>

typedef struct yoseNode{
    int data;
    struct yoseNode* next;
} yoseNode;

int main(void)
{
    int N, K;
    scanf("%d %d", &N, &K);

    int left = N;
    yoseNode* first = (yoseNode*)malloc(sizeof(yoseNode));
    first->data = 1;
    yoseNode* head = first;
    yoseNode* tail = first;
    yoseNode* cur = head;
    
    if(N > 1) {
        for(int i = 2; i <= N - 1; i++) {
            yoseNode* t = (yoseNode*)malloc(sizeof(yoseNode));
            t->data = i;
            cur->next = t;
            cur = cur->next;
            tail = t;
        }

        yoseNode* t = (yoseNode*)malloc(sizeof(yoseNode));
        t->data = N;
        cur->next = t;
        tail = t;
        tail->next = head;
    }

    yoseNode* prev = tail;
    cur = tail;

    printf("<");
    while(left > 1) {
        //move pointer K times
        cur = cur->next;
        for(int i = 2; i <= K; i++){
            cur = cur->next;
            prev = prev->next;
        }

        //Delete the target
        printf("%d, ", cur->data);
        yoseNode* del = cur;
        prev->next = cur->next;
        cur = prev;
        free(del);
        left--;
    }
    printf("%d>", cur->data);
    return 0;
}