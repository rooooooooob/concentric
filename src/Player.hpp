#ifndef CON_PLAYER_HPP
#define CON_PLAYER_HPP

#include <map>
#include <string>
#include <memory>
#include "Entity.hpp"
#include "Animation.hpp"
#include "Controller.hpp"
#include "PlayerConfig.hpp"

namespace con
{

class Player : public je::Entity
{
public:
	Player(je::Level *level, int x, int y, int team, const PlayerConfig& config, const je::Controller& controller);
private:
	void draw(sf::RenderTarget& target, const sf::RenderStates& states = sf::RenderStates::Default) const override;

	void onUpdate() override;

	std::string currentAnimation;
	std::map<std::string, std::unique_ptr<je::Animation> > animations;
	je::Controller input;
};

}

#endif