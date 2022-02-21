#include"texture.h"

Texture::Texture()
	:width(0), height(0), NEW_IMAGE_FORMAT(GL_RGB), OLD_IMAGE_FORMAT(GL_RGB), WRAP_S(GL_REPEAT), WRAP_T(GL_REPEAT), MIN_FILTER(GL_LINEAR), MAG_FILTER(GL_LINEAR)
{
	glGenTextures(1, &ID);
}

void Texture::Create(GLint width, GLint height, unsigned char* data)
{
	/*���ذ�����*/
	this->width = width;
	this->height = height;
	glBindTexture(GL_TEXTURE_2D, this->ID);
	glTexImage2D(GL_TEXTURE_2D, 0, NEW_IMAGE_FORMAT, width, height, 0, OLD_IMAGE_FORMAT, GL_UNSIGNED_BYTE, data);

	/*����������ˡ����Ʒ�ʽ*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WRAP_S);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WRAP_T);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, MIN_FILTER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, MAG_FILTER);
}

void Texture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, ID);
}