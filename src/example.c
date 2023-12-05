#include <stdio.h>
#include <unistd.h>

void print_loop(int a, int b) {
  int sum = a + b;
  printf("%d\n", sum);
}

int main(void) {
  int a = 0;
  int b = 0;
  while (1) {
    print_loop(a++, b++);
    sleep(1);
  }
  return 0;
}
