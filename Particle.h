#pragma once
#include "Model.h"

class Particle : public Model
{
public:
	Particle();


	ModelDef change;
	float actualTime, liveTime, animationTimeMin, animationTimeMax, minimalSteap;	
	bool needToReset()
	{
		return actualTime > liveTime + minimalSteap;
	}
	bool canBeDisplayed()
	{
		return	actualTime > animationTimeMin && 
				actualTime < animationTimeMax;
	}

	void update(float dt, const string& constructionScript, const Sprite& connectedTo = Sprite(), const Vector2D& posRot = Vector2D());
	void display(RenderTarget& wnd, const Sprite& connectedTo = Sprite());
	void display(Camera& cam, const Sprite& connectedTo = Sprite());


	void serialize(const string& str)
	{
		ISerializable::serialize(str);
	}
	void serialize(ostream& file) override;
	void deserialize(const string& str);
	void deserialize(istream& file) override;


	void resetParticle(const string& constructionScript, const Sprite& connectedTo = Sprite(), const Vector2D& posRot = Vector2D());
};

