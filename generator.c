#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int f(char t[]){
  if (strcmp(t, "al")==0) return 0;
  if (strcmp(t, "cl")==0) return 1;
  if (strcmp(t, "dl")==0) return 2;
  if (strcmp(t, "bl")==0) return 3;

  if (strcmp(t, "ah")==0) return 4;
  if (strcmp(t, "ch")==0) return 5;
  if (strcmp(t, "dh")==0) return 6;
  if (strcmp(t, "bh")==0) return 7;

  if (strcmp(t, "ax")==0) return 0;
  if (strcmp(t, "cx")==0) return 1;
  if (strcmp(t, "dx")==0) return 2;
  if (strcmp(t, "bx")==0) return 3;

  if (strcmp(t, "sp")==0) return 4;
  if (strcmp(t, "bp")==0) return 5;
  if (strcmp(t, "si")==0) return 6;
  if (strcmp(t, "di")==0) return 7;

  if (strcmp(t, "es")==0) return 0;
  if (strcmp(t, "cs")==0) return 1;
  if (strcmp(t, "ss")==0) return 2;
  if (strcmp(t, "ds")==0) return 3;

  return 200;
}

int isword(char t[]){
  if (t[1]=='x' || t[1]=='p' || t[1]=='i' ) return 1;
  return 0;
}
int isint(char* a){
  if (a[0]<='9') return 1;
  return 0;
}
int isseg(char* a){
  if (a[1]=='s') return 1;
  return 0;
}
int ismem(char* a){
  if (a[0]=='[') return 1;
  return 0;
}

int main(void) {
 
  FILE *fp, *inpF;
  char t[10], u[10], v[10];
  int i = 0, g, sy[200];
  
  printf("Give filename: ");
  scanf("%s", t);
  //printf("Hello\n");
  inpF = fopen( t, "r");
  fscanf(inpF, "%s", t);
  fscanf(inpF, "%s", t);
  fscanf(inpF, "%s", t);
  printf("%s\n", t);
  fp = fopen("t2", "w");

  for (i = 0; i < 200; i++)   sy[i] = -1;
  
  do {
    fscanf(inpF, "%s", t);
    if (t[1] == ':') sy[t[0]] = i;
    if (strcmp(t, "int") == 0) {
      fscanf(inpF, "%d", &g);
      i = i+2;
      fprintf(fp, "205\n");
      fprintf(fp, "%d\n", g);
    }
    if (strcmp(t, "jc") == 0) {
      fscanf(inpF, "%s", u);
      i = i+2;
      fprintf(fp, "114\n");
      fprintf(fp, "%d\n", sy[u[0]] - i);
    }
    if (strcmp(t, "jmp") == 0) {
      fscanf(inpF, "%s", u);
      i = i+2;
      fprintf(fp, "235\n");
      fprintf(fp, "%d\n", sy[u[0]] - i);
    }
    if (strcmp(t, "jl") == 0) {
      fscanf(inpF, "%s", u);
      i = i+2;
      fprintf(fp, "124\n");
      fprintf(fp, "%d\n", sy[u[0]] - i);
    }
    if (strcmp(t, "add") == 0) {
      fscanf(inpF, "%s%d", u, &g);
      i = i+3;
      fprintf(fp, "128\n");
      fprintf(fp, "%d\n", 192 + f(u));
      fprintf(fp, "%d\n", g);
    }
    if (strcmp(t, "cmp") == 0) {
      fscanf(inpF, "%s%d", u, &g);
      i = i+3;
      fprintf(fp, "128\n");
      fprintf(fp, "%d\n", 248 + f(u));
      fprintf(fp, "%d\n", g);
    }
    if (strcmp(t, "mov") == 0) {
      fscanf(inpF, "%s%s", u, v);
      i = i+2;
      if (f(v) < 200) {
        fprintf(fp, "138\n");
        fprintf(fp, "%d\n", 192 + 8*f(u) + f(v));
      }
      else {
        fprintf(fp, "%d\n", 176 + f(u));
        fprintf(fp, "%d\n", atoi(v));
      }
    }
  } while (strcmp(t, "end") != 0);
  fprintf(fp, "\n");
  return 0;
}