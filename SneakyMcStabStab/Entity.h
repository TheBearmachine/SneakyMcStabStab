#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Time.hpp>
#include <queue>
#include "EntityStateIdle.h"
#include "EntityStateMoving.h"
#include "EntityStatePossess.h"
#include "EntityStateDead.h"
#include "EntityHands.h"
#include "EntityEyes.h"

class EntityState;
class EventManager;
class EntityManager;

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
	EntityEyes* getEyes();

	float getRadius() const;
	void onCollision(const sf::Vector2f &penetration);

	void setForward(const sf::Vector2f &v);
	sf::Vector2f getForward() const;

	sf::FloatRect getBroadDetection();
	float getNarrowDetection();

	sf::FloatRect getWeaponRect();
	sf::Vector2f getWeaponTip();

	void populatePatrolQueue(const sf::Vector2f &point);
	sf::Vector2f getNextPatrolPoint() const;
	void cyclePatrolPoints();

	EntityStateIdle* getIdleState();
	EntityStateMoving* getMovingState();
	EntityStateDead* getDeadState();
	EntityStatePossess* getPossessedState();

	void possess();

protected:
	EntityStatePossess mEntityStatePossess;
	EntityStateIdle mEntityStateIdle;
	EntityStateMoving mEntityStateMoving;
	EntityStateDead mEntityStateDead;
	EntityState* mCurrentEntityState;

	std::queue<sf::Vector2f> mPatrolPoints;
	sf::Vector2f mForward;
	sf::CircleShape mSprite;
	EntityHands mHands;
	EntityEyes mEyes;
	sf::RectangleShape test;
};