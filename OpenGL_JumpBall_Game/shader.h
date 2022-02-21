#pragma once
/*
	��װOpenGL�ײ��API,�ṩ��shader��ͳһ����
*/


#ifndef SHADER_H
#define SHADER_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include<string>

class Shader
{
public:
	GLint ID;		//shader id 

	Shader() = default;
	~Shader() = default;

	Shader& Use();	//ʹ��shader�Ľӿ�
	void Compile(const GLchar* vertexCode, const GLchar* fragmentCode);	//����SHADER

	void SetVector2f(const GLchar* name, GLfloat x, GLfloat y, GLboolean useShader = false);
	void SetVector2f(const GLchar* name, const glm::vec2& value, GLboolean useShader = false);
	void SetVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
	void SetVector3f(const GLchar* name, const glm::vec3& value, GLboolean useShader = false);
	void SetVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
	void SetVector4f(const GLchar* name, const glm::vec4& value, GLboolean useShader = false);
	void SetMatrix4(const GLchar* name, const glm::mat4& matrix, GLboolean useShader = false);
	void SetInteger(const GLchar* name, GLint value, GLboolean useShader = false);

private:
	void CheckLink(GLint Object, std::string str);//���Ӽ����
};

#endif // !SHADER_H
