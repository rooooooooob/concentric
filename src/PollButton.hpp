#ifndef CON_POLLBUTTON_HPP
#define CON_POLLBUTTON_HPP

#include "Window.hpp"
#include "PlayerConfig.hpp"

namespace con
{

class PollButton : public Button
{
	public:
		PollButton (const sf::Vector2f &pos, const sf::Vector2f &dimensions, const std::string &label, je::Level *level, std::function <void(Button*)> click, std::string texturepath, PlayerConfig& config, Window *window = nullptr);
		void update() override;

	private:
		PlayerConfig& config;
};

}

#endif
