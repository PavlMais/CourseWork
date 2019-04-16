#include <iostream>
#include <conio.h>
#include <string>
#include "View.h"
#include "utils.h"

using std::string;

View::View(Data* pdata)
{
	data = pdata;
}

void View::enter() {
	if (isMenuActive) {
		viewActive = menuSelect;
		isMenuActive = false;
	} else {

		switch (viewActive)
		{
		case LISTITEMS: viewActive = DETAILITEMS; break;
		case DETAILITEMS:
			if (filedItemSelect == BUTTON) {

				viewActive = LISTITEMS;
				need_save = true;
			}
			else {
				isfieldEdit = true;
				editedField = data->products[itemsSelect].getValue(filedItemSelect);
			}

			break;

		case ADDITEMS:
			if (filedItemSelect == BUTTON) {
				viewActive = LISTITEMS;
				need_save = true;
				data->addProduct();
			}
			else {
				isfieldEdit = true;
				editedField = data->new_product.getValue(filedItemSelect);
			}

			break;

		default:
			std::cout << "Error! 1";
			break;
		}
	}
}

bool View::editField(int key){
	if (key == 8) editedField = editedField.substr(0, editedField.size() - 1);
	
	else if (key == 13) {
		switch (viewActive) {
			case DETAILITEMS: 
				data->products[itemsSelect].setValue(filedItemSelect, editedField);
				break;
			case ADDITEMS:
				data->new_product.setValue(filedItemSelect, editedField);
				break;
		}
		isfieldEdit = false;
		return true;
	}
	else editedField += char(key);

	return false;
}

void View::cursorUp(){
	if (isMenuActive) menuSelect--;
	else {
		switch (viewActive) {
			case LISTITEMS: itemsSelect--; break;
			case DETAILITEMS: filedItemSelect--; break;
			case ADDITEMS: filedItemSelect--; break;
		}
	}
}

void View::cursorDown(){
	if (isMenuActive) menuSelect++;
	else {
		switch (viewActive) {
			case LISTITEMS: itemsSelect++; break;
			case DETAILITEMS: filedItemSelect++; break;
			case ADDITEMS: filedItemSelect++; break;
		}
	}
}


void View::render() {

	system("cls");// Move to bottom

	string *bMenu = bildMenu();

	string *view = nullptr;

	
	//std::cout << "Menu size: " << menuSizeY << "  View size: " << viewSizeY << "  Sub view size: " << subViewSizeY;
	
	std::cout << "Menu active: " << isMenuActive << " ViewActive: " << viewActive << "\n";
	

	
	switch (viewActive) {
		case LISTITEMS: view = bildListItems(); break;
		case ADDITEMS: view = bildDetailItem(data->new_product); break;
		case DETAILITEMS: view = bildDetailItem(data->products[itemsSelect]); break;
		default:
			std::cout << "Menu not found:/\n\n";
			view = new string[winSizeX];
			break;
	}





	string buffer;
	for (int i = 0; i < winSizeX; i++) buffer += bMenu[i] + view[i] +"\n";
	std::cout << buffer;
}

