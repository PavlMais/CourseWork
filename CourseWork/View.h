#pragma once
#include "Data.h"

class View
{
public:
	View(Data* data);
	enum Menu {LISTITEMS, DETAILITEM, EDITITEM, ADD};
	
	Menu viewActive = Menu::LISTITEMS;
	bool menuActive = false;

	string editedField = "";

	bool editedFieldOnluNumbers = false;

	
	void cursorUp();
	void cursorDown();
	
	void render();

	bool login();
	

		
	Data* data;
	
	int itemsSelect = 0;
	short int fieldSelect = 0;
private:
	
	short int menuSelect = 0;
	User activeUser;
	unsigned int winSizeX = 20;
	unsigned int winSizeY = 61;
	unsigned int menuSizeY = winSizeY / 4;
	unsigned int viewSizeY = winSizeY - menuSizeY;
	unsigned int offsetItems = 0;

	static const unsigned short int menuCount = 5;
	string menuItems[menuCount] = { "View", "Add", "Search", "Setting", "Quit" };


	string* bildMenu();
	string* bildListItems();
	string* bildDetailItem(Product);
	string bildItem(Product product);
};

