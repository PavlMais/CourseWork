#include <iostream>
#include <string>
#include "View.h"

using std::string;

View::View(Data* pdata)
{
	data = pdata;
}

void View::render() {


	system("cls");
	string *bMenu = bildMenu();

	string *view;
	if (itemOpen) {
		view = bildOpenItem();
	}
	else {
		view = bildListItems();
	}


	string buffer;
	for (int i = 0; i < winSizeX; i++) {
		buffer += bMenu[i] + view[i] + "\n";
	}
	std::cout << buffer;


}



string* View::bildOpenItem() {

	string *view = new string[winSizeX];
	
	for (int i = 0; i < viewSizeY; i++)
	{
		if (i == viewSizeY / 2) view[0] += "View";
		else view[0] += " ";
	}

	view[2] = "Title: " + data->products[itemsSelect].name;

	







	return view;
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
			if (data->users[i].login == login) {
				check_user = data->users[i];
				users_exists = true;
				break;
			}
		}
		system("cls");
		if (!users_exists) std::cout << "\n\n\t\tUser not exists!";

	} while (!users_exists);



	do {
		std::cout << "\n\t\tTrying: " << left_try << "\n\t\tEnter password: ";
		std::cin >> password;

		if (password == check_user.password) {
			activeUser = check_user;
			break;
		}

		left_try--;
		if (left_try <= 0) return false;
		system("cls");
		std::cout << "Passwort incorect";
	} while (true);


	std::cout << "you login";
	return true;
}

string* View::bildMenu() {

	int hline, vline, anglUL, anglUR, anglDL, anglDR, vrline, qnglURS, qnglDRS;
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

		bMenu[i] += char(anglUL);
		for (unsigned int s = 0; s < menuSizeY; s++) bMenu[i] += char(hline);
		bMenu[i] += char(anglUR);
		bMenu[i] += char(qnglURS);


		bMenu[i + 1] = "";
		bMenu[i + 1] += char(vline);
		int strr = menuSizeY - menuItems[i / 3].length();
		for (int s = 0; s < strr + 1; s++) {
			if (s == strr / 2) bMenu[i + 1] += menuItems[i / 3];
			else bMenu[i + 1] += " ";
		}
		bMenu[i + 1] += char(vrline);
		bMenu[i + 1] += char(vrline);

		bMenu[i + 2] = "";

		bMenu[i + 2] += char(anglDL);
		for (unsigned int s = 0; s < menuSizeY; s++) bMenu[i + 2] += char(hline);
		bMenu[i + 2] += char(anglDR);
		bMenu[i + 2] += char(qnglDRS);

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
	string* view = new string[winSizeX];
	view[0] = " ID   Name            Price     Rating";



	if (itemsSelect < 0) itemsSelect = 0;// add ring ring
	if (itemsSelect > data->productsSize - 1) itemsSelect = data->productsSize - 1;
	
	if (itemsSelect == winSizeX / 2 + offsetItems - 2) offsetItems++;
	else if (itemsSelect == offsetItems && offsetItems != 0) offsetItems--;



	
	for (int VIter = 1, IIter = offsetItems; VIter < winSizeX - 1 && IIter < data->productsSize; VIter += 2, IIter++)
	{
		if (IIter == itemsSelect) {
			view[VIter] = char(218);
			for (unsigned int j = 0; j < viewSizeY; j++) view[VIter] += char(196);
			view[VIter] += char(191);


		}
		else if (IIter == itemsSelect + 1) {

			view[VIter] = char(192);
			for (unsigned int j = 0; j < viewSizeY; j++) view[VIter] += char(196);
			view[VIter] += char(217);
		}
		else view[VIter] = " ";



		if(IIter == itemsSelect)
			

			view[VIter + 1] = char(179) + bildItem(data->products[IIter]) + char(179);
		else
			view[VIter + 1] = " "+ bildItem(data->products[IIter]);

		if (itemsSelect == data->productsSize - 1) {

			view[VIter + 2] += char(192);
			for (unsigned int j = 0; j < viewSizeY; j++) view[VIter + 2] += char(196);
			view[VIter + 2] += char(217);
		}


	}
	

	for (int i = data->productsSize * 2; i < winSizeX; i++)
	{
		view[i] = "   - Space - ";
	}

	std::cout << winSizeY << " > " << viewSizeY << std::endl;
	//std::cout <<"Sel:"<< itemsSelect << " DT:" << data->productsSize << " Offs:" << offsetItems << " " << winSizeX / 2 << std::endl;

	return view;
}


