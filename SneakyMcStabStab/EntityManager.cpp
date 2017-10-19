#include "EntityManager.h"
#include "EntityState.h"
#include "VectorFunctions.h"

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
}

void EntityManager::addEntity(Entity * entity)
{
	mEntities.push_back(entity);
	entity->getEyes()->setEntityManager(this);
}

void EntityManager::setSearchTargets()
{
	Entity* target = nullptr;
	for (size_t i = 0; i < mEntities.size(); i++)
	{
		if (mEntities[i]->getCurrentEntityState() == mEntities[i]->getPossessedState())
		{
			target = mEntities[i];
			break;
		}
	}
	for (size_t i = 0; i < mEntities.size(); i++)
	{
		mEntities[i]->getEyes()->setSearchTarget(target);
	}
}

void EntityManager::update(const sf::Time & deltaTime)
{
	for (auto e : mEntities)
	{
		e->update(deltaTime);
	}
}

void EntityManager::addWall(Wall* wall)
{
	mWalls.push_back(wall);
}

void EntityManager::detectCollisions()
{
	// Entity to entity collisions using circular checks
	for (size_t i = 0; i < mEntities.size() - 1; i++)
	{
		for (size_t j = i + 1; j < mEntities.size(); j++)
		{
			sf::Vector2f pos1 = mEntities[i]->getPosition(), pos2 = mEntities[j]->getPosition();
			float dxSq = (pos1.x - pos2.x) * (pos1.x - pos2.x);
			float dySq = (pos1.y - pos2.y) * (pos1.y - pos2.y);
			float rad = mEntities[i]->getRadius() + mEntities[j]->getRadius();
			float radSq = rad * rad;
			if (dxSq + dySq < radSq)
			{
				sf::Vector2f dir = pos1 - pos2;
				VectorFunctions::normalizeVector(dir);

				float penDist = rad - VectorFunctions::vectorMagnitude(pos1 - pos2);
				mEntities[i]->move(dir * penDist / 1.9f);
				mEntities[j]->move(-dir * penDist / 1.9f);
			}
			pos1 = mEntities[i]->getWeaponTip();
			// Weapon to entity collision
			if (mEntities[i]->getHands()->getAttacking() &&
				mEntities[j]->getCurrentEntityState() != mEntities[j]->getDeadState()) // Don't bother with dead entities
			{
				dxSq = (pos1.x - pos2.x) * (pos1.x - pos2.x);
				dySq = (pos1.y - pos2.y) * (pos1.y - pos2.y);
				rad = 1.5f + mEntities[j]->getRadius();
				radSq = rad * rad;

				if (dxSq + dySq < radSq)
				{
					mEntities[j]->getCurrentEntityState()->die();
					printf("Stab!");
				}
			}
			if (mEntities[j]->getHands()->getAttacking() &&
				mEntities[i]->getCurrentEntityState() != mEntities[i]->getDeadState()) // Don't bother with dead entities
			{
				dxSq = (pos1.x - pos2.x) * (pos1.x - pos2.x);
				dySq = (pos1.y - pos2.y) * (pos1.y - pos2.y);
				rad = 1.5f + mEntities[i]->getRadius();
				radSq = rad * rad;

				if (dxSq + dySq < radSq)
				{
					mEntities[i]->getCurrentEntityState()->die();
					printf("Stab!");
				}
			}
		}

		// Wall collisions
		for (size_t j = 0; j < mWalls.size(); j++)
		{
			sf::FloatRect rect1 = mEntities[i]->getBroadDetection();
			sf::FloatRect rect2 = mWalls[j]->getBounds();
			if (rect1.intersects(rect2))
			{
				const float distTop = abs(rect1.top - (rect2.top + rect2.height));
				const float distBot = abs(rect2.top - (rect1.top + rect1.height));
				const float distLeft = abs(rect1.left - (rect2.left + rect2.width));
				const float distRight = abs(rect2.left - (rect1.left + rect1.width));

				float min = distTop;
				if (min > distBot)
					min = distBot;
				if (min > distLeft)
					min = distLeft;
				if (min > distRight)
					min = distRight;

				if (min == distTop)
				{
					mEntities[i]->move(0.0f, distTop);
				}
				else if (min == distBot)
				{
					mEntities[i]->move(0.0f, -distBot);
				}
				else if (min == distLeft)
				{
					mEntities[i]->move(distLeft, 0.0f);
				}
				else if (min == distRight)
				{
					mEntities[i]->move(-distRight, 0.0f);
				}
			}
		}
	}
}

void EntityManager::draw(sf::RenderTarget & window) const
{
	for (auto e : mEntities)
	{
		window.draw(*e);
	}

	for (auto w : mWalls)
	{
		window.draw(*w);
	}
}

bool EntityManager::rayCast(const sf::Vector2f & start, const sf::Vector2f & target, float stepSize)
{
	sf::Vector2f current = start;
	bool done = false;
	while (!done)
	{
		current = VectorFunctions::lerp(current, target, stepSize, done);
		for (auto w : mWalls)
		{
			if (w->getBounds().contains(current))
				return true;
		}
	}
	return false;
}

void EntityManager::unregisterEntities()
{
	for (auto e : mEntities)
	{
		e->getCurrentEntityState()->unregisterEvents();
	}
}

void EntityManager::registerEntities()
{
	for (auto e : mEntities)
	{
		e->getCurrentEntityState()->registerEvents();
	}
}

void EntityManager::clearEntities()
{
	while (!mEntities.empty())
	{
		delete mEntities.back();
		mEntities.pop_back();
	}
}
