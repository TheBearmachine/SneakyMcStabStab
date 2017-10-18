#pragma once
#include "Entity.h"
#include "Wall.h"
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <vector>

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	void addEntity(Entity* entity);
	void setSearchTargets();

	void update(const sf::Time &deltaTime);

	void addWall(Wall* wall);
	void detectCollisions();
	void draw(sf::RenderTarget &window) const;

	void unregisterEntities();
	void registerEntities();
	void clearEntities();

private:
	std::vector<Entity*> mEntities;
	std::vector<Wall*> mWalls;
};