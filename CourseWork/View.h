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
	short int addFieldSelect = 0;
	short int fieldSelect = 0;


	// ----- MENU ----- // 

	bool menuActive = false;
	int menuSelect = LISTITEMS;
	short int menuCursor = LISTITEMS;
	


	// ----- FIlter ------- //
	int filterFiledSelect = 0;
	int minPrice = 0;
	int maxPrice = 0;
	enum SortBy {NONE, MONEYUP, MONEYDOWN, RATINGUP};
	int sort = SortBy::NONE;










	bool itemOpen = false;

	

	int itemsSelect = 0;

	
	void cursorUp();
	void cursorDown();

	void enter();
	bool editField(int key);

	void render();

	bool login();
	

		
	Data* data;
	


	enum Field { TITLE, PRICE, RATING, LEFTITEM, DESCRIPTION, BUTTON };

private:
	User activeUser;

	enum Menu {LISTITEMS, ADD};

	unsigned int winSizeX = 20;
	unsigned int winSizeY = 100;
	unsigned int menuSizeY = winSizeY * 20 / 100;
	unsigned int viewSizeY = winSizeY * 50 / 100;
	unsigned int subViewSizeY = winSizeY  * 30 / 100;
	

	static const unsigned short int menuCount = 5;
	string menuItems[menuCount] = { "View", "Add", "Search", "Setting", "Quit" };


	string* bildMenu();

	string* bildAdd();
	string* bildSearch();
	string* bildListItems();
	string* bildSubView();

	string* bildDetailItem(Product);

	string bildItem(Product);

	string title(string, int);

	string topLine(int);
	string bottomLine(int);

	
	
};


