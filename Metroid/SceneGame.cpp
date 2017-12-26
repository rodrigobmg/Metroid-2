
#include "SceneGame.h"

SceneGame::SceneGame(void) : Scene(ESceneState::Game_Scene)
{
	camera = new CCamera();
	bg = NULL;
	_levelNow = 1;
}

void SceneGame::LoadLevel(int level)
{
	camera->viewport.y = 480;
	//camera->viewport.x = 1023;

	bg = new QBackground(level);

	samus = new Samus(1264, 250);  //1264
}

void SceneGame::LoadStage()
{
	qGameObject = new QGameObject("Resources\\Maps\\demoMap\\demoMap_GameObj.txt");
	camera->SetSizeMap(G_MaxSize, G_MinSize);
}

void SceneGame::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int deltaTime)
{
	samus->Collision(*(qGameObject->_staticObject), deltaTime);


	G_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	samus->Update(deltaTime);
	camera->UpdateCamera(samus->posX);
	
	bg->Draw(camera);	
	samus->Draw(camera);

	G_SpriteHandler->End();
	
	//render info
	arial->onLost();
	arial->render("viewport x - y: ", 10, 10);
	arial->render(camera->viewport.x, 120, 10);
	arial->render(camera->viewport.y, 180, 10);
	arial->render(samus->posX, 240, 10);
	arial->render(samus->posY, 300, 10);
	arial->render(1000/deltaTime,380, 10);
}

void SceneGame::ProcessInput(int keyCode)
{
	switch (keyCode)
	{
		case DIK_RIGHT:
		case DIK_D:
			samus->TurnRight();
			break;
		case DIK_LEFT:
		case DIK_A:
			samus->TurnLeft();
			break;
		case DIK_UP:
		case DIK_W:
			samus->TurnUp();
			break;
		default:
			samus->Stop();
			break;
	}
}


void SceneGame::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
	srand((unsigned)time(NULL));

	D3DXCreateSprite(d3ddv, &G_SpriteHandler);

	HRESULT res = D3DXCreateSprite(d3ddv, &G_SpriteHandler);
	arial = new CText(d3ddv, 22, G_ScreenWidth, G_ScreenHeight);

	LoadLevel(_levelNow);
	LoadStage();

}

void SceneGame::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_X:
		samus->Jump();
		break;
	case DIK_DOWN:
	case DIK_S:
		samus->Roll();
		break;
	case DIK_Z:
		samus->Shot();
		break;
	}
}

SceneGame::~SceneGame(void)
{
	if (camera != NULL)
		delete camera;
}
