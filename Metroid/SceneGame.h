#ifndef _SCENE1_H_
#define _SCENE1_H_

#include "QBackground.h"
#include "QGameObject.h"
#include "Scene.h"
#include "Samus.h"
#include "CText.h"
using namespace std;

class SceneGame : public Scene
{
public:
	int _levelNow;
	int _stageNow;

	bool _loadLevel;

	SceneGame();
	~SceneGame();
protected:

	QBackground *bg;
	QGameObject* qGameObject;
	Samus* samus;
	CCamera *camera;
	CText* arial;

	void LoadLevel(int level);
	void LoadStage();
	void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t);
	void ProcessInput(int keyCode);
	void LoadResources(LPDIRECT3DDEVICE9 d3ddv);
	void OnKeyDown(int KeyCode);
};
#endif

#pragma once
