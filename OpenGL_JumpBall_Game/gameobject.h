#pragma once
/*
	障碍物类。
	为game提供对障碍物的管理。
*/

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"texture.h"
#include"renderer.h"
#include"resource.h"

#include<time.h>

class GameObject
{
public:
	glm::vec2 Position, Size, Velocity;
	glm::vec3 Color;
	GLfloat Rotation;
	Texture texture;
	GLfloat dt = 1000.0f;

	GameObject();
	GameObject(Texture& texture);

	void Draw(Renderer& renderer);

private:
	void RandColor();
};

#endif // !GAMEOBJECT_H
