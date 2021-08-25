#include <iostream>
#include <queue>
#include <list>
using std::cin;
using std::cout;
using std::queue;
using std::list;

int main()
{
   std::ios_base::sync_with_stdio(false);
   cin.tie(NULL);
   cout.tie(NULL);
    
   int N, M, howMany, who, truthParty = 0;
   cin >> N >> M;
    
   bool* isInvestigatedPerson = new bool[N + 1]{};    //truthteller queue의 visited 배열
   bool* isInvestigatedParty = new bool[M]{};         //party 중복 순회 방지용 visited 배열
   queue<int> truthteller;                             //사람 순회 frontier.
   list<int>* participated = new list<int>[N + 1];     //idx번 사람이 참가한 파티 목록
   list<int>* participantsOfParty = new list<int>[M];              //해당 파티 참가 명단
   
   //진실 말하는 사람 목록 입력
   cin >> howMany;
   for (int i = howMany; i > 0; i--) {
       cin >> who;
       isInvestigatedPerson[who] = 1;
       truthteller.push(who);
   }
   
   //파티 정보 및 구성원 입력
   for (int i = 0; i < M; i++) {
       cin >> howMany;
       for (int j = 0; j < howMany; j++) {
           cin >> who;
           participantsOfParty[i].push_back(who);
           participated[who].push_back(i);
       }
   }
   
   //진실 말하는 사람 추적
   while (!truthteller.empty()) {
       int curPerson = truthteller.front();
       truthteller.pop();
       
       //그 사람이 갔던 파티 목록 추적
       for (list<int>::iterator it = participated[curPerson].begin(); it != participated[curPerson].end(); it++) {
           //아직 조사되지 않은 파티만 조사
           if (!isInvestigatedParty[*it]) {
               isInvestigatedParty[*it] = true;
               truthParty++;
               
               //그 파티 참가 명단 추적
               for (list<int>::iterator POPit = participantsOfParty[*it].begin(); POPit != participantsOfParty[*it].end(); POPit++) {
                   //조사하지 않은 사람만 frontier에 추가
                   if (!isInvestigatedPerson[*POPit]) {
                       truthteller.push(*POPit);
                       isInvestigatedPerson[*POPit] = true;
                   }
               }
           }
       }
   }
   
   cout << M - truthParty;
   
  
   for (int i = 0; i <= N; i++) {
       participated[i].clear();
   }
   for (int i = 0; i < M; i++) {
       participantsOfParty[i].clear();
   }
   delete[] isInvestigatedPerson, isInvestigatedParty, participated, participantsOfParty;
   
   return 0;
}
