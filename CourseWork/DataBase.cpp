#include <iostream>
#include <fstream>
#include "DataBase.h"




DataBase::DataBase()
{
}
DataBase::~DataBase()
{
}

void save(Data* data){
	string strData = data.toString();
	
	std::ofstream file(PATH_DB);
	file << strData;
	file.close();

}

Data* DataBase::getData(){
	std::ifstream file(PATH_DB);

	if (!file.good()) {
		std::cout << "File not exist\nCreate file..";
		std::ofstream file(PATH_DB);
		file << "file txt" << std::endl;
	}
	string buffer;


	Data *data = new Data;
	
	getline(file, buffer);
	data->usersSize = stoi(buffer);
	data->users = new User[data->usersSize];

	for (int i = 0; i < data->usersSize; i++) {
		getline(file, buffer);
		data->users[i] = parse_user(buffer);
	}


	getline(file, buffer);
	data->productsSize = stoi(buffer);
	data->products = new Product[data->productsSize];

	for (int i = 0; getline(file, buffer); i++){
		data->products[i] = parse_product(buffer);
	}

	file.close();
	return data;
}






User DataBase::parse_user(string data) {
	int indx1 = data.find("[n]") + 3;
	int indx2 = data.find("[p]") + 3;
	int indx3 = data.find("[g]") + 3;
	User user;

	user.login = data.substr(0, indx1 - 3);
	user.password = data.substr(indx1, indx2 - indx1 - 3);
	user.group = stoi(data.substr(indx2, indx3 - indx2 - 3));

	return user;
}

Product DataBase::parse_product(string data) {
	int indx1 = data.find("[i]") + 3;
	int indx2 = data.find("[t]") + 3;
	int indx3 = data.find("[n]") + 3;
	int indx4 = data.find("[p]") + 3;
	int indx5 = data.find("[s]") + 3;
	int indx6 = data.find("[l]") + 3;
	int indx7 = data.find("[r]") + 3;
	int indx8 = data.find("[d]") + 3;
	int indx9 = data.find("[c]") + 3;
	Product product;

	product.id       = stoi(data.substr(0, indx1 - 3));
	product.type     = data.substr(5, 7);
	product.name     = data.substr(indx2, indx3 - indx2 - 3);
	product.price    = stof(data.substr(indx3, indx4 - indx3 - 3));
	product.sale     = stoi(data.substr(indx4, indx5 - indx4 - 3));
	product.left_item = stoi(data.substr(indx5, indx6 - indx5 - 3));
	product.rating   = stof(data.substr(indx6, indx7 - indx6 - 3));
	product.description = data.substr(indx7, indx8 - indx7 - 3);
	product.id_company = stoi(data.substr(indx8, indx9 - indx8 - 3));
	return product;
}
