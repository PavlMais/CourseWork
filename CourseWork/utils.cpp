#include "utils.h"
#include <string>
#include <iostream>
using namespace std;

std::string floatNormalize(float fi)
{
	return std::to_string(fi).substr(0, std::to_string(fi).find(".") + 3);
}



std::string adaptString(std::string str, int size) {

	if (str.size() > size) str = str.substr(0, size - 2) + "..";
	else  for (unsigned int i = str.size(); i < size; i++) str += " ";	
	return str;
}
