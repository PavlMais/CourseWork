#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include <iomanip>   

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
struct Data {
	Product* products;
	int productsSize;
	User* users;
	int usersSize;

};




class Window {
private:
	Data data;
	Product* products;

	int sizeX = 23, sizeY = 80;
	int menuSizeY = sizeY / 4;


	int mainSizeY = sizeY - (sizeY / 4);

	static const unsigned short int menuCount = 5;

	int offsetView = 0;

	string menus[menuCount] = { "View", "Add", "Search", "Setting", "LOL"};
	string bMenu[100];

	string* bild_menu() {

		int hline, vline, anglUL, anglUR, anglDL, anglDR, vrline, qnglURS, qnglDRS;
		hline = 196;
		vline = 179;
		anglUL = 218;
		anglDL = 192;
		bMenu[0] = "";
		for (int _ = 0; _ < menuSizeY + 2; _++) bMenu[0] += " ";
		bMenu[0] += char(vline);

		for (int i = 1; i < menuCount * 3 + 1; i += 3){
			
			bMenu[i] = "";
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
			for (int s = 0; s < menuSizeY; s++) bMenu[i] += char(hline);
			bMenu[i] += char(anglUR);
			bMenu[i] += char(qnglURS);
			
			
			bMenu[i + 1] = "";
			bMenu[i + 1] += char(vline);
			int strr = menuSizeY - menus[i / 3].length();
			for (int s = 0; s < strr + 1; s++){
				if (s == strr / 2) bMenu[i+1] += menus[i/3];
				else bMenu[i+1] += " ";
			}
			bMenu[i+1] += char(vrline);
			bMenu[i + 1] += char(vrline);
			
			bMenu[i + 2] = "";

			bMenu[i+2] += char(anglDL);
			for (int s = 0; s < menuSizeY; s++) bMenu[i+2] += char(hline);
			bMenu[i+2] += char(anglDR);
			bMenu[i + 2] += char(qnglDRS);
			
		}

		
		for (int i = menuCount * 3 + 1; i < sizeX; i++){
			bMenu[i] = "";
			for (int _ = 0; _ < menuSizeY + 2; _++) bMenu[i] += " ";
			bMenu[i] += char(vline);
		}


		return bMenu;
	}

	string info_item(Product product) {
		
		const unsigned short int widthID     = mainSizeY * 5 / 100;
		const unsigned short int widthTitle  = mainSizeY * 30 / 100;
		const unsigned short int widthPrice  = mainSizeY * 20 / 100;
		const unsigned short int widthRating = mainSizeY * 25 / 100;

		string id = to_string(product.id);
		string title = product.name;
		string price = to_string(product.price).substr(0, to_string(product.price).find(".") + 3);
		string rating = to_string(product.rating).substr(0, to_string(product.rating).find(".") + 3);
		


		if (id.length() > widthID)  id = id.substr(0, widthID);
		else  for (int i = id.length(); i < widthID; i++)id += " ";

		
		if (title.length() > widthTitle)  title = title.substr(0, widthTitle - 3) + "...";
		else  for (int i = title.length(); i < widthTitle; i++) title += " ";



		if (price.length() > widthPrice)  price = price.substr(0, widthPrice);
		else  for (int i = price.length(); i < widthPrice; i++) price += " ";





		if (product.name.length() > widthTitle)  product.name = product.name.substr(0, widthTitle);
		else  for (int i = product.name.length(); i < widthTitle; i++) product.name += " ";
		if (product.name.length() > widthTitle)  product.name = product.name.substr(0, widthTitle);
		else  for (int i = product.name.length(); i < widthTitle; i++) product.name += " ";


		
		
		string info = "";
		info +=  " " + id + " " + title + " " + price +  " " + rating + "\t\t    ";
		return info;
	}

	string* bild_view() {
		string* view = new string[40]; //data.productsSize * 3
		
		view[0] = " ID   Name               Price        Rating";

		if (viewSelect < 0) {
			cout << "\a";  viewSelect = 0;
		}


		if (viewSelect == (sizeX / 2 - 1) + offsetView) offsetView++;
		else if (viewSelect == offsetView) offsetView--;

		

		for (int i = 1; i < sizeX; i++)
		{ 
			if (i % 2 == 0) {
				
				if (i - 2 == viewSelect * 2 && !menuActive)
					view[i] = char(179) + info_item(data.products[i / 2 +offsetView]) + char(179);
				else
					view[i] = " " + info_item(data.products[i / 2 + offsetView]);

			}
			else {
				if (i - 1 == viewSelect * 2 && !menuActive){

					view[i] += char(218);
					for (int j = 0; j < mainSizeY; j++) view[i] += char(196);
					view[i] += char(191);

				} else if (i - 3 == viewSelect * 2 && !menuActive) {

					view[i] += char(192);
					for (int j = 0; j < mainSizeY; j++) view[i] += char(196);
					view[i] += char(217);
				}

			}
		}
		return view;
	}



public:
	bool menuActive = false;
	int menuSelect = 0; 
	int viewSelect = 0;


	Window(Data adata) {
		data = adata;
	}

	void render() {
		system("cls");

		string *bMenu = bild_menu();
		string *view = bild_view();

		for (int i = 0; i < 23; i++) {
			cout << bMenu[i]  << view[i]<< endl;;
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
	Data data;

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
		data.usersSize = stoi(buffer);

		data.users = new User[data.usersSize];

		for (int i = 0; i < data.usersSize; i++){
			getline(file, buffer);
			data.users[i] = parse_user(buffer);
		}


		getline(file, buffer);
		data.productsSize = stoi(buffer);

		data.products = new Product[data.productsSize];

		//cout << data.productsSize << endl;
		for (int i = 0; getline(file, buffer); i++)
		{
			//cout <<"BUffer: "<<i <<" "<< buffer << "\n\n";
			data.products[i] = parse_product(buffer);
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
	
	if (!view.login(db.data.users, db.data.usersSize)) return 0;
	

	Window win(db.data);

	int press;
	while (true)
	{
		 

		win.render();
		press = _getch();
		if (press == 224) { 
			switch (_getch())
			{
			case 72: // UP
				if (win.menuActive) win.menuSelect--;
				else win.viewSelect--;

				break;

			case 77: // LEFT
				win.menuActive = !win.menuActive;
				break;

			case 80: // 
				if (win.menuActive) win.menuSelect++;
				else win.viewSelect++;

				break;

			case 75: // RIGHT
				win.menuActive = !win.menuActive;
				break;



			default:
				break;
			}
		}
		
	}


	cout << "\n";
	system("pause");

	return 0;
}

