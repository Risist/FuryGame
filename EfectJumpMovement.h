#pragma once
#include "GameCompetitor.h"
#include "EfectTppMovement.h"
#include "control.h"

class EfectJumpMovement : public EfectTppMovement
{
public:
	EfectJumpMovement(float speed = 0, const string& jumpKeyCode = "jump", size_t resid = 0, float minimalCd = 1, float scaleCd = 1, float jumpTime = 0.25, float cost = 1);

	void onInit() override;

	void onUpdate(float dt) override;

	string jumpKeyCode;
	Control::Timer jumpCd;
	Control::Timer timerJump;

	float cost, minimalCd, scaleCd;

	Resource<float>& getRes()
	{
		return getOwner()->getResource_f(resId);
	}

private:
	// false - awaiting to activation
	// true - at movement
	bool state;
	size_t resId;
};

