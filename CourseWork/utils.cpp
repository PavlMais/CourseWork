#include <string>
#include <iostream>
#include <windows.h>
#include <algorithm>

#include "utils.h"
#include "data.h"


std::string floatNormalize(float fi) {
	return std::to_string(fi).substr(0, std::to_string(fi).find(".") + 3);
}



// --------- BAD ------------
int sortBy;
bool sortRevers;

bool SortBy(Product const f, Product const s) {
	
	if (sortRevers) {
		switch (sortBy) {
		case 0: return f.id < s.id;
		case 1: return strcmp(f.name.c_str(), s.name.c_str()) > 0;
		case 2: return f.price < s.price;
		default: return false;
		}
	} else {
		switch (sortBy) {
		case 0: return f.id > s.id;
		case 1: return strcmp(f.name.c_str(), s.name.c_str()) < 0;
		case 2: return f.price > s.price;
		default: return false;
		}
	}
}

void sorting(Product* prs, int const prsSize, SortConfing sortConf) {
	sortBy = sortConf.selected;
	sortRevers = sortConf.revers;
	std::sort(prs, prs + prsSize, SortBy); 
}



std::string adaptString(std::string str, int size) {
	if (str.size() > size) str = str.substr(0, size - 2) + "..";
	else  for (unsigned int i = str.size(); i < size; i++) str += " ";
	return str;
}

std::string line(char ch, int size) {
	string str;
	for (int i = 0; i < size; i++) str += ch;
	return str;
}
