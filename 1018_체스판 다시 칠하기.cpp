#include <stdio.h>

char chessBoard[50][50];
int changed[50][50];

int changed_time(int m, int n);

int main(void)
{
	/*보드 생성*/
	int M, N;
	scanf("%d%*c%d%*c", &M, &N);

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%c", &chessBoard[i][j]);
		}
		getchar();
	}

	/*1st column 체스판 정렬*/
	for (int i = 1; i < M; i++) {
		if (chessBoard[i][0] == chessBoard[i - 1][0]) {
			chessBoard[i][0] = (chessBoard[i - 1][0] == 'B' ? 'W' : 'B');
			changed[i][0] = 1;
		}
	}

	/*나머지 체스판 정렬*/
	for (int i = 0; i < M; i++) {
		for (int j = 1; j < N; j++) {
			if (chessBoard[i][j - 1] == chessBoard[i][j]) {
				chessBoard[i][j] = (chessBoard[i][j - 1] == 'B' ? 'W' : 'B');
				changed[i][j] = 1;
			}
		}
	}

	/*changed 개수로 색칠 횟수 세기*/
	int answer = 64, count = 0;
	for (int m = M - 1; m >= 7; m--) {
		for (int n = N - 1; n >= 7; n--) {
			count = changed_time(m, n);
			if (answer > count) answer = count;
			if (answer > 64 - count) answer = 64 - count;
		}
	}
	printf("%d", answer);
	return 0;
}

int changed_time(int m, int n)
{
	int count = 0;

	for (int i = m; i >= m - 7; i--) {
		for (int j = n; j >= n - 7; j--) {
			if (changed[i][j] == 1)
				count++;
		}
	}

	return count;
}
