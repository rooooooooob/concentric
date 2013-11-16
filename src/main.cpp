#include "Game.hpp"
#include "Arena.hpp"
#include "MainMenu.hpp"
#include "TexManager.hpp"

int main()
{

	je::Game game(640, 480, 6);
	game.getTexManager().setPath("concentric/resources/img/");
	game.setLevel (new con::Menu (&game));
	//game.setLevel(new con::Arena(&game));
    return game.execute();
}
