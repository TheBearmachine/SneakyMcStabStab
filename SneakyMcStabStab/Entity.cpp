#include "Entity.h"
#include "EntityState.h"
#include "EntityManager.h"
#include "VectorFunctions.h"
#include <SFML/Graphics/RenderTarget.hpp>

static const float RADIUS = 12.0f;
static const float THICKNESS = 2.0f;

const sf::Vector2f WORLD_FORWARD(0.0f, 1.0f);

Entity::Entity() :
	mEntityStatePossess(this),
	mEntityStateDead(this),
	mEntityStateIdle(this),
	mEntityStateMoving(this),
	mEntityStateChase(this),
	mEyes(this),
	mCurrentEntityState(&mEntityStateIdle),
	mForward(0.0f, 1.0f)
{
	mSprite.setFillColor(sf::Color::Red);
	mSprite.setOutlineColor(sf::Color::Black);
	mSprite.setOutlineThickness(-THICKNESS);
	mSprite.setRadius(RADIUS);
	float diameter = mSprite.getLocalBounds().width;
	mSprite.setOrigin(diameter / 2.0f, diameter / 2.0f);

	test.setFillColor(sf::Color::Transparent);
	test.setOutlineColor(sf::Color::Red);
	test.setOutlineThickness(1.0f);
}

Entity::~Entity()
{

}

void Entity::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mEyes, states);
	target.draw(mHands, states);
	target.draw(mSprite, states);
	//target.draw(test);
}

void Entity::update(const sf::Time & deltaTime)
{
	if (mCurrentEntityState)
		mCurrentEntityState->update(deltaTime);
	mHands.update(deltaTime);
	float rotation = VectorFunctions::angleBetweenVectors(mForward, WORLD_FORWARD) * 180.0f / PI;
	if (mForward.x > 0)
		rotation *= -1;
	setRotation(rotation);

	sf::FloatRect rect = getWeaponRect();
	test.setPosition(rect.left, rect.top);
	test.setSize(sf::Vector2f(rect.width, rect.height));
}

void Entity::setCurrentState(EntityState * state)
{
	mCurrentEntityState = state;
}

EntityState * Entity::getCurrentEntityState()
{
	return mCurrentEntityState;
}

void Entity::setEventManager(EventManager * eventManager)
{
	mEntityStatePossess.setEventManager(eventManager);
}

EntityHands * Entity::getHands()
{
	return &mHands;
}

EntityEyes * Entity::getEyes()
{
	return &mEyes;
}

float Entity::getRadius() const
{
	return mSprite.getRadius() + mSprite.getOutlineThickness();
}

void Entity::onCollision(const sf::Vector2f & penetration)
{
}

void Entity::setForward(const sf::Vector2f & v)
{
	mForward = v;
	VectorFunctions::normalizeVector(mForward);
}

sf::Vector2f Entity::getForward() const
{
	return mForward;
}

sf::FloatRect Entity::getBroadDetection()
{
	sf::Transform trans;
	trans.translate(getPosition());
	trans *= mSprite.getTransform();
	//trans.translate(-mSprite.getOrigin());
	return trans.transformRect(mSprite.getLocalBounds());
}

float Entity::getNarrowDetection()
{
	return RADIUS;
}

sf::FloatRect Entity::getWeaponRect()
{
	sf::Transform trans = getTransform();
	return mHands.getWeaponRect(trans);
}

sf::Vector2f Entity::getWeaponTip()
{
	sf::Transform trans = getTransform();
	return mHands.getWeaponTip(trans);
}

void Entity::populatePatrolQueue(const sf::Vector2f & point)
{
	mPatrolPoints.push(point);
}

sf::Vector2f Entity::getNextPatrolPoint() const
{
	sf::Vector2f returnVec(0.0f, 0.0f);
	if (!mPatrolPoints.empty())
		returnVec = mPatrolPoints.front();
	return returnVec;
}

void Entity::cyclePatrolPoints()
{
	if (mPatrolPoints.empty()) return;

	sf::Vector2f temp = mPatrolPoints.front();
	mPatrolPoints.pop();
	mPatrolPoints.push(temp);
}

EntityStateIdle * Entity::getIdleState()
{
	return &mEntityStateIdle;
}

EntityStateMoving * Entity::getMovingState()
{
	return &mEntityStateMoving;
}

EntityStateDead * Entity::getDeadState()
{
	return &mEntityStateDead;
}

EntityStatePossess * Entity::getPossessedState()
{
	return &mEntityStatePossess;
}

EntityStateChase * Entity::geChaseState()
{
	return &mEntityStateChase;
}

void Entity::possess()
{
	setCurrentState(&mEntityStatePossess);
	mEntityStatePossess.entry();
	mSprite.setFillColor(sf::Color::Green);
	mHands.setColor(sf::Color::Green);
}
