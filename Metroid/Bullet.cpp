#include "Bullet.h"

#define SPEED_X 0.7f

Bullet::Bullet(void)
{
}

Bullet::Bullet(float x, float y, float direct, EnumID id) : DynamicObject(x, y, 0, 0, id)
{
	if (direct > 0)
		vX = SPEED_X;
	else
	{
		vX = -SPEED_X;
	}
	active = true;
}

void Bullet::Draw(CCamera* camera, int samus_posX, int samus_posY)
{
	if (sprite == NULL || !active)
		return;
	//nếu đạn bay xa hơn so với samus 1 khoảng >= 128 thì deactive đạn
	if (posX - samus_posX >= 128 || samus_posX - posX  >= 128) 
	{
		active = false;
		return;
	}
	D3DXVECTOR2 center = camera->Transform(posX, posY);
	if (vX > 0)
		sprite->Draw(center.x, center.y);
	else
		sprite->DrawFlipX(center.x, center.y);
}

void Bullet::Update(int dt)
{
	if (sprite == NULL || !active)
		return;
	posX += vX*dt;
	posY += vY*dt;
}

Bullet::~Bullet(void)
{
}
