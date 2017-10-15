#pragma once
#include "Clickable.h"
#include "Animation.h"
#include <string>
#include <vector>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>

__interface IButtonListener
{
	void buttonAction(unsigned int action);
};

class Button : public Clickable, public sf::Transformable, public sf::Drawable
{
public:
	Button(IButtonListener *listener, const std::string &textureName, unsigned int action);
	virtual ~Button();

	void setSpriteTexture(std::string texName);
	void setTextString(const std::string &text);
	void setTextFont(const std::string &font);

	void setGlobalPosition(const sf::Vector2f &pos);

	virtual void observe(const sf::Event & _event) override;
	virtual void onMouseOver(bool mouseOver) override;
	virtual void onClickInside() override;
	virtual void onReleaseInside() override;

	virtual void setActive(bool active);
	sf::FloatRect getSpriteBounds() const;

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

private:
	void adjustTextPosition();

	unsigned int mClickAction;
	IButtonListener* mListener;
	Animation mSprite;
	sf::Text mText;
	sf::Vector2f mGlobalPosition;

	bool mIsActive;
};
