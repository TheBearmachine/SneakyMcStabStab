#include "EntityEyes.h"
#include "Entity.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include "VectorFunctions.h"

static const float FIELD_OF_VIEW = 45.0f;
static const float HALF_FOV = FIELD_OF_VIEW / 2.0f;
static const float SIGHT_DISTANCE = 120.0f;

EntityEyes::EntityEyes(Entity* owner) :
	mOwner(owner),
	mSightIndicator(sf::PrimitiveType::TriangleFan, 6),
	mDrawSight(true)
{

	mSightIndicator[0].color = sf::Color(0, 255, 0, 125);
	for (size_t i = 1; i < mSightIndicator.getVertexCount(); i++)
	{
		mSightIndicator[i].color = sf::Color(200, 200, 0, 125);
	}

	detectTarget(sf::Vector2f(0.0f, 1.0f));
}

EntityEyes::~EntityEyes()
{
}

void EntityEyes::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (mDrawSight)
	{
		states.transform *= getTransform();
		target.draw(mSightIndicator, states);
	}
}

bool EntityEyes::detectTarget(const sf::Vector2f &forward)
{
	bool targetSeen = false;
	if (VectorFunctions::vectorMagnitude(forward) <= 0.01) return targetSeen;

	sf::Vector2f forwardPos = forward * SIGHT_DISTANCE;
	VectorRotation rot1(VectorRotation::inDegrees(FIELD_OF_VIEW / 2.0f));
	VectorRotation rot2(VectorRotation::inDegrees(-FIELD_OF_VIEW / (float)(mSightIndicator.getVertexCount() - 2)));
	forwardPos = (VectorRotation(forwardPos) * rot1).toVector();

	for (size_t i = 1; i < mSightIndicator.getVertexCount(); i++)
	{
		mSightIndicator[i].position = forwardPos;
		forwardPos = (VectorRotation(forwardPos) * rot2).toVector();
	}

	if (mSearchTarget &&
		mSearchTarget->getCurrentEntityState() != mSearchTarget->getDeadState()) // Don't bother detecting a dead player
	{
		sf::Vector2f tarDir = mSearchTarget->getPosition() - mOwner->getPosition();
		if (VectorFunctions::vectorMagnitude(tarDir) < SIGHT_DISTANCE)
		{
			float angle = VectorFunctions::angleBetweenVectors(tarDir, forward);
			angle = angle * 180 / PI;
			if (angle < HALF_FOV)
			{
				// Player found, get him (Or her, #feminism)!
				targetSeen = true;
				mLastKnownPlayerPosition = mSearchTarget->getPosition();
			}
		}
	}

	return targetSeen;
}

void EntityEyes::setSearchTarget(Entity * target)
{
	mSearchTarget = target;
}

void EntityEyes::setDrawSight(const bool & drawSight)
{
	mDrawSight = drawSight;
}

sf::Vector2f EntityEyes::getLastKnownPlayerPosition() const
{
	return mLastKnownPlayerPosition;
}
