#include "Particle.h"


Particle::Particle()
{
}

void Particle::update(float dt, const string& constructionScript, const Sprite& connectedTo, const Vector2D& posRot)
{
	
	actualTime += dt;
	(*this) += change*dt;
	
	if (needToReset())
	{
		auto acT = (int)(actualTime-minimalSteap) % (int)liveTime;
		resetParticle(constructionScript, connectedTo, posRot);
		actualTime += acT;
	}
}

void Particle::serialize(ostream& file)
{

}
void Particle::deserialize(const string& path)
{
	string constructionScript;
	fstream file(path);
	if (file)
	{
		constructionScript = "";
		while (!file.eof())
		{
			string s;
			getline(file, s);
			if (s != "")
			constructionScript += s + "\n";
		}
	}
	else
	{
		cerr << " Error : fail open the file to load - \"" << path << "\"\n";
	}

	file.close();

	resetParticle(constructionScript);

}
void Particle::deserialize(istream& file)
{
	Model::deserialize(file);

	// next initialize basic propertites
	XMLloader loader;

	loader.nextLine(file);
	actualTime = loader.load("actialTime", 0.f);
	liveTime = loader.load("liveTime", 1.f);
	animationTimeMin = loader.load("animationTimeMin", actualTime - 1);
	animationTimeMax = loader.load("animationTimeMax", liveTime + 1);
	minimalSteap = loader.load("minimalSteap", 0);


	loader.nextLine(file);
	change.deserialize(loader);

}
void Particle::resetParticle(const string& constructionScript, const Sprite& connectedTo, const Vector2D& posRot)
{
	stringstream stream(constructionScript);
	deserialize(stream);
	update(minimalSteap,constructionScript);

	pos += posRot;
	posNoRot += connectedTo.getPosition();
	rot += connectedTo.getRotation();

	clR *= ((float)connectedTo.getColor().r) / 255.f;
	clG *= ((float)connectedTo.getColor().g) / 255.f;
	clB *= ((float)connectedTo.getColor().b) / 255.f;
	clA *= ((float)connectedTo.getColor().a) / 255.f;
	
}

void Particle::display(RenderTarget& wnd, const Sprite& connectedTo)
{
	// display on the screan
	//sf::Sprite sp;
	//sp.setPosition(positionNoRotation);
	//Model::parent = &sp;

	setColorAll(sf::Color(::clamp(clR, 0.f, 255.f), ::clamp(clG, 0.f, 255.f), ::clamp(clB, 0.f, 255.f), ::clamp(clA, 0.f, 255.f)));

	if (!canBeDisplayed())
		return;
	Model::draw(wnd, connectedTo);

	//Model::parent = nullptr;
}
void Particle::display(Camera& cam, const Sprite& connectedTo)
{
	// display on the screan
	//sf::Sprite sp;
	//sp.setPosition(positionNoRotation);
	//Model::parent = &sp;

	setColor(sf::Color(::clamp(clR, 0.f, 255.f), ::clamp(clG, 0.f, 255.f), ::clamp(clB, 0.f, 255.f), ::clamp(clA, 0.f, 255.f)));

	if (!canBeDisplayed())
		return;
	Model::updateAll(connectedTo);
	Model::draw(cam,connectedTo);

	//Model::parent = nullptr;
}