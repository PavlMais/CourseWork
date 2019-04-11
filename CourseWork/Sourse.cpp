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
		

		if (view.isfieldEdit) {







			if(view.editField(key)) db.save();
			continue;
		}


		if (key == 13) view.enter();
		


		else if (key == 224) {
			switch (_getch()){
			case 72: // UP
				view.cursorUp();
				break;

			case 77: // LEFT
				
				view.menuActive++;
				if (view.menuActive > 1) view.menuActive = 2;
				break;

			case 80: // RIGHT
				view.cursorDown();
				break;

			case 75: // RIGHT
				view.menuActive--;
				if (view.menuActive < 0) view.menuActive = 0;
				break;
			}
		}
	}
	

	system("pause");
	return 0;
}