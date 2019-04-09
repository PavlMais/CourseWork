#include <iostream>
#include <conio.h>
#include <string>
#include "View.h"

using std::string;

View::View(Data* pdata)
{
	data = pdata;
}

void View::enter() {
	if (itemOpen) {
		if (fieldSelect == Field::BUTTON) {
			if (menuSelect == Menu::ADD) {
				menuSelect = Menu::LISTITEMS;
			}
			itemOpen = false;
		}
		else 
		{
			isfieldEdit = true;
			if (menuSelect == Menu::ADD) {
				editedField = data->new_product.getValue(fieldSelect);

			}
			else {

				editedField = data->products[itemsSelect].getValue(fieldSelect);
			}

		}
		return;
	}

	switch (menuSelect)
	{
	case View::LISTITEMS:
		itemOpen = true;
		break;

	case View::ADD:
		break;

	}
}

bool View::editField(int key)
{
	if (key == 8)
	{
		editedField = editedField.substr(0, editedField.size() - 1);
	}
	else if (key == 13)
	{
		if (menuSelect == Menu::ADD) {
			data->new_product.setValue(fieldSelect, editedField);
		}
		else {
			data->products[itemsSelect].setValue(fieldSelect, editedField);
		}
		isfieldEdit = false;
		return true;
	}
	else editedField += char(key);

	return false;
}

void View::cursorUp(){
	if(itemOpen) fieldSelect--;
	else if (menuActive) menuSelect--; 
	else
	switch(menuSelect){
	case Menu::LISTITEMS:
		itemsSelect--; 
		break;

	case Menu::ADD:
		fieldSelect--;
		break;
	
	}

}
void View::cursorDown(){
	if (itemOpen) fieldSelect++;

	else if (menuActive) menuSelect++;
	else
		switch (menuSelect) {
		case Menu::LISTITEMS:
			std::cout << "WOWOWO";
			itemsSelect++;
			break;
		case Menu::ADD:
			fieldSelect++;
			break;

		}
}


void View::render() {

	system("cls");// Move to bottom

	string *bMenu = bildMenu();

	string *view = nullptr;

	std::cout << menuSelect;
	if (menuSelect == Menu::LISTITEMS) {
		if (itemOpen) {
			view = bildDetailItem(data->products[itemsSelect]);

		}
		else {
			view = bildListItems();

		}
	}
	else if (menuSelect == Menu::ADD) {
		view = bildDetailItem(data->new_product);

	}
	else {
		std::cout << "Menu not found:/\n\n";
		view = new string[winSizeX];
	}





	string buffer;
	for (int i = 0; i < winSizeX; i++) buffer += bMenu[i] + view[i] + "\n";
	std::cout << buffer;
}

string* View::bildDetailItem(Product product) {
	const unsigned short int FIELDSSIZE = 6;
	string FIELDS[FIELDSSIZE] = { "Title", "Price", "Rating","Left item", "Description"};

	FIELDS[5] = (menuSelect == Menu::LISTITEMS) ? "Back" : "Save";
	string *view = new string[winSizeX];

	view[0] = title("View");

	


	for (int i = 5, n = 0; i < FIELDSSIZE * 2 + 8; n++, i += 2)
	{
		if (fieldSelect == n && !menuActive) view[i] = topLine();
		else if (fieldSelect == n - 1 && !menuActive)  view[i] = bottomLine();
		else view[i] = "";
		

		if (n == FIELDSSIZE - 1 && !menuActive) {
			if (fieldSelect == n) view[i + 1] = "\t"+ FIELDS[FIELDSSIZE - 1];
			else view[i + 1] = "\t>"+ FIELDS[FIELDSSIZE - 1];
		}

		else if (fieldSelect == n && isfieldEdit) {
			i++;
			view[i + 1] = "\t> " + FIELDS[n] + ": " + editedField;
			i++;
		}
		else if (fieldSelect == n && !menuActive) {

			view[i + 1] = "\t>> " + FIELDS[n] + ": " + product.getValue(n);
		}
		else if (n < FIELDSSIZE){
			view[i + 1] = "\t " + FIELDS[n] + ": " + product.getValue(n);

		}
	}
	return view;
	
}
string View::title(string title) {
	string str;
	for (int i = 0; i < viewSizeY; i++)
	{
		if (i == viewSizeY / 2) str += title;
		else str += " ";
	}
	return str;
}

string View::topLine()
{
	string str;
	str = char(218);
	for (unsigned int j = 0; j < viewSizeY; j++) str += char(196);
	str += char(191);
	return str;
}

string View::bottomLine()
{
	string str;
	str = char(192);
	for (unsigned int j = 0; j < viewSizeY; j++) str += char(196);
	str += char(217);
	return str;
}


bool View::login(){
	
	string login, password;
	bool users_exists = false;
	User check_user;
	int left_try = 3;

	do {
		std::cout << "\n\n\t\tEnter login: ";
		std::cin >> login;


		for (int i = 0; i < data->usersSize; i++) {
			std::cout << data->users[i].login;

			if (data->users[i].login == login) {
				check_user = data->users[i];
				users_exists = true;
				break;
			}
		}
		system("cls");
		if (!users_exists) std::cout << "\n\n\t\tUser not exists!";

	} while (!users_exists);


	int key;
	do {
		password = "";
		while (true)
		{
			std::cout << "\n\t\tTrying: " << left_try << "\n\t\tEnter password: ";
			for (int i = 0; i < password.size(); i++) std::cout << char(249);
			
			key = _getch();

			if (key == 13) break;
			else if (key == 8) password = password.substr(0, password.size() - 1);
			else password += char(key);

			system("cls");
		}

		if (password == check_user.password) {
			activeUser = check_user;
			break;
		}

		left_try--;
		if (left_try <= 0) return false;
		system("cls");
		std::cout << "\n\n\t\tPasswort incorect";
	} while (true);


	std::cout << "you login";
	return true;
}

