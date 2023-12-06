#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void print_loop(int a, int b) {
	int sum = a + b;
	printf("%d\n", sum);
}

int main(void) {
	int a = 0;
	int b = 0;
	while (1) {
		print_loop(a++, b++);
#ifdef _WIN32
		Sleep(1000);
#else
		sleep(1);
#endif
	}
	return 0;
}
