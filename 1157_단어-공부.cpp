#include <stdio.h>

int main(void)
{
    int alphabet[26] = {0, };
    char word[1000001];

    scanf("%s", word);

    for(int i = 0; word[i]; i++){
        if('a' <= word[i] && word[i] <= 'z'){
            alphabet[word[i] - 'a']++;
        }
        else if('A' <= word[i] && word[i] <= 'Z'){
            alphabet[word[i] - 'A']++;
        }
    }

    int max = 0;
    char max_alpha;

    for(int i = 0; i <= 25; i++){
        if(alphabet[i] > max){
            max = alphabet[i];
            max_alpha = i + 'A';
        }
    }
    for(int i = 0; i <= 25; i++){
        if(max == alphabet[i] && max_alpha != i + 'A'){
            printf("?");
            return 0;
        }
    }
    printf("%c", max_alpha);
    return 0;

}