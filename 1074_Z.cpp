#include <stdio.h>
#include <math.h>

int count = -1;
int r, c;
int Z(int len, int r, int c) 
{
	
	count += (int)(pow(len / 2, 2) * (r > len / 2 ? 2 : 0));
	count += (int)(pow(len / 2, 2) * (c > len / 2 ? 1 : 0));
	
	if (len == 2) return count;
	
	r = r - (r > len / 2 ? len / 2 : 0);
	c = c - (c > len / 2 ? len / 2 : 0);
	
	return Z(len / 2, r, c);
}

int main(void)
{
	int N;
	scanf("%d %d %d", &N, &r, &c);
	
	r += 1;  c += 1;
	
	printf("%d", Z((int)(pow(2, N)), r, c));
}

	
