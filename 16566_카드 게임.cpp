#include <iostream>
#include <cstring>
using std::cin;
using std::cout;

int* minsooCards;
int* root;

int getRoot(int A) {
    if (root[A] == A) return A;
    else return root[A] = getRoot(root[A]);
}

int upper_bound(int* Cards, int left, int right, int target) {
    if (left == right) return left;
    
    int mid = (left + right) / 2;
    if (target < Cards[mid]) return upper_bound(Cards, left, mid, target);
    else return upper_bound(Cards, mid + 1, right, target);
}

void merge(int* Cards, int left, int mid, int right) {
    int* sorted = new int[right - left + 1];
    
    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right) {
        if (Cards[i] < Cards[j]) {
            sorted[k] = Cards[i++];
        }
        else {
            sorted[k] = Cards[j++];
        }
        k++;
    }
    while (i <= mid) {
        sorted[k++] = Cards[i++];
    }
    while (j <= right) {
        sorted[k++] = Cards[j++];
    }
    
    std::memmove(&Cards[left], sorted, sizeof(int) * (right - left + 1));
    delete[] sorted;
}

void mergeSort(int* Cards, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        
        mergeSort(Cards, left, mid);
        mergeSort(Cards, mid + 1, right);
        merge(Cards, left, mid, right);
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int N, M, K;
    cin >> N >> M >> K;

    minsooCards = new int[M + 1]{};
    root = new int[M + 1]{};
    for (int i = 1; i <= M; i++) {
        cin >> minsooCards[i];
        root[i] = i;
    }
    
    mergeSort(minsooCards, 1, M);
    
    int cheolsooPlays;
    for (int i = 1; i <= K; i++) {
        
        //find
        cin >> cheolsooPlays;
        int pos = getRoot(upper_bound(minsooCards, 1, M, cheolsooPlays));
        cout << minsooCards[pos] << "\n";
        
        //delete
        root[pos] = getRoot(pos + 1);
    }
    
    return 0;
}
