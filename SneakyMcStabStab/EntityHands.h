#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class EntityHands : public sf::Drawable, public sf::Transformable
{
public:
	EntityHands();
	~EntityHands();

	void setColor(const sf::Color &color);

	void stab();
	void swing();
	void grab();

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
	sf::CircleShape mHand[2];
	sf::RectangleShape mWeapon;

	bool mBusy;
};