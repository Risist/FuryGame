#pragma once
#include "GameEfect.h"
#include "GameCompetitor.h"


/*
brief description:
Adds basic third person players movement behaviour.
Addictionaly locks camera on the player with taken offset.

requiments:
there is assumed that owner is an Competitor

class use 4 keys:
up, down, left, right
and addictionaly drag informations

parametrs to set:
movementSpeed - how fast owner will move in any direction
rotationSpeed - how fast owner will rotate
cameraOffset - where camera will be placed 

*/
class EfectTppMovement : public Game::Efect
{
public:
	EfectTppMovement(float movementSpeed = 1, float rotationSpeed = 1);

	void onUpdate(float dt) override;
	void onDisplay(Camera& cam) override;


	Game::Competitor*  getOwner()
	{
		return (Game::Competitor*)Game::Efect::getOwner();
	}

	float movementSpeed, rotationSpeed;

};

