#pragma once

#include<obliv.h>

void dotProd(void *args);

typedef struct vector{
  int size;
  int* arr;
} vector;

typedef struct protocolIO{
  vector input;
  int result;
} protocolIO;
