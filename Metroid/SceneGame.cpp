
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
	bg = new QBackground(level);

	camera->viewport.y = 2846;
	camera->viewport.x = 1023;
}

void SceneGame::LoadStage(int stage)
{
	
}

void SceneGame::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int deltaTime)
{
	
	//Background
	d3ddv->StretchRect(
		Background,			// from 
		NULL,				// which portion?
		G_BackBuffer,		// to 
		NULL,				// which portion?
		D3DTEXF_NONE);
	G_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	bg->Draw(camera);	
	G_SpriteHandler->End();

}

void SceneGame::ProcessInput(int keyCode)
{
	
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

	LoadLevel(_levelNow);
}

void SceneGame::OnKeyDown(int KeyCode)
{
	
}

SceneGame::~SceneGame(void)
{
	if (camera != NULL)
		delete camera;
}
