#include <iostream>
#include <conio.h>
		#include <string>
#include "DataBase.h"
#include "View.h"
#include "utils.h"




int main() {


	//Create a structure to hold the data:
	string data[] = { "pidgeonbc", "bcgdfijgfdjgi", "1234", "%^*#" };

	//Get the length of the array.
	int size = 4;

	//loop through all the items and print them if they match
	string matchString = "bc";
	for (int x = 0; x < size; x++) {
		std::cout << std::string::npos << "\n";
	}
	system("pause");
	return 0;







	
	DataBase db;

	View view(db.getData());

	//if (!view.login()) return 0; 





	int key;
	while (true)
	{
		view.render();
		key = _getch();
		


		if (view.need_save) { 
			db.save(); 
			view.need_save = false; 
		}

		if (view.isfieldEdit) {
			if(view.editField(key)) db.save();
			continue;
		}

		
		if (key == 1025326534634) {
			if (view.sortConf.active) 
				sorting(view.data->products, view.data->productsSize, view.sortConf);

			view.sortConf.active = !view.sortConf.active;
		
		}
		else if (key == 102) {
			std::cout << "((((((((((((((((((((((((((((((((((((((((((";
			view.isSearch = true;
			view.isSearchActive = true;

			view.isfieldEdit = true;
			view.editedField = view.search;


		}
		else if (key == 13) view.enter();
		
		else if (key == 224) {
			switch (_getch()){
			case 72: view.cursorUp(); break;

			case 77: view.cursorLeft(); break;

			case 80: view.cursorDown(); break;

			case 75: view.cursorRight(); break;
			}
		}
	}
	

	system("pause");
	return 0;
}












