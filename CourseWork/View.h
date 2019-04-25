#pragma once
#include "Data.h"


namespace ListItems {
	string* render();
}


class View
{
public:
	View(Data* data);
	string editedField = "";


	bool isfieldEdit = false;

	int filedItemSelect = 0;
	int filterFiledSelect = 0;

	int fieldSelect = 0;
	int filedCursorSelect = 0;



	const static unsigned short	ALLFILEDS = 5;
	const static unsigned short	MINFILEDS = 4;

	enum Field {ID, TITLE, PRICE, RATING, LEFTITEM, DESCRIPTION, BUTTON};

	string fieldNames[ALLFILEDS] = {
		"ID",
		"Title",
		"Price",
		"Rating"
	};
	

	bool need_save = false;



	int viewActive = LISTITEMS;
	enum ViewActive {LISTITEMS, ADDITEMS, DETAILITEMS	};

	

	bool isMenuActive = false;

	int menuSelect = 0;
	int menuActive = 0;

	

	SortConfing sortConf;

	string search = "";
	bool isSearch = false;
	bool isSearchActive = false;


	int itemsSelect = 0;

	
	void cursorUp();
	void cursorDown();
	void cursorLeft();
	void cursorRight();

	void enter();
	bool editField(int key);

	void render();

	bool login();
	

		
	Data* data;
	


private:


	User activeUser;

	const unsigned int winSizeX = 20;
	const unsigned int winSizeY = 105;
	const unsigned int menuSizeY = winSizeY * 20 / 100;
	const unsigned int viewSizeY = winSizeY * 50 / 100;
	const unsigned int widthItem = viewSizeY - 2;

	unsigned int widthFieldTitles[ALLFILEDS] = {
		widthItem * 7 / 100,
		widthItem * 43 / 100,
		widthItem * 25 / 100,
		widthItem * 25 / 100
	};

	static const unsigned short int menuCount = 5;
	string menuItems[menuCount] = { "View", "Add", "Search", "Setting", "Quit" };


	string* bildMenu();

	string* bildAdd();
	void bildSearch(string*);
	string* bildListItems();
	void topTitle(string * arr, short select);
	void bildSearch(string * view, int start);

	string getFilterField(int key);

	string* bildDetailItem(Product);

	string bildItem(Product);

	string title(string, int);

	string topLine(int);
	string bottomLine(int);

	
	
};


