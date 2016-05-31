#include "KeyboardManager.h"

//


KeyboardManager::KeyboardManager() 
{
	for (int i = 0; i < 1024; ++i)
		keys[i] = false;
}


KeyboardManager::~KeyboardManager()
{
}



