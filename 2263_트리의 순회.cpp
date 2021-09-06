#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::vector;

int find(vector<int>& data, int left, int right, int target) {
    for (int i = left; i <= right; i++) {
        if (data.at(i) == target) {
            return i;
        }
    }
}

//[left, right]
void preOrder(vector<int>& inOrder, int inLeft, int inRight, vector<int>& postOrder, int postLeft, int postRight) {
    int root = postOrder.at(postRight);
    int inRoot = find(inOrder, inLeft, inRight, root);
    
    bool hasLeftSub = (inLeft != inRoot);
    bool hasRightSub = (inRoot - inLeft != postRight - postLeft);
    
    int rightSubPostLeft = postLeft + (inRoot - inLeft);
    
    //cout << root << left subtree preorder << right subtree preorder
    //tree Inorder = inLeft ~ inRoot - 1 / inRoot / inRoot + 1 ~ inRight
    //tree postOrder = postLeft ~ postLeft + leftSubSize - 1 / postLeft + leftSubSize ~ postRight - 1/ postRight
    cout << root; 
    
    //왼쪽 subtree가 있다면
    if (hasLeftSub) {
        cout << " ";
        preOrder(inOrder, inLeft, inRoot - 1, postOrder, postLeft, rightSubPostLeft - 1); 
    }
    
    //오른쪽 subtree가 있다면
    if (hasRightSub) {
        cout << " ";
        preOrder(inOrder, inRoot + 1, inRight, postOrder, rightSubPostLeft, postRight - 1);
    }
}

int main()
{
   std::ios_base::sync_with_stdio(false);
   cin.tie(NULL);
   cout.tie(NULL);
   
   int N, input;
   cin >> N;
   
   vector<int> inOrder;
   vector<int> postOrder;
   
   for (int i = 0; i < N; i++) {
       cin >> input;
       inOrder.push_back(input);
   }
   for (int i = 0; i < N; i++) {
       cin >> input;
       postOrder.push_back(input);
   }
   
   preOrder(inOrder, 0, N - 1, postOrder, 0, N - 1);
   
   return 0;
}