string* View::bildMenu() {

	char hline, vline, anglUL, anglUR, anglDL, anglDR, vrline, qnglURS, qnglDRS;
	hline = 196;
	vline = 179;
	anglUL = 218;
	anglDL = 192;
	
	string *bMenu = new string[winSizeX];

	for (unsigned int _ = 0; _ < menuSizeY + 2; _++) bMenu[0] += " ";
	bMenu[0] += char(vline);

	for (unsigned int i = 1; i < menuCount * 3 + 1; i += 3) {

		bMenu[i] = "";
		if (i / 3 == menuSelect) {
			vrline = 32;
			anglUR = 196;
			anglDR = 196;
			qnglURS = 217;
			qnglDRS = 191;
		}
		else {
			vrline = 179;
			anglUR = 191;
			anglDR = 217;
			qnglURS = 179;
			qnglDRS = 179;
		}

		bMenu[i] += anglUL;
		for (unsigned int s = 0; s < menuSizeY; s++) bMenu[i] += hline;
		bMenu[i] += anglUR;
		bMenu[i] += qnglURS;


		bMenu[i + 1] = "";
		bMenu[i + 1] += vline;
		int strr = menuSizeY - menuItems[i / 3].length();
		for (int s = 0; s < strr + 1; s++) {
			if (s == strr / 2) bMenu[i + 1] += menuItems[i / 3];
			else bMenu[i + 1] += " ";
		}
		bMenu[i + 1] += vrline;
		bMenu[i + 1] += vrline;

		bMenu[i + 2] = "";

		bMenu[i + 2] += anglDL;
		for (unsigned int s = 0; s < menuSizeY; s++) bMenu[i + 2] += hline;
		bMenu[i + 2] += anglDR;
		bMenu[i + 2] += qnglDRS;

	}


	for (unsigned int i = menuCount * 3 + 1; i < winSizeX; i++) {
		bMenu[i] = "";
		for (unsigned int _ = 0; _ < menuSizeY + 2; _++) bMenu[i] += " ";
		bMenu[i] += char(vline);
	}

	return bMenu;
}

string View::bildItem(Product product) {
	const unsigned short int widthID = viewSizeY * 10 / 100;
	const unsigned short int widthTitle = viewSizeY * 40 / 100;
	const unsigned short int widthPrice = viewSizeY * 25 / 100;
	const unsigned short int widthRating = viewSizeY * 25 / 100;


	string id = std::to_string(product.id);
	string title = product.name;
	string price = std::to_string(product.price).substr(0, std::to_string(product.price).find(".") + 3);
	string rating = std::to_string(product.rating).substr(0, std::to_string(product.rating).find(".") + 3);



	if (id.length() > widthID)  id = id.substr(0, widthID);
	else  for (unsigned int i = id.length(); i < widthID; i++)id += " ";


	if (title.length() > widthTitle)  title = title.substr(0, widthTitle - 2) + "..";
	else  for (unsigned int i = title.length(); i < widthTitle; i++) title += " ";



	if (price.length() > widthPrice)  price = price.substr(0, widthPrice);
	else  for (unsigned int i = price.length(); i < widthPrice; i++) price += " ";





	if (product.name.length() > widthTitle)  product.name = product.name.substr(0, widthTitle);
	else  for (unsigned int i = product.name.length(); i < widthTitle; i++) product.name += " ";
	if (product.name.length() > widthTitle)  product.name = product.name.substr(0, widthTitle);
	else  for (unsigned int i = product.name.length(); i < widthTitle; i++) product.name += " ";




	string info = "";
	info += " " + id + " " + title + " " + price + " " + rating + "  ";
	return info;
}

string* View::bildListItems() {
	static unsigned int offsetItems = 0;
	string* view = new string[winSizeX];
	view[0] = " ID   Name            Price     Rating";

	if (itemsSelect < 0) itemsSelect = 0;// add ring ring
	if (itemsSelect > data->productsSize - 1) itemsSelect = data->productsSize - 1;
	
	if (itemsSelect == winSizeX / 2 + offsetItems - 2) offsetItems++;
	else if (itemsSelect == offsetItems && offsetItems != 0) offsetItems--;

	
	for (int VIter = 1, IIter = offsetItems; VIter < winSizeX - 1 && IIter < data->productsSize; VIter += 2, IIter++)
	{
		if (IIter == itemsSelect && !menuActive) view[VIter] = topLine();
		else if (IIter == itemsSelect + 1 && !menuActive) view[VIter] = bottomLine();
		else view[VIter] = " ";


		if(IIter == itemsSelect && !menuActive)
			view[VIter + 1] = char(179) + bildItem(data->products[IIter]) + char(179);
		else
			view[VIter + 1] = " "+ bildItem(data->products[IIter]);

		if (itemsSelect == data->productsSize - 1 && !menuActive) view[VIter + 2] = bottomLine();
	}
	return view;
}


