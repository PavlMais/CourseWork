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
public:

	int id = 0;
	string type = "";
	string name = "";
	float price = 0;
	int sale = 0;
	int left_item = 0;
	float rating = 0;
	string description = "";
	int id_company = 0;


	string getValue(int field) {
		switch (field) {
		case Field::ID: return std::to_string(id);
		case Field::TITLE: return name;
		case Field::TYPE: return type;
		case Field::PRICE: return floatNormalize(price);
		case Field::RATING: return floatNormalize(rating);
		case Field::LEFTITEM: return std::to_string(left_item);
		case Field::DESCRIPTION: return description;
		default: return " ";
		}
	}

	void setValue(int key, string val) {
		switch (key){
			case ID: id = stoi(val); break;
			case TITLE: name = val; break;
			case TYPE: type = val; break;
			case PRICE: price = stoi(val); break;
			case RATING: rating = stoi(val); break;
			case LEFTITEM: left_item = stoi(val); break;
			case DESCRIPTION: description = val; break;
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
private:
	string floatNormalize(float fi) {
		return std::to_string(fi).substr(0, std::to_string(fi).find(".") + 3);
	}

	
	enum Field { ID, TITLE, TYPE, PRICE, RATING, LEFTITEM, DESCRIPTION, BUTTON };

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
		productsSize += 1;
		

		Product *newProducts = new Product[productsSize];

		for (int i = 0; i < productsSize - 1; i++)
			newProducts[i] = products[i];
		

		newProducts[productsSize - 1] = new_product;

		delete[] products;

		products = newProducts;
	

		new_product = Product();

		indexing();

	}


	void indexing() 
	{
		ids_size = productsSize;
		ids_products = new int[ids_size];
		for (int i = 0; i < ids_size; i++) ids_products[i] = i;
	}


	void delProduct(int index) {
		std::cout << "\n\nIDSSIZE"<< ids_size;

	
		ids_size -= 1;
		productsSize -= 1;
	

		for (int i = index; i < productsSize; i++)
		{
			products[i] = products[i + 1];
		}


		indexing();
	}


};
