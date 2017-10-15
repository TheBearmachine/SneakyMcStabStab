#pragma once
#include <string>
#include <SFML/Window/Keyboard.hpp>

#define const_float const float
#define const_int const int
#define const_uint const unsigned int
#define const_charptr const char*

namespace Constants
{
	namespace World
	{
		
	}

	namespace Player
	{
		const_float MoveSpeed = 40.0f;
		const_float SneakSpeed = 25.0f;

		namespace Binds
		{
			const sf::Keyboard::Key Left = sf::Keyboard::A;
			const sf::Keyboard::Key Right = sf::Keyboard::D;
			const sf::Keyboard::Key Up = sf::Keyboard::W;
			const sf::Keyboard::Key Down = sf::Keyboard::S;
			const sf::Keyboard::Key Stab = sf::Keyboard::Space;
			const sf::Keyboard::Key Sneak = sf::Keyboard::LShift;
		}
	}

	namespace NPCs
	{

	}

	namespace Filepaths
	{
		const std::string FontsFolder = "Resources/Fonts/";
		const std::string ImagesFolder = "Resources/Images/";
		const std::string DefaultFont = FontsFolder + "sui_generis_rg.ttf";
	}
}