#pragma once
/*
	��װshader��texture�ļ���������Դ�����ṩΨһ��ʼ����������ɫ��������Ľӿڡ�
*/

#ifndef RESOURCE_H
#define RESOURCE_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<map>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

#include "texture.h"
#include "shader.h"


class Resource
{
public:
	static std::map<std::string, Shader> shaders;		//��ɫ����������
	static std::map<std::string, Texture> textures;		//�����������

	static Shader SetShader(const GLchar* VertexShaderFile, const GLchar* FragmentShaderFile, std::string name);
	static Shader GetShader(std::string name);

	static Texture SetTexture(const GLchar* file, GLboolean alpha, std::string name);
	static Texture GetTexture(std::string name);

	static void Clear();

private:
	static Shader GetShaderFile(const GLchar* VertexShaderFile, const GLchar* FragmentShaderFile);
	static Texture GetTextureFile(const GLchar* file, GLboolean alpha);
};
#endif // !RESOURCE_H
