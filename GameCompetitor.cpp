#include "GameCompetitor.h"

namespace Game
{

	Competitor::Competitor()
	{
	}

	void Competitor::resetInput()
	{
		for (auto& it = keys.begin(); it != keys.end(); ++it)
			unpress(it->first);
		drag = Vector2D();
	}


	bool Competitor::lookAt(const Vector2D& position, float forceRatio, float maxForce, float tolerance)
	{
		Vector2D toPosition = getPosC().position - position;
		float toPositionAngle = (-getPosC().position + position).angle();

		float angleDiffirence = minimalAngleDiffirence(toPositionAngle, getRotC().position);
		//float cosinus = Vector2D(0, 1).getRotated(getRotC().position).dot(toPosition.normalised());
		//float angleDiffirence = acos(cosinus);


		//cout << "diff " << angleDiffirence << "\n";
		if (angleDiffirence < tolerance && angleDiffirence > -tolerance)
			return true;
		
		float force = clamp( -angleDiffirence*forceRatio, -maxForce, maxForce);
		
		drag.x += force;

		return false;
	}


	bool Competitor::moveTo(const Vector2D& position, const Vector2D& radius, const Vector2D& tolerance)
	{
		Vector2D toAim = getPosC().position - position;
		toAim.rotate(-getRotC().position + 180);
		
		//Vector2D toRotation = Vector2D(0, 1).getRotated(getRotC().position);

		static const float forceRatio = 0.5;

		if ( toAim.getLenghtSq() > radius.y * radius.y)
		{
			/**/if (toAim.y > 0)
				press("down", abs(toAim.y - radius.y) * tolerance.y);
			else
				press("up", abs(toAim.y - radius.y) * tolerance.y);

			if (toAim.x > 0)
				press("right", abs(toAim.x - radius.y) * tolerance.y);
			else
				press("left", abs(toAim.x - radius.y) * tolerance.y);

			/**if (toAim.y > tolerance.y)
				press("down");
			else if (toAim.y < -tolerance.y)
				press("up");

			if (toAim.x > tolerance.x)
				press("right");
			else if (toAim.x < -tolerance.x)
				press("left");/**/
			//cout << toAim.getLenghtSq() << ">" << radius.y * radius.y << "\n";
		}
		else if (toAim.getLenghtSq() < radius.x * radius.x)
		{
			/**/if (toAim.y < 0)
				press("down", abs(toAim.y - radius.x) * tolerance.x);
			else
				press("up", abs(toAim.y - radius.x) * tolerance.x);

			if (toAim.x < 0)
				press("right", abs(toAim.x - radius.x) * tolerance.x);
			else
				press("left", abs(toAim.x - radius.x) * tolerance.x);

			/**if (toAim.y > tolerance.y)
				press("up");
			else if (toAim.y < -tolerance.y)
				press("down");

			if (toAim.x > tolerance.x)
				press("left");
			else if (toAim.x < -tolerance.x)
				press("right");/**/
			
			//cout << toAim.getLenghtSq() << "<" << radius.x * radius.x << "\n";
		}
		else
		{
			//system("cls");
			return true;
		}

		return false;
	}

}