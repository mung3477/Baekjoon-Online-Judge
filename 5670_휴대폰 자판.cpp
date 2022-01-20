#include <iostream>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::string;
using std::getline;
using std::vector;

struct TrieNode {
    TrieNode** next;
    int prefixFor;

    TrieNode(): prefixFor(0) {
        next = new TrieNode*[27]{};
    };

    void clear() {
        if (next[26]) prefixFor -= 1;

        for (int i = 0; i <= 25 && prefixFor; i++) {
            if (next[i]) {
                next[i]->clear(); 
                prefixFor -= 1;
                delete next[i];
            }
        }
        delete[] next;
    }
};

int main(void) {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cout << std::fixed;
    cout.precision(2);

    int N;
    vector<string> dictionary;

    while (cin >> N) {
        cin.ignore();

        TrieNode start;
        for (int i = 1; i <= N; i++) {
            string word;
            getline(cin, word);
            dictionary.emplace_back(word);

            TrieNode* cur = &start;
            // create trie
            for (char c : word) {
                if (!cur->next[c - 'a']) {
                    cur->next[c - 'a'] = new TrieNode();
                    cur->prefixFor += 1;
                }
                cur = cur->next[c - 'a'];
            }

            //mark END
            cur->next[26] = cur;
            cur->prefixFor += 1;
        }

        //type word
        int pressed = 0;
        for (int i = 0; i < N; i++) {
            TrieNode* cur = &start;
            for (char c : dictionary[i]) {
                //auto complete 불가
                if (cur->prefixFor > 1 || cur == &start) pressed += 1;
                cur = cur->next[c - 'a'];
            }
        }

        cout << (double)pressed / N << "\n";

        start.clear();
        dictionary.clear();
    }

    return 0;
}

