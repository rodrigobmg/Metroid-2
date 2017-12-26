#include "Samus.h"

#define SPEED_X 0.4f
#define SPEED_Y 0.6f
#define MAX_HEIGHT 150.0f

Samus::Samus(void) : DynamicObject()
{
}

Samus::Samus(int _posX, int _posY) : DynamicObject(_posX, _posY, 0, -SPEED_Y, EnumID::Samus_ID)
{
	_action = Action::Idle;
	_allowPress = true;
	_vLast = 0.2f;
	_hasJump = false;
	_hasRoll = false;
	_hasTurnUp = false;
	_hasShot = false;
	_heightJump = 0.0f;
	_isDraw = true;
	_demVaCham = 0;
	_lastCollidedGround = nullptr;
	bullet = new list<Bullet*>();;
	samusJump1 = new CSprite(Singleton::getInstance()->getTexture(EnumID::SamusJump1_ID), 0, 0, 300);
	samusJump2 = new CSprite(Singleton::getInstance()->getTexture(EnumID::SamusJump2_ID), 0, 3, 10);
	samusRoll = new CSprite(Singleton::getInstance()->getTexture(EnumID::SamusRoll_ID), 0, 3, 10);
	samusShotUp = new CSprite(Singleton::getInstance()->getTexture(EnumID::SamusShotUp_ID), 1, 3, 20);
	samusShot = new CSprite(Singleton::getInstance()->getTexture(EnumID::SamusShot_ID), 1, 3, 20);
	Initialize();
}

void Samus::Update(int deltaTime)
{
	//List các đạn được bắn
	list<Bullet*>::iterator it = bullet->begin();
	while (it != bullet->end())
	{
		if (!(*it)->active)
			bullet->erase(it++); //xóa đạn khi đạn ko còn active
		else
		{
			(*it)->Update(deltaTime);
			++it;
		}
	}

	switch (_action)
	{
	case Action::Run_Left:
		sprite->Update(deltaTime);
		break;
	case Action::Run_Right:
		sprite->Update(deltaTime);
		break;
	}

	//Update vị trí
	posX += vX *deltaTime;
	posY += vY *deltaTime;

	//Nhảy
	if (_hasJump)
	{
		samusJump2->Update(deltaTime); //tạm thời set jump của samus là kiểu nhảy 2
		_heightJump += vY * deltaTime;
		if (_heightJump >= MAX_HEIGHT) //nếu nhảy lên max height thì cho rớt xuống
		{
			vY = -(SPEED_Y);
		}
		////if (posY < 129) //nếu chạm đất (tạm thời set đất là 129 do chưa xét collision)
		////{
		////	vY = 0;
		////	vX = 0;
		////	posY = 129;
		////	_hasJump = false;
		////}
	}

	//Lăn tròn
	if (_hasRoll)
	{
		samusRoll->Update(deltaTime);

	}

	//Bắn lên
	////if (_hasTurnUp)
	////{
	////	posY = 135;  //tạm thời set posY = 135
	////	if (_action == Action::Run_Left || _action == Action::Run_Right)		
	////		samusShotUp->Update(deltaTime);
	////}
	////else if (!_hasJump) posY = 129;

	//Bắn
	if (_hasShot)
	{
		//Nếu vừa chạy vừa bắn
		if (_action == Action::Run_Left || _action == Action::Run_Right)
			samusShot->Update(deltaTime);
	}
}

Box Samus::GetBox()
{
	if (_hasJump && _heightJump >= MAX_HEIGHT / 2)  //???????
	{
		return Box(posX - width / 2 + 14.5f, posY + height / 2 - 3, width - 29, height - 34);
	}
	return Box(posX - width / 2 + 14.5f, posY + height / 2 - 3, width - 10, height - 18);
}

