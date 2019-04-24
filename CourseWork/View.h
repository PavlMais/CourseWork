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


	enum Field {TITLE, PRICE, RATING, LEFTITEM, DESCRIPTION, BUTTON};

	enum FilterFiled {SEARCH, SORT, FILTER };
	
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

	unsigned int winSizeX = 20;
	unsigned int winSizeY = 105;
	unsigned int menuSizeY = winSizeY * 20 / 100;
	unsigned int viewSizeY = winSizeY * 50 / 100;
	unsigned int subViewSizeY = winSizeY  * 30 / 100;
	

	static const unsigned short int menuCount = 5;
	string menuItems[menuCount] = { "View", "Add", "Search", "Setting", "Quit" };


	string* bildMenu();

	string* bildAdd();
	void bildSearch(string*);
	string* bildListItems();
	void topTitle(string * arr, short select);
	void bildSearch(string * view, int start);
	string* bildSubView();

	string getFilterField(int key);

	string* bildDetailItem(Product);

	string bildItem(Product);

	string title(string, int);

	string topLine(int);
	string bottomLine(int);

	
	
};


