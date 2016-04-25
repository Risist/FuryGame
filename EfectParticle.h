#pragma once
#include "GameEfect.h"
#include "ParticleGenerator.h"

/*
brief description:
simple graphical efect which play taken particle efect all the time

reqiments: none

constructor parametrs:
pathParticle - path to constructionScript of particles
nParticle - how much particles to add
offsetParticle - how big offset every particle has
animationSpeed - how fast live cycle of particles is played
connectedToUpdate - each particle in incomming into new live circle has statistics relative to this sprite
connectedToDisplay - each particle has statistics relative to this sprite
*/
class EfectParticle : public Game::Efect
{
public:
	EfectParticle(const string& pathParticle, size_t nParticle = 1, float offsetParticle = 1, float animationSpeed = 1, float begginsFrom = 0, Sprite* connectedToUpdate = nullptr, Sprite* connectedToDisplay = nullptr);

	void onInit() override;
	
	void onUpdate(float dt) override;
	void onDisplay(Camera& cam) override;

	ParticleGenerator gen;

	// if equal to nullptr uses Default sprite - sf::Sprite()
	// each particle in incomming into new live circle has statistics relative to this sprite
	Sprite *connectedToUpdate;

	// if equal to nullptr uses Default sprite - sf::Sprite()
	// each particle has statistics relative to this sprite
	Sprite *connectedToDisplay;


	// how fast live cycle of particles is played
	float animationSpeed;

};

