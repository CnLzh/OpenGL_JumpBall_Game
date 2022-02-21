#pragma once
/*
	封装shader、texture文件，用于资源管理，提供唯一初始化、调用着色器、纹理的接口。
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
	static std::map<std::string, Shader> shaders;		//着色器关联容器
	static std::map<std::string, Texture> textures;		//纹理关联容器

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
