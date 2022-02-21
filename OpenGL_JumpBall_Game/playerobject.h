#pragma once
/*
	玩家类。用于对玩家控制的Ball的控制，包含球类属性。
*/

#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"texture.h"
#include"renderer.h"
#include"resource.h"


class PlayerObject
{
public:
	glm::vec2 Position, Size, Velocity;
	glm::vec3 Color;
	GLfloat Rotation;
	Texture texture;
	bool isUp, isDown;

	const GLfloat PI = 3.1415926f;
	const GLfloat Radius = 50.0f;


	PlayerObject();


	PlayerObject(Texture texture);

	void Draw(Renderer& renderer);

	void ResizeDt(float dt, float speed);

private:
	void GetRotation();
	void Move();

	float dt = 0.0f;
	float speed = 0.0f;
};


#endif // !PLAYEROBJECT
