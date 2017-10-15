#include "EventManager.h"
#include "EventObserver.h"

EventManager::EventManager() :
	mObservers()
{

}

EventManager::~EventManager()
{

}

void EventManager::registerObserver(EventObserver* observer, const std::vector<sf::Event::EventType>& types)
{
	for (auto t : types)
		registerObserver(observer, t);
}

void EventManager::registerObserver(EventObserver* observer, const sf::Event::EventType& type)
{
	mObservers[type].insert(observer);
}

void EventManager::unregisterObserver(EventObserver* observer, const std::vector<sf::Event::EventType>& types)
{
	for (auto t : types)
		unregisterObserver(observer, t);
}

void EventManager::unregisterObserver(EventObserver* observer, const sf::Event::EventType& type)
{
	mObservers[type].erase(observer);
}

void EventManager::notify(const sf::Event & _event) const
{
	auto temp = mObservers;

	if (temp.find(_event.type) != temp.end())
	{
		const ObserverSet& observers = temp.at(_event.type);
		for (auto o : observers)
			o->observe(_event);
	}
}
