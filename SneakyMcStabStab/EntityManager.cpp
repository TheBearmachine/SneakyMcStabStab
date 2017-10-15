#include "EntityManager.h"
#include "EntityState.h"

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
