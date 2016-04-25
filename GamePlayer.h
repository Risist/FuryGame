#pragma once
#include "GameCompetitor.h"
#include "Animation.h"
#include "control.h"

namespace Game
{

	class Player : public Competitor
	{
	public:

		void standardInputUpdate();
		void standardMouseUpdate(float speed = 1.f, const Vector2D& maxValue = Vector2D(1000, 1000), const Vector2D& mouseMovementLock = Vector2D(100, 100));

		bool isReadyInput(const string& name)
		{
			return inputs[name].isReady();
		}
		void setInput(const string& name, const Control::Input& s)
		{
			inputs[name] = s;
		}

	private:
		map< string, Control::Input> inputs;
		Control::MouseDrag mouseInput;
	};

}

/**
class Player : public GameObject
{
public:
	Player();

	void onInit() override;

	void onUpdate(float dt) override;
	void onDisplay(Camera& cam) override;

	Model axe;
	vector<Model*> allModelsAxe;

	float movementSpeed;
	float atack1Speed, atack2Speed;

	Control::Input keyUp, keyDown, keyLeft, keyRight;
	Control::Input keyAt1;
	Control::MouseDrag mouseInput;

	void drag(const Vector2D& force);
	
	size_t idAt1;
	Resource<float>& getResAt1()
	{
		return getResource_f(idAt1);
	}
	size_t idAt2;
	Resource<float>& getResAt2()
	{
		return getResource_f(idAt2);
	}

	void moveAsPlayer(const Vector2D& force, float addictionalRotation = 0);
	void movementScript();
	void movementScript_version2();
	void atack1Script();
	void atack2Script();

};

/**/