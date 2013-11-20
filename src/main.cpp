#include "Game.hpp"
#include "Arena.hpp"
#include "MainMenu.hpp"
#include "TexManager.hpp"
#include "Settings.hpp"

int main()
{

	je::Game game(640, 480, 60);
	game.getTexManager().setPath("resources/img/");
	con::Settings settings(game);
	settings.addPlayer();
	settings.addPlayer();
	game.setLevel(new con::Menu(&game, settings));
	//game.setLevel(new con::Arena(&game));
    return game.execute();
}
