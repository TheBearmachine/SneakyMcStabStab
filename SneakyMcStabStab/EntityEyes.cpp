#include "EntityEyes.h"
#include "Entity.h"
#include "EntityManager.h"
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
		sf::Transform trans;
		trans.translate(mOwner->getPosition());
		target.draw(mSightIndicator, trans);
	}
}

bool EntityEyes::detectTarget(const sf::Vector2f &forward)
{
	bool targetSeen = false;
	sf::Vector2f newVec = forward;
	VectorFunctions::normalizeVector(newVec);
	if (VectorFunctions::vectorMagnitude(newVec) <= 0.01) return targetSeen;

	sf::Vector2f forwardPos = newVec * SIGHT_DISTANCE;
	VectorRotation rot1(VectorRotation::inDegrees(FIELD_OF_VIEW / 2.0f));
	VectorRotation rot2(VectorRotation::inDegrees(-FIELD_OF_VIEW / (float)(mSightIndicator.getVertexCount() - 2)));
	forwardPos = (VectorRotation(forwardPos) * rot1).toVector();

	for (size_t i = 1; i < mSightIndicator.getVertexCount(); i++)
	{
		mSightIndicator[i].position = forwardPos;
		forwardPos = (VectorRotation(forwardPos) * rot2).toVector();
	}

	if (mSearchTarget &&
		mSearchTarget->getCurrentEntityState() != mSearchTarget->getDeadState()) // Don't bother detecting a dead entity
	{
		sf::Vector2f tarDir = mSearchTarget->getPosition() - mOwner->getPosition();
		if (VectorFunctions::vectorMagnitude(tarDir) < SIGHT_DISTANCE)
		{
			float angle = VectorFunctions::angleBetweenVectors(tarDir, newVec);
			angle = angle * 180 / PI;
			if (angle < HALF_FOV)
			{
				// Player found, see if there is a clear line
				if (!mEntityManager->rayCast(mOwner->getPosition(), mSearchTarget->getPosition()))
				{
					targetSeen = true;
					mLastKnownPlayerPosition = mSearchTarget->getPosition();
				}
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

void EntityEyes::setEntityManager(EntityManager * entityManager)
{
	mEntityManager = entityManager;
}

sf::Vector2f EntityEyes::getLastKnownPlayerPosition() const
{
	return mLastKnownPlayerPosition;
}
