#include <stdio.h>

#pragma once
void inputArr(int *arr, int n, char *msg) {
  printf("%s", msg);
  for (int i = 0; i < n; i++) {
    scanf("%d", &arr[i]);
  }
}
