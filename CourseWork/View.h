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



	const static unsigned short	ALLFILEDS = 8;
	const static unsigned short	MINFILEDS = 6;

	enum Field {ID, TITLE,TYPE, PRICE, RATING, LEFTITEM, DESCRIPTION, BUTTON};
	bool FieldIsNum[ALLFILEDS] = { 1, 0, 0, 1, 1, 1, 0 };
	string fieldNames[ALLFILEDS] = {
		"ID",
		"Title",
		"Type",
		"Price",
		"Rating",
		"Left items",
		"Description"
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

	const unsigned int winSizeX = 26;
	const unsigned int winSizeY = 180;
	const unsigned int menuSizeY = winSizeY * 15 / 100;
	const unsigned int viewSizeY = winSizeY * 75 / 100;

	const unsigned int widthItem = viewSizeY - 2;

	unsigned int widthFieldTitles[ALLFILEDS] = {
		widthItem * 4 / 100,
		widthItem * 32 / 100,
		widthItem * 10 / 100,
		widthItem * 15 / 100,
		widthItem * 20 / 100,
		widthItem * 17 / 100
	};

	static const unsigned short int menuCount = 5;
	string menuItems[menuCount] = { "View", "Add", "Search", "Setting", "Quit" };

	string message, error_msg_type;
	string* bildMenu();

	string* bildAdd();
	void bildSearch(string*);
	string* bildListItems();
	void topTitle(string * arr, short select);
	void bildSearch(string * view, int start);

	string getFilterField(int key);

	string* bildDetailItem(Product);
	string* bildHelp();

	string bildItem(Product);

	string title(string, int);

	string topLine(int);
	string bottomLine(int);

	
	
};


