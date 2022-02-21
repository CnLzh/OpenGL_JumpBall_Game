#pragma once
/*
	封装OpenGL底层接口，用于对纹理的统一管理。
*/

#ifndef TEXTURE_H
#define TEXTURE_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>

class Texture
{
public:
	unsigned int ID;		//纹理ID
	GLint width, height;	//宽、高
	GLint WRAP_S;		//s轴
	GLint WRAP_T;		//t轴
	GLint MIN_FILTER;	//纹理缩小过滤方式
	GLint MAG_FILTER;	//纹理放大过滤方式
	GLint NEW_IMAGE_FORMAT;	//图片通道格式
	GLint OLD_IMAGE_FORMAT;	//原图通道格式

	Texture();
	~Texture() = default;
	void Create(GLint width, GLint height, unsigned char* data);	//创建纹理
	void Bind() const;	//绑定纹理
};

#endif // !TEXTURE_H
