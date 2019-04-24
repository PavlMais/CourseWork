#pragma once


#include <string>
using std::string;

struct User {
	string login;
	string password;
	int group;
	string toString(){
		return login + "[l]" + password + "[p]" + std::to_string(group) + "[g]";  
	}
};

struct Product {
	int id;
	string type;
	string name;
	float price = 0;
	int sale = 0;
	int left_item = 0;
	float rating = 0;
	string description;
	int id_company;

	enum Field {TITLE, PRICE, RATING, LEFTITEM, DESCRIPTION};

	string getValue(int field) {
		switch (field) {
		case Field::TITLE: return name;
		case Field::PRICE: return std::to_string(price);
		case Field::RATING: return std::to_string(rating);
		case Field::LEFTITEM: return std::to_string(left_item);
		case Field::DESCRIPTION: return description;
		default: return " ";
		}
	}

	void setValue(int key, string val) {
		switch (key){
		case TITLE: name = val;
			break;
		case PRICE: price = stoi(val);
			break;
		case RATING: rating = stoi(val);
			break;
		case LEFTITEM: left_item = stoi(val);
			break;
		case DESCRIPTION: description = val;
			break;
		default: 
			system("cls");
			std::cout << "Error key: " << key;
			system("pause");
			exit(1);
		}
	}

    string toString(){
        string str = std::to_string(id) + "[i]";
        str += type + "[t]" + name + "[n]";
        str += std::to_string(price) + "[p]";
        str += std::to_string(sale) + "[s]";
        str += std::to_string(left_item) + "[l]";
        str += std::to_string(rating) + "[r]";
        str += description + "[d]";
        str += std::to_string(id_company) + "[c]";
        return str;
    }
};
struct Company {
	int id;
	string name;

};

struct SortConfing {
	enum SortBy { NONE = -1, ID, TITLE, PRICE };
	bool  active = false;
	int selected = -1;
	int select = 0;
	bool revers = false;

};

struct Data {
	Product* products;
	int productsSize;

	int* ids_products;
	int ids_size;

	Product new_product;
	User* users;
	int usersSize;
	User userActive;

	
	
	
	string toString(){
		string str = "";
        str += std::to_string(usersSize) + "\n";
        
        for(int a = 0; a < usersSize; a++) str += users[a].toString() + "\n";
        
        
        str += std::to_string(productsSize) + "\n";
        
        for(int i = 0; i < productsSize; i++) str += products[i].toString() + "\n";   
        
        return str;
	}



	void addProduct()
	{
		Product *newProducts = new Product[productsSize];

		for (int i = 0; i < productsSize; i++)
		{
			newProducts[i] = products[i];
		}
		newProducts[productsSize] = new_product;

		//products = (Product *)realloc(products, productsSize * sizeof(Product) + 1);
		//products[productsSize] = new_product;
		//productsSize += 1;

		delete[] products;

		products = newProducts;
		newProducts = nullptr;

	}

};
