#pragma once


/*
	粒子系统，用于渲染特效
*/


#ifndef PARTICLE_GENERATOR_H
#define PARTICLE_GENERATOR_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "shader.h"
#include "texture.h"
#include "gameobject.h"
#include "playerobject.h"

#include <vector>



struct Particle {
	glm::vec2 Position, Velocity;
	glm::vec4 Color;
	GLfloat Life;

	Particle() : Position(0.0f, 0.0f), Velocity(0.0f, 0.0f), Color(1.0f), Life(0.0f) { }
};


class ParticleGenerator
{
public:
	ParticleGenerator(Shader shader, Texture texture, GLuint amount);
	void Update(GLfloat dt, PlayerObject& object, GLuint newParticles, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
	void Draw();

private:
	std::vector<Particle> particles;

	GLuint amount;

	Shader shader;

	Texture texture;

	GLuint VAO;

	void init();

	GLuint firstUnusedParticle();

	void respawnParticle(Particle& particle, PlayerObject& object, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
};

#endif