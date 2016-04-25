#include "CircleCollider.h"


CircleCollider::CircleCollider(const Vector2D& _center, float _range)
	:center(_center), range(_range)
{
}

// tells whether the colliders are colliding each other
bool CircleCollider::isOnCollision(const CircleCollider& other) const
{
	return (other.center - center).getLenghtSq() < (range + other.range)*(range + other.range);
}

CircleCollider CircleCollider::getColliderAccordingToSprite(const sf::Sprite& sp) const
{
	return CircleCollider( sp.getPosition() + center.getRotated( sp.getRotation() ), range );
}


void CircleCollider::display(Camera& cam, const Color& color) const
{
	CircleShape sh(range);
	sh.setPosition(center);
	sh.setOrigin(range, range);
	sh.setFillColor(color);

	cam.draw(sh);
}
void CircleCollider::display(RenderWindow& wnd, const Color& color) const
{
	CircleShape sh(range);
	sh.setPosition(center);
	sh.setOrigin(range, range);
	sh.setFillColor(color);
	
	wnd.draw(sh);
}