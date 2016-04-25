#include "Camera.h"


Camera::Camera() : lastScale(1), vis(0), darkness(1), alpha(1)
{
}
void Camera::create(const sf::Vector2f& size, const sf::Vector2f& center)
{
	reset(sf::FloatRect(size, size));

	ts.create((unsigned int)size.x, (unsigned int)size.y);

	setCenter(center);
}

void Camera::follow(sf::Sprite& sp, float addIctionalRotation, float d, bool followPosition, bool followRotation)
{
	/*Vector2D vd(0, d);
	vd.rotate( sp.getRotation() );


	if (followRotation)
		setRotation(sp.getRotation() + addIctionalRotation);
	if (followPosition)
		setCenter( sp.getPosition() + vd);*/
	follow(sp.getPosition(), sp.getRotation(), addIctionalRotation, d, followPosition, followRotation);
}
void Camera::follow(const Vector2D& position, float rotation, float addIctionalRotation, float d, bool followPosition, bool followRotation)
{
	Vector2D vd(0, d);
	vd.rotate(rotation);


	if (followRotation)
		setRotation(rotation + addIctionalRotation);
	if (followPosition)
		setCenter(position + vd);
}


void Camera::draw(sf::RenderWindow& wnd, const sf::Vector2f& pos)
{
	ts.display();
	ts.setView(*this);

	sf::Sprite sprite(ts.getTexture());
	sprite.setPosition(pos);
	sprite.setColor(sf::Color(255 * darkness, 255 * darkness, 255 * darkness, 255 * alpha));

	wnd.draw(sprite);
	ts.clear(background);

}