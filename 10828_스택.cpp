#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/////////////////////////////////////////////
//struct & class definition

typedef struct stackNode {
    int data;
    struct stackNode* prev;
} stackNode;

class stack {
    public: 
        int size;
        stackNode* top;
        stack();
        void push(stackNode* newNode);
        int pop();
        int empty();
        
};
///////////////////////////////////////////////

///////////////////////////////////////////////
//member function implementation
stack::stack(void){
        this->size = 0;
        this->top = NULL;
    }

void stack::push(stackNode* newNode){
    if(top == NULL) {
        top = newNode;
        newNode->prev = NULL;
    }

    else {
        newNode->prev = top;
        top = newNode;
    }
    size++;
}

int stack::pop(void){
    if(top == NULL) {
        return -1;
    }
    else {
        stackNode* del = top;
        int delData = del->data;
        
        top = top->prev;
        
        free(del);
        size--;
        return delData;
    }
}

int stack::empty(void){
    if(top == NULL) { return 1; }
    else { return 0; }
}
////////////////////////////////////////////////

int main(void)
{
    int N;
    scanf("%d", &N);

    stack S;
    char command[10];

    for(int i = 1; i <= N; i++){
        scanf("%s", command);
        
        if(0 == strcmp(command, "push")){
            int C;
            scanf(" %d", &C);
            stackNode* newNode = (stackNode*)malloc(sizeof(stackNode));
            newNode->data = C;
            S.push(newNode);
        }
        else if(0 == strcmp(command, "pop")){
            printf("%d\n", S.pop());
        }
        else if(0 == strcmp(command, "size")){
            printf("%d\n", S.size);
        }
        else if(0 == strcmp(command, "empty")){
            printf("%d\n", S.empty());
        }
        else if(0 == strcmp(command, "top")){
            if(S.empty()) { printf("-1\n"); }
            else { printf("%d\n", S.top->data); }
        }
    }
}