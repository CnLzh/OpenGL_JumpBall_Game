#pragma once
/*
	��װOpenGL�ײ�ӿڣ����ڶ������ͳһ����
*/

#ifndef TEXTURE_H
#define TEXTURE_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>

class Texture
{
public:
	unsigned int ID;		//����ID
	GLint width, height;	//����
	GLint WRAP_S;		//s��
	GLint WRAP_T;		//t��
	GLint MIN_FILTER;	//������С���˷�ʽ
	GLint MAG_FILTER;	//����Ŵ���˷�ʽ
	GLint NEW_IMAGE_FORMAT;	//ͼƬͨ����ʽ
	GLint OLD_IMAGE_FORMAT;	//ԭͼͨ����ʽ

	Texture();
	~Texture() = default;
	void Create(GLint width, GLint height, unsigned char* data);	//��������
	void Bind() const;	//������
};

#endif // !TEXTURE_H
