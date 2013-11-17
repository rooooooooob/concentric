#ifndef CON_SCOREBOARD_HPP
#define CON_SCOREBOARD_HPP

#include "PlayerConfig.hpp"
#include <vector>

namespace con
{

class Scoreboard
{
	typedef std::vector<int> Team;

	public:
		Scoreboard ();
		void addPlayer (int team);
		void addTeam ();
		void removePlayer (int team);
		void removeTeam ();
		void reportKill (const PlayerConfig& killer);
		int numberOfTeams () const;
		int numberOfPlayers (int team) const;
		int getPlayerScore (int team, int player) const;

	private:
		std::vector<Team> teamList;
};

}

#endif
