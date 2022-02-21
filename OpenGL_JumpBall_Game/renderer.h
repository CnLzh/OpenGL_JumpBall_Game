#pragma once
/*
	��װOpenGL�ײ㣬ר���ڻ��ơ���Ⱦ���ṩ��Ⱦ�ӿڣ�ʵ�ֶ�ͼ�ε���Ⱦ�����ơ�
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
