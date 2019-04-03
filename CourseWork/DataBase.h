#pragma once
#include "Data.h"

class DataBase
{
public:
	DataBase();

	Data* getData();

	void save(Data*);




	
	~DataBase();
	
private:
	const string PATH_DB = "text.txt";

	Data* parse_data(std::ifstream file);
	Product parse_product(string line);
	User parse_user(string line);
};

