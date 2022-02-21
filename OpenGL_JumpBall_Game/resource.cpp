#include"resource.h"
#include"stb_image.h"

/*��̬������ʼ��*/
std::map<std::string, Shader>Resource::shaders;
std::map<std::string, Texture>Resource::textures;

Shader Resource::SetShader(const GLchar* VertexShaderFile, const GLchar* FragmentShaderFile, std::string name)
{
	shaders[name] = GetShaderFile(VertexShaderFile, FragmentShaderFile);
	return shaders[name];
}

Shader Resource::GetShader(std::string name)
{
	return shaders[name];
}

Texture Resource::SetTexture(const GLchar* file, GLboolean alpha, std::string name)
{
	textures[name] = GetTextureFile(file, alpha);
	return textures[name];
}

Texture Resource::GetTexture(std::string name)
{
	return textures[name];
}


Shader Resource::GetShaderFile(const GLchar* VertexShaderFile, const GLchar* FragmentShaderFile)
{
	/*��ȡ��SHADER���ļ�*/
	std::string vertexCode;
	std::string fragmentCode;

	try
	{
		/*�ļ�������*/
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		/*��֤�����׳��쳣*/
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		/*���ļ���*/
		vShaderFile.open(VertexShaderFile);
		fShaderFile.open(FragmentShaderFile);
		/*��ȡ�ļ��������ݵ�������*/
		std::stringstream vertexShaderStream, fragmentShaderStream;
		vertexShaderStream << vShaderFile.rdbuf();
		fragmentShaderStream << fShaderFile.rdbuf();
		/*�ر��ļ���*/
		vShaderFile.close();
		fShaderFile.close();
		/*ת����������string*/
		vertexCode = vertexShaderStream.str();
		fragmentCode = fragmentShaderStream.str();
	}
	catch (const std::ifstream::failure e)
	{
		std::cout << "ERROR:��ȡSHADER�ļ�ʧ��" << std::endl;
	}
	/*ת��C����ַ���*/
	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();
	/*����SHADER*/
	Shader shader;
	shader.Compile(vShaderCode, fShaderCode);

	return shader;
}

Texture Resource::GetTextureFile(const GLchar* file, GLboolean alpha)
{
	Texture texture;

	/*�Ƿ�����RGBA 4ͨ��*/
	if (alpha)
	{
		texture.OLD_IMAGE_FORMAT = GL_RGBA;
		texture.NEW_IMAGE_FORMAT = GL_RGBA;
	}
	/*����ͼƬ*/
	int width, height, nrChannels;
	unsigned char* image = stbi_load(file, &width, &height, &nrChannels, 0);

	/*��������*/
	texture.Create(width, height, image);

	/*�ͷ�ͼƬ*/
	stbi_image_free(image);
	return texture;
}

void Resource::Clear()
{
	for (auto iter : shaders)
		glDeleteProgram(iter.second.ID);
	for (auto iter : textures)
		glDeleteTextures(1, &iter.second.ID);
}