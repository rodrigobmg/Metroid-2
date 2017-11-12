#ifndef _SIMON_H_
#define _SIMON_H_

#include "DynamicObject.h"
#include "Bullet.h"

class Samus : public DynamicObject
{
public:
	list<Bullet*> *bullet;

	CSprite* _samusSprite;
	CSprite *samusJump1;
	CSprite *samusJump2;
	CSprite *samusRoll;
	CSprite *samusShotUp;
	CSprite *samusShot;

	float _vLast;
	Action _action;

	bool _hasJump;
	float _heightJump;

	bool _hasShot;

	bool _allowPress;		//Cho phep nhan phim
	bool _hasRoll;
	bool _hasTurnUp;
	bool _isDraw;
	
	//----------------Khoi Tao
	Samus(void);
	Samus(int, int);

	~Samus(void);
	//----Samus Action----------------
	void Update(int deltaTime);
	void TurnLeft();
	void TurnRight();
	void Jump();
	void Stop();
	void Roll();
	void TurnUp();
	void Shot();
	void Draw(CCamera*);
	void Initialize();
	D3DXVECTOR2* getPos();
	
};

#endif