string* View::bildDetailItem(Product product) {
	const unsigned short int FIELDSSIZE = 6;
	string FIELDS[FIELDSSIZE] = { "Title", "Price", "Rating","Left item", "Description"};

	FIELDS[5] = (viewActive == 2) ? "Back" : "Save";
	string *view = new string[winSizeX];

	view[0] = title("View", viewSizeY);

	


	for (int i = 5, n = 0; i < FIELDSSIZE * 2 + 8; n++, i += 2)
	{
		if (filedItemSelect == n && !isMenuActive) view[i] = topLine(viewSizeY);
		else if (filedItemSelect == n - 1 && !isMenuActive)  view[i] = bottomLine(viewSizeY);
		else view[i] = "";
		

		if (n == FIELDSSIZE - 1 && !isMenuActive) { // for button
			if (filedItemSelect == n) view[i + 1] = "\t "+ FIELDS[FIELDSSIZE - 1];
			else view[i + 1] = "\t "+ FIELDS[FIELDSSIZE - 1];
		}

		else if (filedItemSelect == n && isfieldEdit) {

			i++;
			view[i] = "\t Edit mode:";
			view[i + 1] = "\t " + FIELDS[n] + ": " + editedField;
			i++;
		}
		else if (filedItemSelect == n && !isMenuActive) {

			view[i + 1] = "\t " + FIELDS[n] + ": " + product.getValue(n);
		}
		else if (n < FIELDSSIZE){
			view[i + 1] = "\t " + FIELDS[n] + ": " + product.getValue(n);
		}
	}
	return view;
	
}
string View::title(string title, int size) {
	//std::cout << "txtSize: " << title.size() << " size: " << size;
	string str;
	size = size - title.size(); // TODO: ReWrite
	for (int i = 0; i < size + 1; i++)
	{
		if (i == size / 2) str += title;
		else str += "-";
	}
	//std::cout << "txtSize: " << str.size() << "\n";
	return str;
}
string View::topLine(int size)
{
	string str;
	str = char(218);
	for (unsigned int j = 0; j < size - 2; j++) str += char(196);
	str += char(191);
	return str;
}
string View::bottomLine(int size)
{
	string str;
	str = char(192);
	for (unsigned int j = 0; j < size - 2; j++) str += char(196);
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
	char hLine, vLine, TR, TL, BR, BL, TRR, BRR, CR, CRR;

	string *menu = new string[winSizeX];

	for (unsigned int _ = 0; _ < menuSizeY + 2; _++) menu[0] += " ";
	menu[0] += char(179);

	//std::cout << "M sel:"<<isMenuActive << " M act:" << viewFocus << " M cur:" <<menuSelect <<   "\n";

	if (menuSelect < 0) menuSelect = menuCount - 1;
	else if (menuSelect >= menuCount) menuSelect = 0;

	for (int m = 0, i = 1; m < menuCount; m++, i += 3)
	{		
		if (isMenuActive && menuSelect == m && m == menuActive) {
			vLine = char(186);
			hLine = char(205);

			TR = char(205);
			TL = char(201);
			BR = char(205);
			BL = char(200);

			TRR = char(190);
			BRR = char(184);
			CRR = ' ';
			CR = ' ';
		}
		
		else if (menuActive == m) {
			vLine = char(179);
			hLine = char(196);
			TR = char(196);
			TL = char(218);
			BR = char(196);
			BL = char(192);

			TRR = char(217);
			CRR = ' ';
			BRR = char(191);
			CR = ' ';
		}
		else if (isMenuActive && menuSelect == m) {
			vLine = char(186);
			hLine = char(205);

			TR = char(187);
			TL = char(201);
			BR = char(188);
			BL = char(200);

			TRR = char(179);
			BRR = char(179);
			CRR = char(179);
			CR = char(186);
		}
		else {
			vLine = char(179);
			hLine = char(196);
			TR = char(191);
			TL = char(218);
			BR = char(217);
			BL = char(192);

			TRR = char(179);
			BRR = char(179);
			CRR = char(179);
			CR = char(179);
		}

		menu[i] = TL;
		for (unsigned int _ = 0; _ < menuSizeY; _++) menu[i] += hLine;
		menu[i] += TR;
		menu[i] += TRR;
		
		int strr = menuSizeY - menuItems[m].length();
		menu[i + 1] = vLine;
		for (int s = 0; s < strr + 1; s++) {
			if (s == strr / 2) menu[i + 1] += menuItems[m];
			else menu[i + 1] += " ";
		}
		menu[i + 1] += CR;
		menu[i + 1] += CRR;

		
		menu[i + 2] = BL;
		for (unsigned int _ = 0; _ < menuSizeY; _++) menu[i + 2] += hLine;
		menu[i + 2] += BR;
		menu[i + 2] += BRR;

	}

	for (int i = menuCount * 3 + 1; i < winSizeX; i++)
	{
		for (int s = 0; s < menuSizeY + 2; s++) menu[i] += " ";
		menu[i] += char(179);;
	}

	return menu;
}

string View::bildItem(Product product) {
	const unsigned short int widthItem = viewSizeY - 6;
	const unsigned short int widthID = widthItem * 10 / 100;
	const unsigned short int widthTitle = widthItem * 40 / 100;
	const unsigned short int widthPrice = widthItem * 25 / 100;
	const unsigned short int widthRating = widthItem * 25 / 100;


	string id = std::to_string(product.id);
	string title = product.name;
	string price = floatNormalize(product.price);
	string rating = floatNormalize(product.rating);

	id = adaptString(id, widthID);

	title = adaptString(title, widthTitle);

	price = adaptString(price, widthPrice);

	rating = adaptString(rating, widthRating);

	
	return  " " + id + " " + title + " " + price + " " + rating + "  ";
}

string* View::bildListItems() {
	static unsigned int offsetItems = 0;
	string* view = new string[winSizeX];

	int start, magic;
	if (isSearch) {

		view[1] = "Search:     Sort: None   ";



		start = 3; magic = 3;
	}
	else {
		start = 1; magic = 2;
	}

	
	view[start - 1] = title("ID Name Price", viewSizeY);












	if (itemsSelect < 0) itemsSelect = 0;// add ring ring
	if (itemsSelect > data->productsSize - 1) itemsSelect = data->productsSize - 1;
	
	if (itemsSelect == winSizeX / 2 + offsetItems - magic) offsetItems++;
	else if (itemsSelect == offsetItems && offsetItems != 0) offsetItems--;

	
	for (int VIter = start, IIter = offsetItems; VIter < winSizeX - 1 && IIter < data->productsSize; VIter += 2, IIter++)
	{
		if (IIter == itemsSelect && !isMenuActive) view[VIter] = topLine(viewSizeY);
		else if (IIter == itemsSelect + 1 && !isMenuActive) view[VIter] = bottomLine(viewSizeY);
		else for (int i = 0; i < viewSizeY; i++) view[VIter] += " ";
		


		if(IIter == itemsSelect && !isMenuActive)
			view[VIter + 1] = char(179) + bildItem(data->products[IIter]) + char(179);
		else
			view[VIter + 1] = " "+ bildItem(data->products[IIter]) + " ";

		if (itemsSelect == data->productsSize - 1 && !isMenuActive) view[VIter + 2] = bottomLine(viewSizeY);
	}
	return view;
}







