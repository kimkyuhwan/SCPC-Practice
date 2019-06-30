#include <cstdio>
int b, cnt;
int main() {
	for (int i = 0; i<3; i++) {
		cnt = 0;
		for (int j = 0; j<4; j++) {
			scanf("%d", &b);
			if (b==0) cnt++;
		}
		if (cnt == 0) puts("E");
		else {
			printf("%c\n", 'A' + (cnt - 1));
		}
	}
}