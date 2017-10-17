#pragma once
#include "Entity.h"
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <vector>

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	void addEntity(Entity* entity);

	void update(const sf::Time &deltaTime);

	void addWall();
	void detectCollisions();
	void draw(sf::RenderTarget &window) const;

	void unregisterEntities();
	void registerEntities();
	void clearEntities();

private:
	std::vector<Entity*> mEntities;
};