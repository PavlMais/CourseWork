#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
using namespace std;

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
// ____________________________ NAME __________________________________
// |  View      | id   name    price       info         itd		  |
// |-------------|  1  IPhone  100000   Good or bat      info		  |
// |   Search    |  2  IPhone  1000     Good or bat      info		  |
// |-------------|  2  IPhone  1000     Good or bat      info		  |
// |  Setting    |  2  IPhone  1000     Good or bat      info		  |
// |             |  2  IPhone  1000     Good or bat      info		  |
// |             |  2  IPhone  1000     Good or bat      info		  |





class Window {
private:
	int sizeX = 23, sizeY = 50;
	int doxSize = sizeY / 4;
	int MainSize = sizeY - (sizeY / 4);
	static const int menu_size = 4;
	string menus[menu_size] = { "View", "Add", "Search", "Setting"};
	int menuSelect = 1;
	string bMenu[100];
	


	string* bild_menu() {
		int hline, vline, anglUL, anglUR, anglDL, anglDR, vrline, qnglURS, qnglDRS;
		hline = 196;
		vline = 179;
		anglUL = 218;
		anglDL = 192;
		bMenu[0] = "";
		for (int _ = 0; _ < doxSize + 2; _++) bMenu[0] += " ";
		bMenu[0] += char(vline);

		for (int i = 1; i < menu_size * 3 + 1; i += 3){ 
			
			bMenu[i] = "\n";
			if (i / 3 == menuSelect) {
				vrline = 32;
				anglUR = 196;
				anglDR = 196;
				qnglURS = 217;
				qnglDRS = 191;
			} else {
				vrline = 179;
				anglUR = 191;
				anglDR = 217;
				qnglURS = 179;
				qnglDRS = 179;
			}

			bMenu[i] += char(anglUL);
			for (int s = 0; s < doxSize; s++) bMenu[i] += char(hline);
			bMenu[i] += char(anglUR);
			bMenu[i] += char(qnglURS);
			bMenu[i] += "\n";
			

			bMenu[i+1] += char(vline);
			int strr = doxSize - menus[i / 3].length();
			for (int s = 0; s < strr + 1; s++){
				if (s == strr / 2) bMenu[i+1] += menus[i/3];
				else bMenu[i+1] += " ";
			}
			bMenu[i+1] += char(vrline);
			bMenu[i + 1] += char(vrline);
			bMenu[i+1] += "\n";

			bMenu[i+2] += char(anglDL);
			for (int s = 0; s < doxSize; s++) bMenu[i+2] += char(hline);
			bMenu[i+2] += char(anglDR);
			bMenu[i + 2] += char(qnglDRS);
			
		}

		
		for (int i = menu_size * 3 + 1; i < sizeX; i++){
			bMenu[i] = "\n";
			for (int _ = 0; _ < doxSize + 2; _++) bMenu[i] += " ";
			bMenu[i] += char(vline);
		}


		return bMenu;
	}

	string* bild_view() {




	}

	



public:
	void render(Product* products) {
		system("cls");

		string *bMenu = bild_menu();


		for (int i = 0; i < 40; i++)
		{
			cout << bMenu[i];
		}

	}
};


class View {
public:

	User active_user;

	bool login(User *users, const int users_count) {
		string login, password;
		bool users_exists = false;
		User check_user;
		int left_try = 3;

		do {
			cout << "\n\n\t\tEnter login: ";
			cin >> login;

			
			for (int i = 0; i < users_count; i++){
				if (users[i].login == login) {
					check_user = users[i];
					users_exists = true;
					break;
				}
			}
			system("cls");
			if (!users_exists) cout << "\n\n\t\tUser not exists";
			
		} while (!users_exists);



		do{
			cout << "\n\t\ttrying : "<<left_try<<"\n\t\tEnter password: ";
			cin >> password;

			if (password == check_user.password) {
				active_user = check_user;
				break;
			}

			left_try--;
			if (left_try <= 0) return false;
			system("cls");
			cout << "Passwort incorect";
		} while (true);


		cout << "you login";
		return true;
	}
};

class DataBase {

public:

	Product *products;
	int products_count;
	User *users;
	int users_count;

	void connect() {
		const string PATH_DB = "text.txt";

		ifstream file(PATH_DB);
		if (!file.good()) {
			cout << "File not exist\nCreate file...";
			ofstream file(PATH_DB);
			file << "4" << endl;
			for (size_t i = 0; i < 255; i++){
				file << i << " " << char(i) << "\n";
			}
		}
		string buffer;
		getline(file, buffer);
		users_count = stoi(buffer);

		users = new User[users_count];

		for (int i = 0; i < users_count; i++)
		{
			getline(file, buffer);
			cout << "GL: " << endl;
			users[i] = parse_user(buffer);
		
		}


		getline(file, buffer);
		products_count = stoi(buffer);
		products = new Product[products_count];

		for (int i = 0; getline(file, buffer); i++)
		{
			cout <<"BUffer: " << buffer << "\n\n";
			products[i] = parse_product(buffer);
		}

		file.close();
	}

private:

	User parse_user(string data) {
		int indx1 = data.find("[n]") + 3;
		int indx2 = data.find("[p]") + 3;
		int indx3 = data.find("[g]") + 3;
		User user;

		user.login =      data.substr(0, indx1 - 3);
		user.password =   data.substr(indx1, indx2 - indx1 - 3);

		

		string datas = data.substr(indx2, indx3 - indx2 - 3);
		user.group = stoi(datas);

		return user;
	}



	Product parse_product(string data) {
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

		product.id    = stoi(data.substr(0, indx1 - 3));
		product.type  = data.substr(5, 7);
		product.name  = data.substr(indx2, indx3 - indx2 - 3);
		product.price = stof(data.substr(indx3, indx4 - indx3 - 3));
		product.sale  = stoi(data.substr(indx4, indx5 - indx4 - 3));
		product.left_item = stoi(data.substr(indx5, indx6 - indx5 - 3));
		product.rating = stof(data.substr(indx6, indx7 - indx6 - 3));
		product.description = data.substr(indx7, indx8 - indx7 - 3);
		product.id_company = stoi(data.substr(indx8, indx9 - indx8 - 3));
		return product;
	}



};
int main() {
	View view;
	DataBase db;

	db.connect();
	
	//if (!view.login(db.users, db.users_count)) return 0;
	

	Window win;

	win.render(db.products);

	cout << "\n\n";
	system("pause");

	return 0;
}





// ###########
// #items
// #items
// #items
// #
// ############
