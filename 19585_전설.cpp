#include <iostream>
#include <string>
#include <map>
#include <utility>
using std::cin;
using std::cout;
using std::string;
using std::map;

struct Trie {
    bool end;
    map<char, Trie*> next;

    Trie(): end(false) {}

    void free() {
        for (auto it = next.begin(); it != next.end(); it++) {
            it->second->free();
            delete it->second;
        }
        next.clear();
    }
};

Trie *color, *nickname;

void findName(const string& teamName, bool *nicknameStartsAt);

int main(void) {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    color = new Trie;
    nickname = new Trie;

    int C, N, Q;
    cin >> C >> N;

    for (int i = 1; i <= C; i++) {
        Trie* cur = color;
        string input;
        cin >> input;

        for (int i = 0; i < input.size(); i++) {
            if (cur->next.count(input[i]) == 0) {
                cur->next.insert({ input[i], new Trie });
            }
            cur = cur->next.find(input[i])->second;
        }
        cur->end = true;
    }

    for (int i = 1; i <= N; i++) {
        Trie* cur = nickname;
        string input;
        cin >> input;

        for (int i = input.size() - 1; 0 <= i; i--) {
            if (cur->next.count(input[i]) == 0) {
                cur->next.insert({ input[i], new Trie });
            }
            cur = cur->next.find(input[i])->second;
        }
        cur->end = true;
    }

    cin >> Q;
    for (int i = 1; i <= Q; i++) {
        bool found = false;
        string teamName;
        cin >> teamName;

        bool *nicknameStartsAt = new bool[teamName.size()]{};
        findName(teamName, nicknameStartsAt);

        Trie *cur = color;
        for (int i = 0; i < teamName.size() - 1; i++) {
            auto nextIt = cur->next.find(teamName[i]);

            if (nextIt == cur->next.end()) break;
            else {
                cur = nextIt->second; 
                if (cur->end && nicknameStartsAt[i + 1]) {
                    found = true;
                    break;
                }
            }
        }

        if (found) cout << "Yes\n";
        else cout << "No\n";
        delete[] nicknameStartsAt;
    }

    color->free();
    nickname->free();

    delete color, nickname;

    return 0;
}

void findName(const string& teamName, bool *nicknameStartsAt) {
    Trie *cur = nickname;
    for (int i = teamName.size() - 1; 0 <= i; i--) {
        auto nextIt = cur->next.find(teamName[i]);

        if (nextIt == cur->next.end()) break;
        else {
            cur = nextIt->second;
            if (cur->end) nicknameStartsAt[i] = true;
        }
    }
}
