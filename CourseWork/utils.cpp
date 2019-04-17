#include <string>
#include <iostream>
#include <algorithm>
#include "utils.h"
#include "data.h"
using namespace std;

std::string floatNormalize(float fi)
{
	return std::to_string(fi).substr(0, std::to_string(fi).find(".") + 3);
}



void sortProducts(Product* prs,int prsSize, SortConfing sortConf) {
	if (sortConf.selected == 0) {
		std::sort(prs, prs + prsSize);
	}
}


std::string adaptString(std::string str, int size) {
	//std::cout << str.size() << " " << size << " | ";
	if (str.size() > size) str = str.substr(0, size - 2) + "..";
	else  for (unsigned int i = str.size(); i < size; i++) str += " ";
	//std::cout << str.size() << " == ";
	return str;
}

std::string line(char ch, int size)
{
	string str;
	for (int i = 0; i < size; i++) str += ch;
	return str;
}
