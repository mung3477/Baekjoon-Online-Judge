#include <iostream>
#include <vector>
#include <string>
using std::cin;
using std::cout;
using std::vector;
using std::string;
using std::getline;

vector<int> RSL;    //RepeatedSuffixLength

void fillRSL(const string& pattern);

int main() {
    string T, P;
    getline(cin, T);
    getline(cin, P);

    fillRSL(P);

    int textPointer = 0, patternPointer = 0;
    vector<int> answerIndexes;
    for (textPointer; textPointer < T.length(); textPointer++) {
        //탐색 속행이 가능할 때까지 pattern matching 경우의 수 skip
        while (patternPointer > 0 && T[textPointer] != P[patternPointer]) {
            patternPointer = RSL[patternPointer - 1];
        }

        //이번 pattern matching이 promising한 경우
        if (T[textPointer] == P[patternPointer]) {
            //pattern을 찾은 경우
            if (patternPointer == P.length() - 1) {
                answerIndexes.push_back(textPointer - P.length() + 2);
                patternPointer = RSL[patternPointer];
            }
            //탐색 진행
            else {
                patternPointer += 1;
            }
        }
    }

    cout << answerIndexes.size() << "\n";
    for (auto it = answerIndexes.begin(); it != answerIndexes.end(); it++) {
        cout << *it << " ";
    }

    return 0;
}

void fillRSL(const string& pattern) {
    //RSL[0] = 0
    RSL.push_back(0);

    int fillingPointer = 1, comparingPointer = 0, maxLength = pattern.length();
    for (fillingPointer; fillingPointer < maxLength; fillingPointer++) {
        //pattern 비교가 가능할 때까지 matching 경우의 수 skip
        while (comparingPointer > 0 && pattern[fillingPointer] != pattern[comparingPointer]) {
            comparingPointer = RSL[comparingPointer - 1];
        }

        //비교 진행 가능
        if (pattern[fillingPointer] == pattern[comparingPointer]) {
            RSL.push_back(comparingPointer + 1);    //숫자 개수 = index + 1
            comparingPointer += 1;
        }
        //이번 fillingPointer로 끝나는 suffix는 일치하는 prefix가 없음
        else {
            RSL.push_back(0);
        }
    }
}