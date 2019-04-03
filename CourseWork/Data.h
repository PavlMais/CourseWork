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
    
	string getValue(string key) {
		if (key == "Title") return name;
		if (key == "Price") return std::to_string(price);
		if (key == "Rating") return std::to_string(rating);
	}

	void setValue(int key, string val) {
		if (key == 0) name = val;
		if (key == 1) price = stoi(val);
		if (key == 2) rating = stoi(val);
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
