#pragma once


#include <string>
using std::string;

struct User {
	string login;
	string password;
	int group;
};

struct Product {
	int id;
	string type;
	string name;
	float price;
	int sale;
	int left_item;
	float rating;
	string description;
	int id_company;
};
struct Company {
	int id;
	string name;

};
struct Data {
	Product* products;
	int productsSize;
	User* users;
	int usersSize;
	User userActive;

};
