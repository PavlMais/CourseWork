#include <iostream>
#include <conio.h>
#include <string>
#include "View.h"
#include "utils.h"



//#define DEBAGON

using std::string;

View::View(Data* pdata){
	data = pdata;
}



void View::enter() {
	if (isMenuActive) {
		viewActive = menuActive = menuSelect;
		isMenuActive = false;
	}
	else if (sortConf.active) {

		if (sortConf.selected == sortConf.select) {

			if (sortConf.revers) {
				sortConf.selected = -1;
				sortConf.revers = false;
			} else
				sortConf.revers = true;


		} else sortConf.selected = sortConf.select;
	
	
	} else {

		switch (viewActive) {
		case LISTITEMS: viewActive = DETAILITEMS; break;
		case DETAILITEMS:
			if (filedItemSelect == 5){
				viewActive = LISTITEMS;
				need_save = true;
			}
			else if (filedItemSelect == 4) { // delete item
				viewActive = LISTITEMS;
				data->delProduct(itemsSelect);
				need_save = true;


			}
			else {
				isfieldEdit = true;
				editedField = data->products[itemsSelect].getValue(filedItemSelect);
				filedCursorSelect = editedField.size();
			}
			break;

		case ADDITEMS:
			if (filedItemSelect == 4) {

				if (checkProduct(data->new_product)) {

					viewActive = menuActive = LISTITEMS;
					need_save = true;
					data->addProduct();
				}
				else {
					message = "Not all fields!";
				}

				
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
	filedCursorSelect = limiter(filedCursorSelect, editedField.size() + 1);
	std::cout << "S size: " << editedField.size() << " sel: " << filedCursorSelect;

	 if (key == 224) {
		switch (_getch()) {
		
		case 77: filedCursorSelect++; break;
		
		case 75: filedCursorSelect--; break;
		}

	}
	 else if (key == 8) {
		 filedCursorSelect--;
		 if (filedCursorSelect > -1) editedField.erase(filedCursorSelect, 1);
	 }

	else if (key == 27) {
	
		switch (viewActive) {
			case LISTITEMS:
				search = editedField;
				isSearchActive = false;
				isSearch = false;
				break;
		}
		isfieldEdit = false;
	}
	else if (key == 13) {
		switch (viewActive) {
			case LISTITEMS:
				search = editedField;
				isSearchActive = false;
				
				searchByTitle(data->ids_products, &data->ids_size, search, data->products, data->productsSize);

				break;
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
	else {
		 editedField.insert(filedCursorSelect, 1, key);

		 filedCursorSelect++;
	 }

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

void View::cursorLeft(){
	if(sortConf.active) sortConf.select++;
	else isMenuActive = false;
}

void View::cursorRight(){
	if (sortConf.active) sortConf.select--;
	else isMenuActive = true;
}

string* View::bildHelp() {
	string *view = new string[winSizeX];

	for (int i = 0; i < winSizeX; i++) view[i] = "|\t";
	

	view[0] += "Tips: ";
	int index = 2;
	


	if (viewActive == 0) {

		if (isSearchActive ||isSearch ) {
			view[index] += "Esc - cancel";
			index += 2;
			view[index] += "Enter - Search";
			index += 2;

		}
		else {
			view[index] += "f - Search";
			index += 2;
		}

		if (sortConf.active) {
			view[index] += "<, > - Select sort";
			index += 2;
			view[index] += "Enter - set, revers";
			index += 2;
			view[index] += "s - apply";
			index += 2;
		}
		else {
			view[index] += "s - Sorting";
			index += 2;
		}





	}
	else if (viewActive == 2) {
		if (isfieldEdit) {
			view[index] += "Esc - Cancel";
			index += 2;
			view[index] += "Enter - Save";
			index += 2;
		}
	}




	

	return view;
}

void View::render() {


	string* bMenu = bildMenu();

	string* view = nullptr;

	string* helpView = bildHelp();

		//system("cls");// Move to bottom
	#ifdef DEBAGON
		std::cout << "Menu size: " << menuSizeY << "  View size: " << viewSizeY << "  Sub view size: " << subViewSizeY;
	
		std::cout << "Menu active: " << isMenuActive << " ViewActive: " << viewActive << "\n";
	
	#endif

	
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
	for (int i = 0; i < winSizeX; i++) buffer += bMenu[i] + view[i] + helpView[i] + "\n";

	#ifdef DEBAGON
		system("cls");
	#endif	

	std::cout << buffer;
}

string* View::bildDetailItem(Product product) {
	if(viewActive == 2) filedItemSelect = limiter(filedItemSelect, ALLFILEDS + 1);
	else filedItemSelect = limiter(filedItemSelect, ALLFILEDS);

	string *view = new string[winSizeX];

	view[0] = title("View", viewSizeY);
	
	string button = (viewActive == 2) ? "Close and save" : "Save  "+ message;
	view[1] = line(' ', viewSizeY);
	
	for (int i = 2, n = 0; i < ALLFILEDS * 2 + 6; n++, i += 2)
	{

		if (filedItemSelect == n && !isMenuActive) view[i] = topLine(viewSizeY);
		else if (filedItemSelect == n - 1 && !isMenuActive)  view[i] = bottomLine(viewSizeY);
		else view[i] = line(' ', viewSizeY);
		

		if (n == ALLFILEDS && viewActive == 2 || n == ALLFILEDS - 1 && viewActive == 1) { // for button
			if (filedItemSelect == n && !isMenuActive) view[i + 1] = adaptString("|\t " + button, viewSizeY - 7) + "|";
			else view[i + 1] = adaptString("\t " + button, viewSizeY - 7);

		}
		else if (n == ALLFILEDS - 1 && viewActive == 2) {
			if (filedItemSelect == n && !isMenuActive) view[i + 1] = adaptString("|\t Delete", viewSizeY - 7)+ "|";
			else view[i + 1] = adaptString("\t Delete", viewSizeY - 7);

		}

		else if (filedItemSelect == n && isfieldEdit) {
			i++;

			string isNum = (FieldIsNum[n]) ? "(Only numbers)" : "";

			view[i] = "|\t " + adaptString("Edit mode: "+ isNum, viewSizeY - 10)+ "|";
		

			view[i + 1] = "|\t " + adaptString(fieldNames[n] + ": " + editedField, viewSizeY - 10) + "|";


			i++;
			
			view[i + 1] = "|\t" +line(' ', fieldNames[n].size() + 3)+ lineCorsor(filedCursorSelect, viewSizeY - 19, ' ') + "|";
		}
		else if (filedItemSelect == n && !isMenuActive) {

			view[i + 1] = "|\t " + adaptString(fieldNames[n] + ": " + product.getValue(n), viewSizeY - 10) + "|";
		}
		else if (n < ALLFILEDS){
			view[i + 1] = "\t " + adaptString(fieldNames[n] + ": " + product.getValue(n), viewSizeY - 9);
		}
	}
	return view;
	
}
string View::title(string title, int size) {
	size -= title.size();
	int sl = (size % 2 != 0) ? size + 1 : size;

	return line(' ', sl / 2) + title + line(' ', size / 2);
}
string View::topLine(int size)
{
	return char(218) + line(char(196), size - 2) + char(191);
}
string View::bottomLine(int size)
{
	return char(192) + line(char(196), size - 2) + char(217);	
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
			std::cout << line(char(249), password.size());
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

	menu[0] = line(' ', menuSizeY + 2) + char(179);

	
#ifdef DEBAGON
	std::cout << "M sel:"<<isMenuActive << " M act:" << viewFocus << " M cur:" <<menuSelect <<   "\n";
#endif


	menuSelect = limiter(menuSelect, menuCount);


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
		menu[i] += TL + line(hLine, menuSizeY) + TR + TRR;

		menu[i + 1] += vLine + title(menuItems[m], menuSizeY) + CR + CRR;

		menu[i + 2] += BL + line(hLine, menuSizeY) + BR + BRR;
	}

	for (int i = menuCount * 3 + 1; i < winSizeX; i++) {
		menu[i] = line(' ', menuSizeY + 2) + char(179);
	}

	return menu;
}

string View::bildItem(Product product) {
	string str;
	for (int i = 0; i < MINFILEDS; i++)
		str += adaptString(product.getValue(i), widthFieldTitles[i]) + " ";
	
	return  str;
}

string* View::bildListItems() {
	static unsigned int offsetItems = 0;
	string* view = new string[winSizeX];

	int start, magic;
	if (isSearch) {
		bildSearch(view);
		start = 2;
	} else start = 0;


	topTitle(view, start);

	if (sortConf.active) {
		start += 3; magic = 4;
	}
	else {
		start += 1; magic = 2;
	}

	itemsSelect = limiter(itemsSelect, data->ids_size);

	

	if (itemsSelect == winSizeX / 2 + offsetItems - magic) offsetItems++;
	else if (itemsSelect == offsetItems && offsetItems != 0) offsetItems--;

	int vIter = start;
	for (int IIter = offsetItems; vIter < winSizeX - 1 && IIter < data->ids_size; vIter += 2, IIter++)
	{
		if      (IIter == itemsSelect && !isMenuActive)     view[vIter] = topLine(viewSizeY);
		else if (IIter == itemsSelect + 1 && !isMenuActive) view[vIter] = bottomLine(viewSizeY);
		else view[vIter] = line(' ', viewSizeY);
		

		if(IIter == itemsSelect && !isMenuActive)
			view[vIter + 1] = char(179) + bildItem(data->products[data->ids_products[IIter]]) + char(179);
		else
			view[vIter + 1] = " "+ bildItem(data->products[data->ids_products[IIter]]) + " ";

	}
	if (itemsSelect == data->ids_size - 1 && !isMenuActive) view[vIter] = bottomLine(viewSizeY);
	return view;
}


void View::topTitle(string* view, short start) {
	sortConf.select = limiter(sortConf.select, MINFILEDS);

	
	for (int i = 0; i < MINFILEDS; i++) {
		string field = fieldNames[i];
		if(sortConf.selected == i) field += (sortConf.revers) ? "v " : "^ ";


		if (!sortConf.active) {
			view[start] += " " + adaptString(field, widthFieldTitles[i]);
			continue;
		}


		if (sortConf.select == i) {
			view[start]     += char(218);
			view[start + 1] += char(179);
			view[start + 2]	+= char(192);
		} else if (sortConf.select == i - 1) {
			view[start]     += char(191);
			view[start + 1] += char(179);
			view[start + 2] += char(217);
		} else {
			view[start]     += " ";
			view[start + 1] += " ";
			view[start + 2] += " ";
		}





		if (sortConf.select == i) {
			view[start] += line(char(196), widthFieldTitles[i]);
			view[start + 1] += adaptString(field, widthFieldTitles[i]);
			view[start + 2] += line(char(196), widthFieldTitles[i]);
		} else {
			view[start] += line(' ', widthFieldTitles[i]);
			view[start + 1] += adaptString(field, widthFieldTitles[i]);
			view[start + 2] += line(' ', widthFieldTitles[i]);;
		}
	}
	if (sortConf.select == MINFILEDS - 1) {
		view[start]     += char(196);
		view[start]     += char(191);
		view[start + 1] += " ";
		view[start + 1] += char(179);
		view[start + 2] += char(196);
		view[start + 2] += char(217);
	}
	else {
		view[start] += "  ";
		view[start + 1] += "  ";
		view[start + 2] += "  ";
	}
}

void View::bildSearch(string* view) {

	if (isSearchActive) {
		view[0] = char(186);
		view[0] += "   Search: " + adaptString(editedField, viewSizeY - 10);
		
		view[1] = char(200) + lineCorsor(filedCursorSelect + 10, viewSizeY - 10, char(205));

	}
	else {
		
		view[0] += "   Search: " + adaptString(search, viewSizeY - 15);

		view[1] = bottomLine(viewSizeY);
	}

}



