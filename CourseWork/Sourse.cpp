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
		


		if (view.need_save) {
			db.save();
			view.need_save = false;
		}

		if (view.isfieldEdit) {
			if(view.editField(key)) db.save();
			continue;
		}

		std::cout << key;
		if (key == 102) view.isSortActive = !view.isSortActive;
		else if (key == 13) view.enter();
		


		else if (key == 224) {
			switch (_getch()){
			case 72: // UP
				view.cursorUp();
				break;

			case 77: // LEFT
				view.sortSelect--;
				//view.isMenuActive = !view.isMenuActive;

				break;

			case 80: // RIGHT
				view.cursorDown();
				break;

			case 75: // RIGHT
				view.sortSelect++;
				//view.isMenuActive = !view.isMenuActive;
				break;
			}
		}
	}
	

	system("pause");
	return 0;
}