void Samus::Collision(list<GameObject*> &obj, float dt)
{
	for (list<GameObject*>::iterator _itBegin = obj.begin(); _itBegin != obj.end(); _itBegin++)
	{
		GameObject* other = (*_itBegin);

		float moveX;
		float moveY;

		Box boxSamus = this->GetBox();
		Box boxOther = other->GetBox();
		_allowPress = true;
		if (AABB(boxSamus, boxOther, moveX, moveY) == true)
		{
			_demVaCham++;

			switch (other->id)
			{
#pragma region
			case EnumID::Ground1_ID:
			case EnumID::Ground4_ID:
			case EnumID::Ground6_ID:
			{
				//_onMovingPlatform = false;
				
				ECollisionDirect dir = this->GetCollisionDirect(other);
				if (dir == ECollisionDirect::Colls_Left || dir == ECollisionDirect::Colls_Right) {
					
					if (_curCollideDir == dir)
					{
						vX = 0;
					}
					
					_curCollideDir = dir;
					_sideCollidedGround = other;
					//posX += moveX;
					
					//vX = 0;
				}
				else if (_sideCollidedGround == other)
				{
					_curCollideDir = ECollisionDirect::Colls_None;
					_sideCollidedGround = nullptr;
				}
				
				_lastCollidedGround = other;
				if (moveY > 0)
				{
					posY += moveY;
					if ((_hasJump))
					{
						_hasJump = false;

						vY = 0;
						vX = 0;
					}
					else
					{
						vY = 0;
						onLand = true;

					}
				}



				//Xu ly rot khoi cuc gach
				if ((!onLand) && !_hasJump)
				{
					vY = -(SPEED_Y);
				}
				break;
#pragma endregion Va cham Gach
			}
			default:

				break;
			}
		}
		else if (_lastCollidedGround == other && !_hasJump) 
		{
			_lastCollidedGround = nullptr;
			onLand = false;
			vY = -(SPEED_Y);
		}
		else if (_sideCollidedGround == other)
		{
			_sideCollidedGround = nullptr;
			_curCollideDir = ECollisionDirect::Colls_None;
		}
	}
}


void Samus::Draw(CCamera* camera)
{
	D3DXVECTOR2 center = camera->Transform(posX, posY);
	//draw list đạn
	for (list<Bullet*>::iterator i = bullet->begin(); i != bullet->end(); i++)
	{
		if ((*i)->active)
			(*i)->Draw(camera, posX, posY);
	}

	if (vX > 0 || _vLast > 0)
	{
		if (_hasJump)
		{
			samusJump2->Draw(center.x, center.y);
			return;
		}
		if (_hasRoll)
		{
			samusRoll->Draw(center.x, center.y);
			return;
		}
		if (_hasTurnUp)
		{
			samusShotUp->Draw(center.x, center.y);
			return;
		}
		if (_hasShot)
		{
			samusShot->Draw(center.x, center.y);
			return;
		}
		sprite->Draw(center.x, center.y);

	}
	else
	{
		if (_hasJump)
		{
			samusJump2->DrawFlipX(center.x, center.y);
			return;
		}
		if (_hasRoll)
		{
			samusRoll->DrawFlipX(center.x, center.y);
			return;
		}
		if (_hasTurnUp)
		{
			samusShotUp->DrawFlipX(center.x, center.y);
			return;
		}
		if (_hasShot)
		{
			samusShot->DrawFlipX(center.x, center.y);
			return;
		}
		sprite->DrawFlipX(center.x, center.y);

	}
}

void Samus::TurnLeft()
{
	if (_allowPress && _curCollideDir != ECollisionDirect::Colls_Right)
	{
		vX = -SPEED_X;
		_vLast = vX;
		_action = Action::Run_Left;
		_curCollideDir = ECollisionDirect::Colls_None;
	}
}

void Samus::TurnRight()
{
	if (_allowPress && _curCollideDir != ECollisionDirect::Colls_Left)
	{
		vX = SPEED_X;
		_vLast = vX;
		_action = Action::Run_Right;
		_curCollideDir = ECollisionDirect::Colls_None;
	}
}

void Samus::Jump()
{
	if (_allowPress)
	{
		if (!_hasJump)
		{
			vY = SPEED_Y;
			_heightJump = 0;
			samusJump2->SelectIndex(0);
			_action = Action::Jump2; //tạm thời chọn kiểu jump2
			_hasJump = true;
		}
	}
}

void Samus::Roll()
{
	if (_allowPress)
	{
		_hasRoll = true;
		_action = Action::Roll;
	}
}

void Samus::TurnUp()
{
	if (_allowPress)
	{
		_hasRoll = false;
		_hasTurnUp = true;
		samusShotUp->SelectIndex(0);
	}
}

void Samus::Initialize()
{
}

void Samus::Stop()
{
	if (!_hasJump) vX = 0;
	_hasTurnUp = false;
	_hasShot = false;
	_action = Action::Idle;
	sprite->SelectIndex(0);
}


void Samus::Shot()
{
	if (_allowPress)
	{
		bullet->push_back(new Bullet(posX, posY + 11, _vLast, EnumID::Bullet_ID));
		_hasShot = true;
	}
}



Samus::~Samus(void)
{
}

D3DXVECTOR2* Samus::getPos()
{
	return new D3DXVECTOR2(this->posX, this->posY);
}


