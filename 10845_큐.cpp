#include <stdio.h>
#include <string.h>
#include <stdlib.h>

///////////////////Declare//////////////////////////
typedef struct queueNode{
    int data;
    struct queueNode* next;
} queueNode;

class queue{
    public:
        int size;
        queueNode* front;
        queueNode* back;
        
        queue(void);
        void push(queueNode* newNode);
        int pop(void);
        int empty(void);
};

////////////////////Definition///////////////////////
queue::queue(void){
    size = 0;
    front = back = NULL;
}

void queue::push(queueNode* newNode){
    //If queue is empty
    if(size == 0){
        front = newNode;
        back = newNode;
        newNode->next = NULL;
    }

    //If queue is already made
    else{
        back->next = newNode;
        newNode->next = NULL;
        back = back->next;
    }

    size += 1;
    return;
}

int queue::pop(void){
    //If queue is empty
    if(empty()) return -1;

    //If queue is not empty
    else{
        int ans = front->data;
        queueNode* del = front;
        front = front->next;
        
        del->next = NULL;
        free(del);
        size--;
        return ans;
    }
}

int queue::empty(void){
    if(size) return 0;
    else return 1;
}

int main(void)
{
    int N;
    scanf("%d", &N);

    char command[6];
    queue q;

    for(int i = 1; i <= N; i++){
        scanf("%s", command);

        if(!strcmp(command, "push")){
            int data;
            scanf(" %d", &data);

            queueNode* newNode = (queueNode*)malloc(sizeof(queueNode));
            newNode->data = data;
            newNode->next = NULL;

            q.push(newNode);
        }
        else if(!strcmp(command, "pop")){
            printf("%d\n", q.pop());
        }
        else if(!strcmp(command, "size")){
            printf("%d\n", q.size);
        }
        else if(!strcmp(command, "empty")){
            printf("%d\n", q.empty());
        }
        else if(!strcmp(command, "front")){
            if(q.empty()) printf("-1\n");
            else printf("%d\n", q.front->data);
        }
        else if(!strcmp(command, "back")){
            if(q.empty()) printf("-1\n");
            else printf("%d\n", q.back->data);
        }
    }
    return 0;
}