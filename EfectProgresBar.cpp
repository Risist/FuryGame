#include "EfectProgresBar.h"


EfectProgresBar::EfectProgresBar(Evaluate::Base *_evaluate, Gui::ProgresBar *_pb)
	:evaluate(_evaluate), pb(_pb)
{
}
EfectProgresBar::~EfectProgresBar()
{
	if (evaluate != nullptr)
		delete evaluate;
}

void EfectProgresBar::onInit()
{
	Efect::onInit();

	gui.add(pb );
}

void EfectProgresBar::onUpdate(float dt)
{
	Efect::onUpdate(dt);

	if (evaluate == nullptr)
		return;

	pb->setProgres(evaluate->evaluate(getOwner()));
}