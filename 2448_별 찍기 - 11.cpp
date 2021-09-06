#include <iostream>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::string;
using std::vector;

int main()
{
   std::ios_base::sync_with_stdio(false);
   cin.tie(NULL);
   cout.tie(NULL);
   
   vector<string> pattern;
   int N, entire, j = 0, threshold = 3;
   cin >> N;
   
   entire = 2 * N - 1;
   
   for (int h = 1; h <= N; h++) {
        string curPattern = "";
        string outerBlank(N - h, ' ');
        
        cout << outerBlank;
           
        if (h == 1) {
            cout << "*";
            pattern.push_back("*");
        } 
        else if (h == 2) {
            cout << "* *";
            pattern.push_back("* *");
        }
        else if (h == 3) {
            cout << "*****";
            pattern.push_back("*****");
        }
        
        else {
            string innerBlank(entire - 2 * (outerBlank.length() + pattern.at(j).length()), ' ');
            
            curPattern = pattern.at(j) + innerBlank + pattern.at(j);
            cout << curPattern;
            pattern.push_back(curPattern);
            
            j++;
            if (j == threshold) {
                j = 0;
                threshold *= 2;
            }
        }
        
        cout << outerBlank;
        cout << "\n";
   }
   
   
   return 0;
}
