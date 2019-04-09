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

void View::enter()
{
	if (menuActive) {
		menuSelect = menuCursor;
		menuActive = false;
	}
	else if (itemOpen || menuSelect == Menu::ADD) {
		if (fieldSelect == Field::BUTTON) {
			if (menuSelect == Menu::ADD) {
				menuSelect = Menu::LISTITEMS;
				data->addProduct();
				
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
	} else 

	switch (menuSelect)
	{
	case View::ADD:
	case View::LISTITEMS:
		itemOpen = true;
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
	if (menuActive) menuCursor--;

	else if(itemOpen) fieldSelect--;
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
	if (menuActive) menuCursor++;
	else if (itemOpen) fieldSelect++;

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

	string *subView = nullptr;
	//std::cout << "Menu size: " << menuSizeY << "  View size: " << viewSizeY << "  Sub view size: " << subViewSizeY;
	if (menuSelect == Menu::LISTITEMS) {
		if (itemOpen) {
			view = bildDetailItem(data->products[itemsSelect]);

		}
		else {
			view = bildListItems();
			subView = bildSubView();
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
	for (int i = 0; i < winSizeX; i++) buffer += bMenu[i] + view[i] + subView[i] +"\n";
	std::cout << buffer;
}

string* View::bildDetailItem(Product product) {
	const unsigned short int FIELDSSIZE = 6;
	string FIELDS[FIELDSSIZE] = { "Title", "Price", "Rating","Left item", "Description"};

	FIELDS[5] = (menuSelect == Menu::LISTITEMS) ? "Back" : "Save";
	string *view = new string[winSizeX];

	view[0] = title("View", viewSizeY);

	


	for (int i = 5, n = 0; i < FIELDSSIZE * 2 + 8; n++, i += 2)
	{
		if (fieldSelect == n && !menuActive) view[i] = topLine(viewSizeY);
		else if (fieldSelect == n - 1 && !menuActive)  view[i] = bottomLine(viewSizeY);
		else view[i] = "";
		

		if (n == FIELDSSIZE - 1 && !menuActive) { // for button
			if (fieldSelect == n) view[i + 1] = "\t "+ FIELDS[FIELDSSIZE - 1];
			else view[i + 1] = "\t "+ FIELDS[FIELDSSIZE - 1];
		}

		else if (fieldSelect == n && isfieldEdit) {

			i++;
			view[i] = "\t Edit mode:";
			view[i + 1] = "\t " + FIELDS[n] + ": " + editedField;
			i++;
		}
		else if (fieldSelect == n && !menuActive) {

			view[i + 1] = "\t " + FIELDS[n] + ": " + product.getValue(n);
		}
		else if (n < FIELDSSIZE){
			view[i + 1] = "\t " + FIELDS[n] + ": " + product.getValue(n);
		}
	}
	return view;
	
}
string View::title(string title, int size) {
	string str;
	size = size - title.size(); // TODO: ReWrite
	for (int i = 0; i < size; i++)
	{
		if (i == size / 2) str += title;
		else str += " ";
	}
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

	//std::cout << "M sel:"<<menuSelect << " M act:" << menuActive << " M cur:" <<menuCursor <<   "\n";

	if (menuCursor < 0) menuCursor = menuCount - 1;
	else if (menuCursor >= menuCount) menuCursor = 0;

	for (int m = 0, i = 1; m < menuCount; m++, i += 3)
	{		
		if (menuActive && menuCursor == m && m == menuSelect) {
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
		
		else if (menuSelect == m) {
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
		else if (menuActive && menuCursor == m) {
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
	const unsigned short int widthItem = viewSizeY - 7;
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
	view[0] = title("ID Name Price", viewSizeY);









	if (itemsSelect < 0) itemsSelect = 0;// add ring ring
	if (itemsSelect > data->productsSize - 1) itemsSelect = data->productsSize - 1;
	
	if (itemsSelect == winSizeX / 2 + offsetItems - 2) offsetItems++;
	else if (itemsSelect == offsetItems && offsetItems != 0) offsetItems--;

	
	for (int VIter = 1, IIter = offsetItems; VIter < winSizeX - 1 && IIter < data->productsSize; VIter += 2, IIter++)
	{
		if (IIter == itemsSelect && !menuActive) view[VIter] = topLine(viewSizeY);
		else if (IIter == itemsSelect + 1 && !menuActive) view[VIter] = bottomLine(viewSizeY);
		else for (int i = 0; i < viewSizeY; i++) view[VIter] += " ";
		


		if(IIter == itemsSelect && !menuActive)
			view[VIter + 1] = char(179) + bildItem(data->products[IIter]) + char(179);
		else
			view[VIter + 1] = " "+ bildItem(data->products[IIter]) + " ";

		if (itemsSelect == data->productsSize - 1 && !menuActive) view[VIter + 2] = bottomLine(viewSizeY);
	}
	return view;
}




string* View::bildSubView() {

	//search
	//sort
	//filter
	const short int FIELDSSIZE = 3;
	char VLINE = char(179);
	string FIELDS[FIELDSSIZE] = { "Search", "Sort", "Filter" };

	string* subView = new string[winSizeX];

	for (int n = 0, i = 0; n < FIELDSSIZE; n++, i += 3)
	{
		if (n == filterFiledSelect) {
			
			subView[i] = VLINE + topLine(subViewSizeY);
			subView[i + 1] = VLINE + FIELDS[n];
			subView[i + 2] =VLINE + bottomLine(subViewSizeY);
			

		}
		else {
			subView[i] = VLINE + topLine(subViewSizeY);
			subView[i + 1] = VLINE + FIELDS[n];
			subView[i + 2] = VLINE + bottomLine(subViewSizeY);

		}

	}
	
	return subView;


}


