#pragma once

#include<obliv.h>

void testPersonSorter(void* args);

void sum(void* args);

void crossTabs(void* args);

typedef struct person{
  int id;
  int category;
  int data;
} person;

typedef struct result{
  int category;
  int dataSum;
  int count;
} result;

typedef struct protocolIO{
  person *input;  // For A this is categoryList, for B is dataList
  result *results;
  size_t iN;
  size_t *oN;
  size_t nCategories;
} protocolIO;

typedef struct sorterIO{
  person *input;
  person *output;
  size_t *oN;
  size_t iN;
} sorterIO;

