#pragma once
/*
	��������Ϸ����״̬����Ⱦ�ȵĹ���Ϊ�ⲿ�ṩΨһ���ýӿڡ�
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

/*��Ϸ״̬*/
enum GameState {
	GAME_BEGIN,	//��ʼ
	GAME_END		//ʤ��
};

/*��Ϸ��*/
class Game
{
public:
	GameState state;			//��Ϸ״̬
	GLint width, height;		//���ڸ߶ȣ����

	float dt = 0.0f;

	std::list<GameObject> obj;	//�ϰ���


	Game(GLint width, GLint height);	//���캯��
	~Game();							//��������

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
