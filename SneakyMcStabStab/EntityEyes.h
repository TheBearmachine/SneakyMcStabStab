#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>

class Entity;

class EntityEyes : public sf::Drawable, public sf::Transformable
{
public:
	EntityEyes(Entity* owner);
	~EntityEyes();

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	bool detectTarget(const sf::Vector2f &forward);
	void setSearchTarget(Entity* target);

	void setDrawSight(const bool &drawSight);

	sf::Vector2f getLastKnownPlayerPosition() const;

private:
	Entity* mOwner;
	Entity* mSearchTarget;
	sf::VertexArray mSightIndicator;
	sf::Vector2f mLastKnownPlayerPosition;
	bool mDrawSight;
};