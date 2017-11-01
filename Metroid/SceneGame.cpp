
#include "SceneGame.h"

#define BACKGROUND_FILE "Resources/black.png"
#define BACKGROUND_WHITE_FILE "Resources/white.png"

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

	samus = new Samus(1264, 129);
}

void SceneGame::LoadStage()
{
	camera->SetSizeMap(G_MaxSize, G_MinSize);
}

void SceneGame::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int deltaTime)
{

	
	G_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	samus->Update(deltaTime);
	camera->UpdateCamera(samus->posX);
	

	bg->Draw(camera);	
	samus->Draw(camera);

	G_SpriteHandler->End();
	
	
	
	

	arial->onLost();
	arial->render("viewport y: ", 10, 10);
	arial->render(camera->viewport.y, 120, 10);
	arial->render(camera->viewport.x, 180, 10);
	arial->render(samus->posX, 240, 10);
	arial->render(1000/deltaTime,300, 10);
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
		default:
			samus->Stop();
			break;
	}
}

void SceneGame::ResetLevel()
{
	
}

void SceneGame::ChangeCamera(EDirectDoor _directDoor)
{
	

}

void SceneGame::MoveCamera(int &_moveRange)
{
	
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
	
}

SceneGame::~SceneGame(void)
{
	if (camera != NULL)
		delete camera;
}
