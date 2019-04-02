#pragma once
#include "Data.h"

class View
{
public:
	View(Data* data);

	bool itemOpen = false;
	string menuActive = "listItems";
	short int menuSelect = 0;
	int itemsSelect = 0;


	void render();

	bool login();

		

private:
	Data* data;
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
	string* bildOpenItem();
	string bildItem(Product product);
};

