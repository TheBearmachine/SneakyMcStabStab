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
	}
}

void EntityManager::draw(sf::RenderTarget & window) const
{
	for (auto e : mEntities)
	{
		window.draw(*e);
	}
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
