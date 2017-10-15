#include "Clickable.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "EventManager.h"

Clickable::Clickable(sf::FloatRect area) :
	mInteractArea(area), mMouseInside(false)
{
	mInterestedEvents.push_back(sf::Event::EventType::MouseMoved);
	mInterestedEvents.push_back(sf::Event::EventType::MouseButtonPressed);
	mInterestedEvents.push_back(sf::Event::EventType::MouseButtonReleased);
}

Clickable::~Clickable()
{
	unregisterEvents();
}

void Clickable::registerEvents()
{
	if (mEventManager && !mRegistered)
	{
		mRegistered = true;
		mEventManager->registerObserver(this, mInterestedEvents);
	}
}

void Clickable::unregisterEvents()
{
	if (mEventManager && mRegistered)
	{
		mRegistered = false;
		mEventManager->unregisterObserver(this, mInterestedEvents);
	}
}

void Clickable::observe(const sf::Event & _event)
{
	sf::Vector2f mousePos;
	switch (_event.type)
	{
	case sf::Event::MouseMoved:
		mousePos = mWindow->mapPixelToCoords(sf::Vector2i(_event.mouseMove.x, _event.mouseMove.y));
		if (mInteractArea.contains(mousePos))
		{
			if (!mMouseInside)
			{
				mMouseInside = true;
				onMouseOver(true);
			}
		}
		else
		{
			if (mMouseInside)
			{
				mMouseInside = false;
				onMouseOver(false);
			}
		}
		break;

	case sf::Event::MouseButtonPressed:
		if (mMouseInside)
			onClickInside();
		break;

	case sf::Event::MouseButtonReleased:
		if (mMouseInside)
			onReleaseInside();
		break;
	}
}

void Clickable::setup(EventManager * eventManager, sf::RenderTarget * window)
{
	mEventManager = eventManager;
	mWindow = window;
}
