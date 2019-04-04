#include <iostream>
#include <conio.h>
#include "DataBase.h"
#include "View.h"


int main() {
	
	DataBase db;

	View view(db.getData());

	if (!view.login()) return 0; 





	int key;
	while (true)
	{
		view.render();
		key = _getch();
		

		if (view.viewActive == view.Menu::EDITITEM) {
			if (key == 8) {
				view.editedField = view.editedField.substr(0, view.editedField.size() - 1);
			}
			else if (key == 13) {
				view.data->products[view.itemsSelect].setValue(view.fieldSelect, view.editedField);
				db.save(view.data);
				view.viewActive = view.Menu::DETAILITEM;
			}
			else {

				view.editedField += char(key);
			}

			continue;
		}


		if (key == 13) {
			if (view.viewActive == view.Menu::LISTITEMS) {
				view.viewActive = view.Menu::DETAILITEM;
			} else if (view.viewActive == view.Menu::DETAILITEM) {
				if (view.fieldSelect == 5) {
					view.viewActive = view.Menu::LISTITEMS;

				} else {

				view.viewActive = view.Menu::EDITITEM;
				view.editedField = "";
				}

			}
		}


		if (key == 224) {
			switch (_getch()){
			case 72: // UP
				view.cursorUp();
				break;

			case 77: // LEFT
				view.menuActive = !view.menuActive;
				break;

			case 80: // RIGHT
				view.cursorDown();
				break;

			case 75: // RIGHT
				view.menuActive = !view.menuActive;
				break;
			}
		}
	}
	

	system("pause");
	return 0;
}