#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Wall : public sf::Drawable
{
public:
	Wall(const sf::Vector2f &pos, const sf::Vector2f &size);
	~Wall();

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	sf::FloatRect getBounds() const;

private:
	sf::RectangleShape mBounds;
};