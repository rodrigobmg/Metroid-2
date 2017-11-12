#ifndef _BULLET_H_
#define _BULLET_H_

#include "DynamicObject.h"

class Bullet : public DynamicObject
{
public:
	Bullet(void);
	Bullet(float x, float y, float direct, EnumID id);
	void Draw(CCamera*, int posX, int posY);
	void Update(int dt);
	~Bullet(void);
};

#endif