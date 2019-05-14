#pragma once
#include "Data.h"

class DataBase
{
public:
	Data* getData();
	void save();

	
private:
	const string PATH_DB = "text.txt";
	Data* data;
	Product parse_product(string line);
	User parse_user(string line);
};

