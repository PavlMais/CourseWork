#pragma once
#include <string>
#include "Data.h"


std::string floatNormalize(float);



void sorting(Product* prs, int prsSize, SortConfing sortConf);

std::string adaptString(std::string, int);

std::string line(char, int);

void sortProducts(Product*, int, SortConfing);
int* searchByTitle(int*, int*, std::string, Product*, int);

string strLower(string str);
int limiter(int, int, int from = 0);

string lineCorsor(int cursor, int size, char fill);