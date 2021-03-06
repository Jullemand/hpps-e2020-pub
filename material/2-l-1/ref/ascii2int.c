#include <stdio.h>
#include <assert.h>

int read_ascii_int(FILE *f, int *out) {
  char c;
  int x = 0;
  while (1) {
    int read = fread(&c, sizeof(c), 1, f);

    if (read == 0) {
      return 1;
    }

    if ('0' <= c && c <= '9') {
      x = x*10 + c - '0';
    } else if (c == '\n') {
      *out = x;
      return 0;
    } else {
      return 1;
    }
  }
}

int main(int argc, char** argv) {
  int x;

  assert(argc == 3);
  FILE *in = fopen(argv[1], "r");
  FILE *out = fopen(argv[2], "w");

  while (read_ascii_int(in, &x) == 0) {
    printf("%d\n", x);
    fwrite(&x, sizeof(int), 1, out);
  }
}
