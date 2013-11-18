#include "Scoreboard.hpp"
#include <iostream>

namespace con
{

Scoreboard::Scoreboard ()
{

}

void Scoreboard::addPlayer (int team)
{
	std::cout << "size: " << teamList.size();
	teamList[team].push_back (0);
	std::cout << "\nplayer added";
}

void Scoreboard::addTeam ()
{
	teamList.push_back (Team());
}

void Scoreboard::removePlayer (int team)
{
	teamList[team].pop_back();
}

void Scoreboard::removeTeam ()
{
	teamList.pop_back ();
}

void Scoreboard::reportScore (const PlayerConfig* p)
{
	teamList[p->team][p->playerID]++;
}

int Scoreboard::numberOfTeams () const
{
	return teamList.size();
}

int Scoreboard::numberOfPlayers (int team) const
{
	return teamList[team].size();
}

int Scoreboard::getPlayerScore (int team, int player) const
{
	return teamList[team][player];
}

}
