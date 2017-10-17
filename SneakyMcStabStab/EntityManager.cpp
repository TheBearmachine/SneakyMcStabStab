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

void EntityManager::update(const sf::Time & deltaTime)
{
	for (auto e : mEntities)
	{
		e->update(deltaTime);
	}
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
