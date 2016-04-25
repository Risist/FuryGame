#pragma once
#include "GameObject.h"
#include "ControlInput.h"

class EfectDebugCollider : public Game::Efect
{
public:
	EfectDebugCollider( const Control::Input& _input = Control::Input(), const Color& _color = Color::White, const Color& _colorOnColision = Color::Black);

	void onDisplay(Camera&cam) override;
	void onCollision(const ColliderInfo& otherCollider) override;
	
	Control::Input input;
	Color color, colorOnCollision;

private:
	bool colliding;
};

