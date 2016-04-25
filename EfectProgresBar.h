#pragma once
#include "GameWorld.h"
#include "gui.h"

class EfectProgresBar : public Game::Efect
{
public:
	EfectProgresBar(Evaluate::Base *_evaluate = nullptr, Gui::ProgresBar *_pb = nullptr);
	~EfectProgresBar();

	void onInit() override;

	void onUpdate(float dt) override;

	Gui::ProgresBar *pb;
	Evaluate::Base *evaluate;
};

