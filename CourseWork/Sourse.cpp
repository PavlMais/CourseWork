#include <iostream>
#include <conio.h>
#include "DataBase.h"
#include "View.h"
#include "utils.h"


int main() {
	
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

		std::cout << key;
		if (key == 102) {
			if (view.sortConf.active) {
				// sort data

				
				sortProducts(view.data->products,view.data->productsSize, view.sortConf);
				

				view.sortConf.active = false;
			}
			else {
				view.sortConf.active = true;
			}
		

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












