#include "Singleton.h"
#include <string>
#include <sstream>
#include <windows.h>
#include <iostream>
#include <malloc.h>

using namespace std;

Singleton* Singleton::single = NULL;

Singleton* Singleton::getInstance()
{
	if (single == NULL)
		single = new Singleton();
	return single;
}

Singleton::Singleton()
{
	samus = new CTexture("Resources/samusRun.png", 4, 1, 4);
}

CTexture* Singleton::getTexture(EnumID id)
{
	switch (id)
	{
	case EnumID::Samus_ID:
		return samus;
	}
}