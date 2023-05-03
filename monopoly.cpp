#include <process.h>
#include <iostream>

#include "manager.h"
#include "user.h"


int main()
{
	system("title Монополия");
	system("mode 110,47");

	Manager manager;
	manager.NewGame();
	manager.Run();

	//system("pause");
	return 0;
}
