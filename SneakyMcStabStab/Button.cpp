#include "Button.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "Constants.h"
#include <SFML/Graphics/RenderWindow.hpp>

Button::Button(IButtonListener * listener, const std::string &textureName, unsigned int action) :
	Clickable::Clickable(sf::FloatRect()),
	mText("Button", ResourceManager::getInstance().getFont(Constants::Filepaths::DefaultFont), 26),
	mIsActive(true)
{
	mListener = listener;
	mClickAction = action;
	AnimationSetup animSetup = AnimationSetup::DefaultButtonSetup();
	animSetup.textureName = textureName;
	mSprite.setup(animSetup);
	mInteractArea = mSprite.getGlobalBounds();
	mInteractArea.left = getPosition().x;
	mInteractArea.top = getPosition().y;
}

Button::~Button()
{

}

void Button::setSpriteTexture(std::string texName)
{
	mSprite.setTexture(ResourceManager::getInstance().getTexture(texName));
	mInteractArea = mSprite.getGlobalBounds();
	mInteractArea.left = getPosition().x;
	mInteractArea.top = getPosition().y;
	adjustTextPosition();
	printf("Interact area left: %f, top: %f", mInteractArea.left, mInteractArea.top);
	/*mInteractArea.left = getPosition().x;
	mInteractArea.top = getPosition().y;
	mInteractArea.width = (float)mSprite.getGlobalBounds().width;
	mInteractArea.height = (float)mSprite.getGlobalBounds().height;*/
}

void Button::setTextString(const std::string &text)
{
	mText.setString(text);
	adjustTextPosition();
}

void Button::setTextFont(const std::string & font)
{
	mText.setFont(ResourceManager::getInstance().getFont(font));
	adjustTextPosition();
}

void Button::setGlobalPosition(const sf::Vector2f & pos)
{
	mGlobalPosition = pos;
	mInteractArea.left = getPosition().x + mGlobalPosition.x;
	mInteractArea.top = getPosition().y + mGlobalPosition.y;
}


void Button::observe(const sf::Event & _event)
{
	Clickable::observe(_event);
}

void Button::onMouseOver(bool mouseOver)
{
	if (mIsActive)
	{
		if (mouseOver)
			mSprite.setFrame(1);
		else
			mSprite.setFrame(0);
	}
}

void Button::onClickInside()
{
	mSprite.setFrame(2);
}

void Button::onReleaseInside()
{
	if (mListener)
		mListener->buttonAction(mClickAction);
	if (mMouseInside)
		mSprite.setFrame(1);
	else
		mSprite.setFrame(0);
}

void Button::setActive(bool active)
{
	mIsActive = active;

	if (active)
		mSprite.setFrame(0);
	else
		mSprite.setFrame(3);
}

sf::FloatRect Button::getSpriteBounds() const
{
	return mSprite.getGlobalBounds();
}

void Button::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);
	target.draw(mText, states);
}

void Button::adjustTextPosition()
{
	sf::Vector2f pos;
	float x = (mSprite.getLocalBounds().width - mText.getLocalBounds().width) / 2.0f;
	float y = (mSprite.getLocalBounds().height - mText.getLocalBounds().height) / 2.0f;
	mText.setPosition(pos);
}
