#pragma once
/*
	封装OpenGL底层，专用于绘制、渲染，提供渲染接口，实现对图形的渲染、绘制。
*/

#ifndef RENDERER_H
#define RENDERER_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"shader.h"
#include"texture.h"


class Renderer
{
public:
	Renderer(Shader shader);
	~Renderer();

	void Draw(Texture& texture, glm::vec2 position, glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));

private:
	Shader shader;
	GLuint VAO;
	void initRenderer();
};

#endif // !RENDERER_H
