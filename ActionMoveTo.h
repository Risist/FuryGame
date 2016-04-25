#pragma once
#include "Action.h"

class ActionMoveTo : public Action
{
public:
	ActionMoveTo(Game::Object **aim, float timeDiference = 0, const Vector2D& radius = Vector2D(0, 100), const Vector2D& tolerance = Vector2D(50, 50), bool useLayerX = false, bool useLayerY = false, const initializer_list< pair<Action*, float> >& initializer = {});
	ActionMoveTo(const Vector2D& position = Vector2D(), const Vector2D& radius = Vector2D(0, 100), const Vector2D& tolerance = Vector2D(50, 50));

	void update(float dt) override;
	bool done() override;


	// if difference in certain axis will be lower than tolerance 
	// owner will stop move in the direction
	Vector2D tolerance;

	// x value - minimal alowded distance to aim
	// y value - maximal alowded distance to aim
	Vector2D radius;

	// position of the aim will be tried to predict 
	// after time diference
	float timeDiference;

	// a pointner to adress of aim
	// the owner will try to look at the aim
	Game::Object **aim;

	// if aim is empty then the owner will follow the position
	Vector2D position;

	bool useLayerX, useLayerY;

private :
	bool isDone;
};

