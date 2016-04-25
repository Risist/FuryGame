#pragma once
#include "Particle.h"

class ParticleGenerator
{
public:
	ParticleGenerator();
	~ParticleGenerator();

	void update(float dt, const Sprite& connectedTo = Sprite(), const Vector2D& posRot = Vector2D() );
	void display(Camera& cam, const Sprite& connectedTo = Sprite());
	void display(RenderWindow& wnd, const Sprite& connectedTo = Sprite());

	void addParticle(const string& path, size_t amount = 1, float delay = 1.f, float begginsFrom = 0.f, const sf::Sprite& connectedTo = sf::Sprite(), const Vector2D& posRot = Vector2D() );

	vector<Particle*> particles;
private:
	string constructionScript;
	size_t begginFrom;
};

