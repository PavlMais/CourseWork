#include <iostream>
#include <conio.h>
#include "DataBase.h"
#include "View.h"


int main() {
	
	DataBase db;

	View view(db.getData());

	//if (!view.login()) return 0; 





	int key;
	while (true)
	{
		view.render();
		key = _getch();
		


		if (key == 13) {
			if (view.menuActive == "listItems") {
				view.itemOpen = true;
			}
		}


		if (key == 224) {
			switch (_getch()){
			case 72: // UP
				if (view.menuActive == "menu") view.menuSelect--;
				else view.itemsSelect--;

				break;

			case 77: // LEFT
				//view.menuActive = !view.menuActive;
				break;

			case 80: // 
				if (view.menuActive == "menu") view.menuSelect++;
				else view.itemsSelect++;
			

				break;

			case 75: // RIGHT
				//view.menuActive = !view.menuActive;
				break;



			default:
				break;
			}
		}
	}
	






	system("pause");
	return 0;
}