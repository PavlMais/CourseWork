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
	float price;
	int sale;
	int left_item;
	float rating;
	string description;
	int id_company;
	enum Field { TITLE, PRICE, RATING, LEFTITEM, DESCRIPTION };

	string getValue(int field) {
		switch (field) {
		case Field:: TITLE: return name;
		case Field:: PRICE: return std::to_string(price);
		case Field:: RATING: return std::to_string(rating);
		case Field:: LEFTITEM: return std::to_string(left_item);
		case Field:: DESCRIPTION: return description;
		default: return " ";
		}
	}

	void setValue(int key, string val) {


		switch (key)
		{
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
        string str = std::to_string(id) + "[id]";
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
struct Data {
	Product* products;
	Product new_product;
	int productsSize;
	User* users;
	int usersSize;
	User userActive;
	
	
	
	string toString(){
		string str = "";
        str += std::to_string(usersSize) + "\n";
        
        for(int a = 0; a < usersSize; a++){
            str += users[a].toString() + "\n";
        }
        
        str += std::to_string(productsSize) + "\n";
        
        for(int i = 0; i < productsSize; i++){
            str += products[i].toString() + "\n";   
        }
        return str;
  
		
	}

};
