#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Time.hpp>

class EntityHands : public sf::Drawable, public sf::Transformable
{
public:
	EntityHands();
	~EntityHands();

	void setColor(const sf::Color &color);

	void stab();
	void swing();

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	void update(const sf::Time &deltaTime);

	bool getAttacking() const;
	sf::FloatRect getWeaponRect(sf::Transform transform);
	sf::Vector2f getWeaponTip(sf::Transform transform);

private:
	enum HandAction
	{
		Stab,
		Swing
	};

	sf::CircleShape mHand[2];
	sf::RectangleShape mWeapon;

	sf::Vector2f mWeaponTip;
	sf::Vector2f mDefaultHandPosition;
	bool mBusy;
	HandAction mCurrentAction;
	float mTimer;
};