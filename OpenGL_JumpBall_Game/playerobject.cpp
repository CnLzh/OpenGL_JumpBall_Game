#include "playerobject.h"

PlayerObject::PlayerObject()
	: Position(200, 1100), Size(100, 100), Velocity(1.0f, 2.2f), Color(1.0f), Rotation(0.0f), texture(), isUp(false), isDown(false)
{

}

PlayerObject::PlayerObject(Texture texture)
	: Position(200, 1100), Size(100, 100), Velocity(1.0f, 2.2f), Color(1.0f), Rotation(0.0f), texture(texture), isUp(false), isDown(false)
{

}

void PlayerObject::Draw(Renderer& renderer)
{
	GetRotation();
	Move();
	renderer.Draw(this->texture, this->Position, this->Size, this->Rotation, this->Color);
}

void PlayerObject::GetRotation()
{
	Rotation += 2 * dt * PI;
}

void PlayerObject::Move()
{
	if (isUp)
	{
		Position.y -= 1000 * dt + speed;
		if (Position.y <= 750)
		{
			isUp = false;
			isDown = true;
		}
	}

	if (isDown)
	{
		Position.y += 1000 * dt + speed;
		if (Position.y >= 1100)
		{
			Position.y = 1100;
			isDown = false;
		}
	}
}

void PlayerObject::ResizeDt(float dt, float speed)
{
	this->dt = dt;
	this->speed = speed;
}