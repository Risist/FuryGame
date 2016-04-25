#pragma once
#include "GameObject.h"
#include "control.h"

class EfectDebugStat : public Game::Efect
{
public:
	EfectDebugStat(int resourceId = 0, bool f_v2 = true, const string& description = "unknown", const Control::Input& inputCheckAll = Control::Input() );

	void onUpdate(float dt) override;
	void onInteract(float value, size_t resourceId, Game::Object* other) override;
	void onInteract(const Vector2D& value, size_t resourceId, Game::Object* other) override;


	int resourceId;
	bool f_v2;
	string description;

	Control::Input inputCheckAll;

};

