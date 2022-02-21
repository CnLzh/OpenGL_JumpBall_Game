#pragma once
/*
	对整个游戏进程状态、渲染等的管理。为外部提供唯一调用接口。
*/


#ifndef GAME_H
#define GAME_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"resource.h"
#include"renderer.h"
#include"gameobject.h"
#include"playerobject.h"
#include"particle_generator.h"
#include <irrklang/irrKlang.h>


#include<iostream>
#include<list>
#include<time.h>

/*游戏状态*/
enum GameState {
	GAME_BEGIN,	//开始
	GAME_END		//胜利
};

/*游戏类*/
class Game
{
public:
	GameState state;			//游戏状态
	GLint width, height;		//窗口高度，宽度

	float dt = 0.0f;

	std::list<GameObject> obj;	//障碍物


	Game(GLint width, GLint height);	//构造函数
	~Game();							//析构函数

	void Init();

	void Render();

	void Move();

	bool AllowMove();

	void ResizeDt(float deltaTime);

private:
	void RandAdd();

	GLboolean CheckCollision(GameObject& GameObj);

	void RandGameObjectSize(GameObject& GameObj);

	void RandAddFly(GameObject& GameObj);


};

#endif // GAME_H
