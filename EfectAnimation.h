#pragma once
#include "GameObject.h"

class EfectAnimation : public Game::Efect
{
public:
	EfectAnimation(const string& name = "", const string& path = ".txt");

	void onInit() override;

	void onUpdate(float dt) override;

	enum
	{
		release,
		under,
		awaiting,
		returns
	}state;

	Animation& getAnimation()
	{
		return getOwner()->getAnimation(name);
	}

	string path, name;

	void press()
	{
		isPressed = true;
	}

private:
	bool isPressed;
};

