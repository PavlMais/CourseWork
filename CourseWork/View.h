#pragma once
#include "Data.h"


namespace ListItems {
	string* render();
}


class View
{
public:
	View(Data* data);
	
	bool menuActive = false;

	string editedField = "";

	bool isfieldEdit = false;

	bool editFieldNum = false;

	
	void cursorUp();
	void cursorDown();
	void enter();
	bool editField(int key);

	void render();

	bool login();
	

		
	Data* data;
	
	int itemsSelect = 0;
	short int addFieldSelect = 0;
	short int fieldSelect = 0;


	enum Field { TITLE, PRICE, RATING, LEFTITEM, DESCRIPTION, BUTTON };

private:
	User activeUser;

	enum Menu {LISTITEMS, ADD};
	int menuSelect = LISTITEMS;

	bool itemOpen = false;

	unsigned int winSizeX = 20;
	unsigned int winSizeY = 61;
	unsigned int menuSizeY = winSizeY / 4;
	unsigned int viewSizeY = winSizeY - menuSizeY;

	static const unsigned short int menuCount = 5;
	string menuItems[menuCount] = { "View", "Add", "Search", "Setting", "Quit" };


	string* bildMenu();

	string* bildAdd();
	string* bildSearch();
	string* bildListItems();

	string* bildDetailItem(Product);

	string bildItem(Product);

	string title(string);

	string topLine();
	string bottomLine();

	
	
};


