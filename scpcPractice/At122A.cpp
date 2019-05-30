#include <cstdio>
char ch;
int main() {
	scanf("%c", &ch);
	if (ch == 'A') ch = 'T';
	else if (ch == 'T') ch = 'A';
	else if (ch == 'G') ch = 'C';
	else if (ch == 'C') ch = 'G';
	printf("%c\n", ch);
}