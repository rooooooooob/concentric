#ifndef CON_HEAD_HPP
#define CON_HEAD_HPP

#include "jam-engine/Core/Entity.hpp"
#include "Player/Player.hpp"

namespace con
{

class Head : public je::Entity
{
public:
	enum class State
	{
		Capitated,
		Decapitated
	};
	Head(je::Level *level, int x, int y, Player& owner, Scoreboard& scores);

	State getState() const;

private:
	void damage(float amount, const PlayerConfig *source);

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	void onUpdate() override;

	Player& owner;
	sf::Sprite sprite;
	float health;
	State state;
	sf::Vector2f velocity;
	Scoreboard& scores;
	bool stuck;
};

}

#endif // CON_HEAD_HPP
