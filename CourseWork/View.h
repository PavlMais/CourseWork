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

	//enum Field { TITLE, PRICE, RATING, LEFTITEM, DESCRIPTION, BUTTON };

	enum  Field {NONE, TITLE, PRICE, RATING, LEFTITEM, DESCRIPTION, BUTTON, SEARCH, SORT, FILTER};


	// ----- MENU ----- // 
	enum MenuActive{MENU, VIEW, SUBVIEW};
	int menuActive = 0;

	int menuSelect = LISTITEMS;
	short int menuCursor = LISTITEMS;
	int viewActive = 0;
	


	// ----- FIlter ------- //
	int filedItemSelect = 0;
	int filterFiledSelect = 0;
	int minPrice = 0;
	int maxPrice = 0;
	enum SortBy {NOSORT, MONEYUP, MONEYDOWN, RATINGUP};
	int sort = SortBy::NOSORT;

	string filterSearch = " - ";



	enum class vActive  {LISTITEMS, ADDITEMS, DETAILITEMS};
	





	bool itemOpen = false;

	

	int itemsSelect = 0;

	
	void cursorUp();
	void cursorDown();

	void enter();
	bool editField(int key);

	void render();

	bool login();
	

		
	Data* data;
	




private:
	User activeUser;

	enum Menu {LISTITEMS, ADD};

	unsigned int winSizeX = 20;
	unsigned int winSizeY = 105;
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

	string getFilterField(int key);

	string* bildDetailItem(Product);

	string bildItem(Product);

	string title(string, int);

	string topLine(int);
	string bottomLine(int);

	
	
};


