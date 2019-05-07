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
	return line(fill, cursor) + char(223) + line(fill, size - cursor);
}

bool checkProduct(Product pr)
{
	if (pr.id == 0
		|| pr.name == ""
		|| pr.type == ""
		|| pr.description == ""
		|| pr.rating == 0
		|| pr.price == 0
		|| pr.left_item == 0
		) return false;
	else return true;
}

// --------- BAD ------------
int sortBy;
bool sortRevers;
Product*  prds;

bool SortBy(int const f, int const s) {
	
	if (sortRevers) {
		switch (sortBy) {
		case 0: return prds[f].id < prds[s].id;
		case 1: return strcmp(prds[f].name.c_str(), prds[f].name.c_str()) > 0;
		case 2: return prds[f].price < prds[f].price;
		default: return false;
		}
	} else {
		switch (sortBy) {
		case 0: return prds[f].id > prds[s].id;
		case 1: return strcmp(prds[f].name.c_str(), prds[f].name.c_str()) < 0;
		case 2: return prds[f].price > prds[f].price;
		default: return false;
		}
	}
}

void sorting(int* ids_products, int ids_size, Product* prs, int const prsSize, SortConfing sortConf) {
	sortBy = sortConf.selected;
	sortRevers = sortConf.revers;
	prds = prs;

	std::sort(ids_products, ids_products + ids_size, SortBy);
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




int limiter(int var, int to, int from)
{
	if (var < from) var = from;
	else if (var >= to) var = to - 1;
	return var;
}


bool isDigit(string str) {
	std::locale loc;
	for (int i = 0; i < str.size(); i++)
	{
		if (!std::isdigit(str[i], loc)) return false;
	}

	return true;


}