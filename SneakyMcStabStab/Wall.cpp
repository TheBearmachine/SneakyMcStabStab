#include "Wall.h"
#include <SFML/Graphics/RenderTarget.hpp>

Wall::Wall(const sf::Vector2f &pos, const sf::Vector2f &size)
{
	mBounds.setPosition(pos);
	mBounds.setSize(size);

	mBounds.setFillColor(sf::Color(175, 175, 175));
}

Wall::~Wall()
{

}

void Wall::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(mBounds, states);
}

sf::FloatRect Wall::getBounds() const
{
	return mBounds.getGlobalBounds();
}
