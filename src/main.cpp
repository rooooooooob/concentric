#include "jam-engine/Core/Game.hpp"
#include "Arena.hpp"
#include "MainMenu.hpp"
#include "jam-engine/Graphics/TexManager.hpp"
#include "Settings.hpp"

//#include "GraphTest.hpp"

int main()
{

	je::Game game(640, 480, 60);
	game.getTexManager().setPath("resources/img/");
	con::Settings settings(game);
	settings.addPlayer();
	settings.addPlayer();
	//game.setLevel(new con::GraphTest(&game));
	game.setLevel(new con::Menu(&game, settings));
	//game.setLevel(new con::Arena(&game));
    return game.execute();
}
