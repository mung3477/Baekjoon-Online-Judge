#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode{
    char data;
    int right;
    int left;
}treeNode;

//arr 배열에 노드 기록
//left와 right는 그 노드의 index in array를 저장
void makeTree(treeNode* arr)
{
    char par, left, right;
    scanf(" %c %c %c", &par, &left, &right);

    arr[par - 'A'].data = par;
    arr[par - 'A'].left = (left != '.' ? left - 'A' : -1);
    arr[par - 'A'].right = (right != '.' ? right - 'A' : -1);
}

void preorder(treeNode* arr, int cur)
{   
    if(cur >= 0){
        printf("%c", arr[cur].data);
        preorder(arr, arr[cur].left);
        preorder(arr, arr[cur].right);
    }
}

void inorder(treeNode* arr, int cur)
{
    if(cur >= 0){
        inorder(arr, arr[cur].left);
        printf("%c", arr[cur].data);
        inorder(arr, arr[cur].right);
    }
}

void postorder(treeNode* arr, int cur)
{
    if(cur >= 0){
        postorder(arr, arr[cur].left);
        postorder(arr, arr[cur].right);
        printf("%c", arr[cur].data);
    }
}

int main(void)
{
    int N;
    scanf(" %d", &N);

    treeNode arr[26];
    for(int i = 1; i <= N; i++){
        makeTree(arr);
    }

    preorder(arr, 0);
    printf("\n");
    inorder(arr, 0);
    printf("\n");
    postorder(arr, 0);
}