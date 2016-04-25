#pragma once
#include "GameObject.h"
#include "control.h"

class EfectFollowAim : public Game::Efect
{
public:
	EfectFollowAim( Game::Object* aimObject = nullptr, 
		float movementSpeed = 0, float movementSpeedIncrease = 0, 
		float decisionRestartTime = 1,
		const Vector2D& minMaxDistance = Vector2D(), 
		const Vector2D& minMaxRotation = Vector2D(0,360), bool rotationAccordingToAim = false, bool debugInfo = false);

	void onUpdate(float dt) override;


	float minimalDistance, 
		maximalDistance,
		minimalRotation,
		maximalRotation;
	bool rotationAccordingToAim;
	
	Game::Object *aimObject;
	Control::Timer timerAim;
	

	float movementSpeed;
	float movementSpeedIncrease;

	void generateNewAim();

	bool debugInfo;

private:
	Vector2D aim;
};

