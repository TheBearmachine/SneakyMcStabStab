#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Time.hpp>
#include "EntityStatePossess.h"
#include "EntityHands.h"

class EntityState;
class EventManager;

class Entity : public sf::Drawable, public sf::Transformable
{
public:
	Entity();
	virtual ~Entity();

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	virtual void update(const sf::Time &deltaTime);

	void setCurrentState(EntityState* state);
	EntityState* getCurrentEntityState();

	void setEventManager(EventManager* eventManager);

	EntityHands* getHands();

	float getRadius() const;
	void onCollision(const sf::Vector2f &penetration);

	void setForward(const sf::Vector2f &v);
	sf::Vector2f getForward() const;

	void possess();

protected:
	EntityStatePossess mEntityStatePossess;
	sf::Vector2f mForward;

	EntityState* mCurrentEntityState;
	sf::CircleShape mSprite;
	EntityHands mHands;
};