#pragma once
#include "Button.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <vector>

namespace sf
{
	class RenderWindow;
}
class EventManager;

class Menu : public sf::Transformable, public sf::Drawable
{
public:
	Menu();
	~Menu();

	void setup(EventManager* eventManager, sf::RenderTarget* window);
	void addButton(IButtonListener * listener, const std::string &buttonText, const std::string &textureName, unsigned int action);
	void clearButtons();

	void setPosition(float x, float y);
	void setPosition(const sf::Vector2f &pos);

	sf::Vector2f getSize() const;

	void registerButtons();
	void unregisterButtons();

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
	void setGlobalPosition(const sf:: Vector2f &pos);

	std::vector<Button*> mButtons;
	EventManager* mEventManager;
	sf::RenderTarget* mWindow;
	sf::Vector2f mSize;
	sf::Vector2f mGlobalPosition;
	sf::RectangleShape mBackground;

};