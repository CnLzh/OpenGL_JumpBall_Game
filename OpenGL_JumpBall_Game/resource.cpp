#include"resource.h"
#include"stb_image.h"

/*静态变量初始化*/
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
	/*读取的SHADER流文件*/
	std::string vertexCode;
	std::string fragmentCode;

	try
	{
		/*文件流控制*/
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		/*保证可以抛出异常*/
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		/*打开文件流*/
		vShaderFile.open(VertexShaderFile);
		fShaderFile.open(FragmentShaderFile);
		/*读取文件缓冲内容到数据流*/
		std::stringstream vertexShaderStream, fragmentShaderStream;
		vertexShaderStream << vShaderFile.rdbuf();
		fragmentShaderStream << fShaderFile.rdbuf();
		/*关闭文件流*/
		vShaderFile.close();
		fShaderFile.close();
		/*转换数据流到string*/
		vertexCode = vertexShaderStream.str();
		fragmentCode = fragmentShaderStream.str();
	}
	catch (const std::ifstream::failure e)
	{
		std::cout << "ERROR:读取SHADER文件失败" << std::endl;
	}
	/*转成C风格字符串*/
	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();
	/*创建SHADER*/
	Shader shader;
	shader.Compile(vShaderCode, fShaderCode);

	return shader;
}

Texture Resource::GetTextureFile(const GLchar* file, GLboolean alpha)
{
	Texture texture;

	/*是否启用RGBA 4通道*/
	if (alpha)
	{
		texture.OLD_IMAGE_FORMAT = GL_RGBA;
		texture.NEW_IMAGE_FORMAT = GL_RGBA;
	}
	/*加载图片*/
	int width, height, nrChannels;
	unsigned char* image = stbi_load(file, &width, &height, &nrChannels, 0);

	/*创建纹理*/
	texture.Create(width, height, image);

	/*释放图片*/
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