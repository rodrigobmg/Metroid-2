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
	samusJump1 = new CTexture("Resources/samusJump1.png", 1, 1, 1);
	samusJump2 = new CTexture("Resources/samusJump2.png", 4, 1, 4);
	samusRoll = new CTexture("Resources/samusRoll.png", 4, 1, 4);
	samusShotUp = new CTexture("Resources/samusShotUp.png", 6, 1, 6);
	samusShot = new CTexture("Resources/samusShot.png", 5, 1, 5);
	bullet = new CTexture("Resources/Weapon/bullet.png", 1, 1, 1);
}

CTexture* Singleton::getTexture(EnumID id)
{
	switch (id)
	{
		case EnumID::Samus_ID:
			return samus;
		case EnumID::SamusJump1_ID:
			return samusJump1;	
		case EnumID::SamusJump2_ID:
			return samusJump2;
		case EnumID::SamusRoll_ID:
			return samusRoll;
		case EnumID::SamusShotUp_ID:
			return samusShotUp;
		case EnumID::SamusShot_ID:
			return samusShot;
		case EnumID::Bullet_ID:
			return bullet;
	}
}