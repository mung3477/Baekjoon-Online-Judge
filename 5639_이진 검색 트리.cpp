#include <iostream>
#include <algorithm>
#include <vector>
using std::cin;
using std::cout;
using std::sort;
using std::vector;

int find(vector<int>& vec, int left, int right, int target) {
    for (int i = left; i <= right; i++) {
        if (vec.at(i) == target) {
            return i;
        }
    }
}

void postOrder(vector<int>& preOrder, int preLeft, int preRight, vector<int>& inOrder, int inLeft, int inRight) {
    int root = preOrder.at(preLeft);
    int inRoot = find(inOrder, inLeft, inRight, root);
    
    //has left subtree
    if (inRoot != inLeft) {
        postOrder(preOrder, preLeft + 1, (preLeft + 1) + (inRoot - inLeft) - 1, inOrder, inLeft, inRoot - 1);
    }
    
    //has right subtree
    if (inRoot != inRight) {
        postOrder(preOrder, (preLeft + 1) + (inRoot - inLeft), preRight, inOrder, inRoot + 1, inRight);
    }
    
    cout << root << " ";
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int input;
    vector<int> preOrder;
    vector<int> inOrder;
    
    while (cin >> input) {
        preOrder.push_back(input);
        inOrder.push_back(input);
    }
    
    sort(inOrder.begin(), inOrder.end());
    
    postOrder(preOrder, 0, preOrder.size() - 1, inOrder, 0, inOrder.size() - 1);
    
    return 0;
}
