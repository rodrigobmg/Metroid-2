#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include "CTexture.h"
#include "CEnum.h"

class Singleton
{
private:
	CTexture* samus;
	CTexture* samusDeath;
	CTexture* samusJump1;
	CTexture* samusJump2;
	CTexture* samusRoll;
	CTexture* samusShotUp;
	CTexture* samusShot;

	static Singleton *single;
	Singleton();

public:
	static Singleton* getInstance();
	~Singleton();
	CTexture* getTexture(EnumID id);
};

#endif#pragma once
