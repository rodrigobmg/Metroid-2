#ifndef _GROUND_H_
#define _GROUND_H_

#include "GameObject.h"
#include "CEnum.h"

class Ground : public GameObject
{
public:
	Ground(void);
	Ground(float _posX, float _posY, int _width, int _height, EnumID _id);
	~Ground(void);
};

#endif
