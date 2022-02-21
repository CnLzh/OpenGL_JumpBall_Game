#include"game.h"

#include<Windows.h>

using namespace irrklang;

Renderer* renderer;

PlayerObject* Player;

ParticleGenerator* Particles;

float speed = 0.0f;

const float speedDt = 0.0003;

auto SoundEngine = createIrrKlangDevice();

Game::Game(GLint width, GLint height)
	:state(GAME_BEGIN), width(width), height(height)
{

}

Game::~Game()
{
	delete renderer;
}

void Game::Init()
{
	Resource::SetShader("shaders/sprite.vs", "shaders/sprite.frag", "sprite");
	Resource::SetShader("shaders/particle.vs", "shaders/particle.frag", "particle");

	glm::mat4 projection = glm::ortho(0.0f, GLfloat(width), GLfloat(height), 0.0f, -1.0f, 1.0f);

	Resource::GetShader("sprite").Use().SetInteger("image", 0);
	Resource::GetShader("sprite").SetMatrix4("projection", projection);

	Resource::GetShader("particle").Use().SetInteger("sprite", 0);
	Resource::GetShader("particle").SetMatrix4("projection", projection);

	Resource::SetTexture("textures/awesomeface.png", GL_TRUE, "face");
	Resource::SetTexture("textures/block.png", GL_FALSE, "block");
	Resource::SetTexture("textures/background.jpg", GL_FALSE, "background");
	Resource::SetTexture("textures/particle.png", GL_TRUE, "particle");

	renderer = new Renderer(Resource::GetShader("sprite"));
	Player = new PlayerObject(Resource::GetTexture("face"));
	Particles = new ParticleGenerator(
		Resource::GetShader("particle"),
		Resource::GetTexture("particle"),
		500
		);
	SoundEngine->play2D("audio/breakout.mp3", GL_TRUE);
}

void Game::Render()
{

	/*背景绘制*/
	Texture texture = Resource::GetTexture("background");
	renderer->Draw(texture, glm::vec2(0, 0), glm::vec2(width, height), 0.0f);


	if (state == GAME_END)
	{
		Player = new PlayerObject(Resource::GetTexture("face"));
		obj.clear();
		dt = 0.0f;
		speed = 0.0f;
		return;
	}

	/*玩家绘制*/
	Player->ResizeDt(dt, speed);
	Player->Draw(*renderer);

	/*障碍物绘制*/

	for (auto it = obj.begin(); it != obj.end();)
	{
		it->Position.x = it->Position.x - dt * it->dt - speed;

		if (it->Position.x <= Player->Position.x)
			speed += speedDt;
		if (it->Position.x <= 0)
		{
			obj.erase(it++);
		}
		else
		{
			if (CheckCollision(*it))
			{
				SoundEngine->play2D("audio/bleep.mp3", GL_FALSE);
				state = GAME_END;

			}
			it->Draw(*renderer);
			it++;
		}
	}

	/*随机生成障碍物*/
	RandAdd();

	if (Player->isUp || Player->isDown)
	{
		Particles->Update(0.005f, *Player, 2, glm::vec2(Player->Radius / 2));
		Particles->Draw();
	}

}

void Game::Move()
{
	Player->isUp = true;
	SoundEngine->play2D("audio/solid.wav", GL_FALSE);
}

void Game::RandAdd()
{
	Texture texture = Resource::GetTexture("block");

	if (obj.size() == 0)
	{
		GameObject tmp_obj(texture);
		RandGameObjectSize(tmp_obj);
		obj.push_back(tmp_obj);
	}
	else
	{
		auto it = --obj.end();
		if (it->Position.x <= 1000)
		{
			srand((int)time(0));
			int RandNum1 = rand() % 10;
			int RandNum2 = rand() % 10;
			int RandNum3 = rand() % 10;
			if (RandNum1 * RandNum2 * RandNum3 % 3 == 1)
			{
				GameObject tmp_obj(texture);
				RandGameObjectSize(tmp_obj);
				obj.push_back(tmp_obj);
			}
			else
			{
				RandNum1 = rand() % 10;
				RandNum2 = rand() % 10;
				RandNum3 = rand() % 10;
				if (RandNum1 * RandNum2 * RandNum3 % 3 == 2)
				{
					GameObject tmp_obj(texture);
					RandAddFly(tmp_obj);
					obj.push_back(tmp_obj);
				}

			}
		}


	}
}

bool Game::AllowMove()
{
	return Player->Position.y == 1100;
}

GLboolean Game::CheckCollision(GameObject& GameObj)
{
	// 获取圆的中心 
	glm::vec2 center(Player->Position + Player->Radius);
	// 计算AABB（中心、半边长）
	glm::vec2 aabb_half_extents(GameObj.Size.x / 2, GameObj.Size.y / 2);
	glm::vec2 aabb_center(
		GameObj.Position.x + aabb_half_extents.x,
		GameObj.Position.y + aabb_half_extents.y
		);
	// 获取两个中心的差矢量
	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	// AABB_center加上clamped得到了碰撞箱上距离圆最近的点closest
	glm::vec2 closest = aabb_center + clamped;
	// 获得圆心center和最近点closest的矢量并判断是否 length <= radius
	difference = closest - center;
	return glm::length(difference) < Player->Radius;
}

void Game::ResizeDt(float deltaTime)
{
	dt = deltaTime;
}

void Game::RandGameObjectSize(GameObject& GameObj)
{
	srand((int)time(0));
	int RandNum1 = rand() % 10;
	int RandNum2 = rand() % 10;
	int RandNum3 = rand() % 10;
	if (RandNum1 * RandNum2 * RandNum3 % 3 == 1)
	{
		GameObj.Size.x = GameObj.Size.x / 4 * 2;
		GameObj.Position.y += GameObj.Size.y - GameObj.Size.y / 4 * 2;
		GameObj.Size.y = GameObj.Size.y / 4 * 2;
	}
	else if (RandNum1 * RandNum2 * RandNum3 % 3 == 2)
	{
		GameObj.Size.x = GameObj.Size.x / 4 * 3;
		GameObj.Position.y += GameObj.Size.y - GameObj.Size.y / 4 * 3;
		GameObj.Size.y = GameObj.Size.y / 4 * 3;
	}

}

void Game::RandAddFly(GameObject& GameObj)
{

	srand((int)time(0));
	int RandNum1 = rand() % 10;
	int RandNum2 = rand() % 10;
	int RandNum3 = rand() % 10;

	if (RandNum1 * RandNum2 * RandNum3 % 3 == 1)
	{
		GameObj.Size.x = GameObj.Size.x / 4 * 3;
		GameObj.Position.y -= GameObj.Size.y - GameObj.Size.y / 4 * 3;
		GameObj.Size.y = GameObj.Size.y / 4 * 3;
	}
	else
	{
		GameObj.Size.x = GameObj.Size.x / 4 * 3;
		GameObj.Size.y = GameObj.Size.y / 4 * 3;

		GameObj.Rotation = glm::radians(90.0f);
	}


}