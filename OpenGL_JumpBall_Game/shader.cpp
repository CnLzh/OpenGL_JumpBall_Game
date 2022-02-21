#include"shader.h"
#include<iostream>

Shader& Shader::Use()
{
	glUseProgram(ID);
	return *this;
}

void Shader::Compile(const GLchar* vertexCode, const GLchar* fragmentCode)
{
	GLint vertex, fragment;	//顶点着色器、片段着色器ID

	/*顶点着色器*/
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexCode, NULL);
	glCompileShader(vertex);
	CheckLink(vertex, "VERTEX");

	/*片段着色器*/
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentCode, NULL);
	glCompileShader(fragment);
	CheckLink(fragment, "FRAGMENT");

	/*着色器程序*/
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	CheckLink(ID, "PROGRAM");

	/*删除着色器*/
	glDeleteShader(vertex);
	glDeleteShader(fragment);

}

void Shader::CheckLink(GLint Object, std::string str)
{
	GLint isSuccess;
	GLchar infoLog[1024];
	if (str != "PROGRAM")
	{
		glGetShaderiv(Object, GL_COMPILE_STATUS, &isSuccess);
		if (!isSuccess)
		{
			glGetShaderInfoLog(Object, 1024, NULL, infoLog);
			std::cout << "ERROR:SHADER：" << str << ":" << infoLog << std::endl << std::endl;
		}
	}
	else
	{
		glGetProgramiv(Object, GL_LINK_STATUS, &isSuccess);
		if (!isSuccess)
		{
			std::cout << "ERROR:SHADER：" << str << ":" << infoLog << std::endl << std::endl;
		}
	}

}

void Shader::SetVector2f(const GLchar* name, GLfloat x, GLfloat y, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniform2f(glGetUniformLocation(this->ID, name), x, y);
}

void Shader::SetVector2f(const GLchar* name, const glm::vec2& value, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
}

void Shader::SetVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
}

void Shader::SetVector3f(const GLchar* name, const glm::vec3& value, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
}

void Shader::SetVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniform4f(glGetUniformLocation(this->ID, name), x, y, z, w);
}

void Shader::SetVector4f(const GLchar* name, const glm::vec4& value, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z, value.w);
}


void Shader::SetMatrix4(const GLchar* name, const glm::mat4& matrix, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::SetInteger(const GLchar* name, GLint value, GLboolean useShader)
{
	if (useShader)
		this->Use();
	glUniform1i(glGetUniformLocation(this->ID, name), value);
}