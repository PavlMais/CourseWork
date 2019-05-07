#include <iostream>
#include <conio.h>

#include "DataBase.h"
#include "View.h"
#include "utils.h"




int main() {
	system("mode con: cols=230 lines=30");
	DataBase db;

	View view(db.getData());

	//if (!view.login()) return 0; 




	int key;
	while (true)
	{
		//system("cls");
		view.render();
		key = _getch();
		
		if (view.need_save) { 
			db.save(); 
			view.need_save = false; 
			std::cout << "SAVED!!!!!!!";
		}

		if (view.isfieldEdit) {
			if(view.editField(key)) db.save();
			continue;
		}

		
		if (key == 115) {
			if (view.sortConf.active) 
				sorting(view.data->ids_products, view.data->ids_size,  view.data->products, view.data->productsSize, view.sortConf);
				
 
				
			view.sortConf.active = !view.sortConf.active;
		
		}
		else if (key == 102) {
			

			view.sortConf.active = false;
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












