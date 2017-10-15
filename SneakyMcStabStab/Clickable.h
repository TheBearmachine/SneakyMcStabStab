#pragma once
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Event.hpp>
#include "EventObserver.h"
#include <vector>

namespace sf
{
	class RenderTarget;
}

class EventManager;

class Clickable : public EventObserver
{
public:
	Clickable(sf::FloatRect area);
	virtual ~Clickable();

	virtual void registerEvents();
	virtual void unregisterEvents();
	virtual void observe(const sf::Event & _event);
	virtual void onMouseOver(bool mouseOver) = 0;
	virtual void onClickInside() = 0;
	virtual void onReleaseInside() = 0;
	void setup(EventManager* eventManager, sf::RenderTarget* window);

protected:
	sf::FloatRect mInteractArea;
	sf::RenderTarget* mWindow;
	EventManager* mEventManager;
	std::vector<sf::Event::EventType> mInterestedEvents;
	bool mMouseInside;
};
