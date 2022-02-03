#include <iostream>
#include <string>
#include <map>
using std::cin;
using std::cout;
using std::string;
using std::map;

struct TrieComp {
    inline bool operator()(const string& A, const string& B) const {
        return A < B;
    }
};

struct Trie {
    map<string, Trie*, TrieComp> next;

    Trie(){};
    ~Trie() {
        for(const auto& item : next) {
            delete item.second;
        }
    };

    void insert(const string& s, Trie* retVal) {
        next.insert({s, retVal});
    }

    map<string, Trie*, TrieComp>::iterator find(const string& s) {
        return next.find(s);
    }

    void traverse(int depth) {
        for (const auto& item : next) {
            string depthIndicator(depth * 2, '-');
            cout << depthIndicator << item.first << "\n";
            (item.second)->traverse(depth + 1);
        }
    }
};

int main(void) {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, K;
    string s;
    Trie root;
    cin >> N;
    for (int i = 1; i <= N; i++) {
        Trie *cur = &root;
        
        cin >> K;
        for (int j = 1; j <= K; j++) {
            cin >> s;

            Trie* t = new Trie();
            auto exists = cur->find(s);
            if (exists != cur->next.end()) cur = exists->second;
            else {
                cur->insert(s, t);
                cur = t;
            }
        }
    }

    root.traverse(0);

    return 0;
}
