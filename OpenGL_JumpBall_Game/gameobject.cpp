#include"gameobject.h"

GameObject::GameObject()
	: Position(1900, 1000), Size(100, 200), Velocity(0.0f), Color(1.0f), Rotation(0.0f), texture()
{
	RandColor();
}

GameObject::GameObject(Texture& texture)
	: Position(1900, 1000), Size(100, 200), Velocity(0.0f), Color(1.0f), Rotation(0.0f), texture(texture)
{
	RandColor();
}


void GameObject::RandColor()
{
	srand((int)time(0));
	Color.x = rand() / double(RAND_MAX);
	Color.y = rand() / double(RAND_MAX);
	Color.z = rand() / double(RAND_MAX);
	if (Color.x <= 0.4 && Color.y <= 0.4 && Color.z <= 0.4)
	{
		Color.x += 0.4;
		Color.y += 0.4;
		Color.z += 0.4;
	}

}

void GameObject::Draw(Renderer& renderer)
{
	renderer.Draw(this->texture, this->Position, this->Size, this->Rotation, this->Color);
}