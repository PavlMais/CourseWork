#include <string>
#include <iostream>
#include <windows.h>
#include <algorithm>
#include <locale> 

#include "utils.h"
#include "data.h"


std::string floatNormalize(float fi) {
	return std::to_string(fi).substr(0, std::to_string(fi).find(".") + 3);
}

string lineCorsor(int cursor, int size, char fill) {
	return line(fill, cursor) + "^" + line(fill, size - cursor);
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
	if (str.size() > size) str = str.substr(0, size);
	else  for (unsigned int i = str.size(); i < size; i++) str += " ";
	return str;
}

std::string line(char ch, int size) {
	string str;
	for (int i = 0; i < size; i++) str += ch;
	return str;

}

int* searchByTitle(int* ids_items,int* ids_size, std::string str, Product* prds, int prsSize) {
	
	for (int i = 0; i < prsSize; i++) ids_items[i] = 1;
	
	str = strLower(str);

	*ids_size = 0;
	for (int i = 0,n = 0; i < prsSize; i++) {
	
		if (strLower(prds[i].name).find(str, 0) != std::string::npos) {
			ids_items[n] = i;
			n++;
			*ids_size += 1;
		}
	}
		
	return ids_items;
}




string strLower(string str) {
	std::locale loc;

	for (int i = 0; i < str.size(); i++)
		str[i] = std::tolower(str[i], loc);
	
	return str;
}




int limiter(int var, int to, int from) {
	if (var < from) var = from;
	else if (var >= to) var = to - 1;

	return var;
}