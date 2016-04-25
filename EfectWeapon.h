#pragma once
#include "efects.h"
#include "GameCompetitor.h"
#include "GameMultiEfectNoInteract.h"

class EfectWeapon : public Game::MultiEfectNoInteract
{
public:
	EfectWeapon( sf::Sprite* handSprite = nullptr, const string& animCodeX = "x", const string& animCodeY = "y");

	Game::Competitor* getOwner()
	{
		return (Game::Competitor*)Game::Efect::getOwner();
	}

	virtual void wear(){}
	virtual void unwear(){}
	


	void onInit() override;
	void onUpdate(float dt) override;

	float strenghtX, strenghtY;
	
	EfectModel * efModel;
	sf::Sprite *handSprite;
	string animCodeX, animCodeY;
	size_t idColiderMin;
	int idColiderMax;

	Resource<float>& getResX()
	{
		return getOwner()->getResource_f(idResX);
	}
	Resource<float>& getResY()
	{ 
		return getOwner()->getResource_f(idResY);
	}
	size_t idResX, idResY;

	void press()
	{
		pressed = true;
	}
protected:
	bool pressed;
};

