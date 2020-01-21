#pragma once

#include <SFML/Window/Event.hpp>

#include "MVC.h"

namespace ABTools
{
	namespace MVC
	{
		class SfmlController : public Controller
		{
		public:
			virtual void OnMouseDown(const sf::Event::MouseButtonEvent& event) {}

			virtual void OnKeyDown(const sf::Event::KeyEvent& event) {}
		};
	}
}