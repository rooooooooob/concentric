#ifndef CON_Scoreboard_HPP
#define CON_Scoreboard_HPP

#include <functional>
#include <map>
#include <vector>

#include "PlayerConfig.hpp"

namespace con
{

class Scoreboard
{
public:
	typedef int TeamID;
	typedef int PlayerID;
	typedef std::vector<PlayerID> PlayerIDList;
	typedef std::map<TeamID, PlayerIDList> TeamMap;

	class Score
	{
	public:
		int kills;
		int deaths;
		int suicides;

		Score() : kills(0), deaths(0), suicides(0)
		{
		}

		int score() const
		{
			return kills - suicides;
		}
	};

	Scoreboard(const std::function<void()>& onScoreCallback);


	void registerPlayer(const PlayerConfig& player);
	
	void unregisterPlayer(const PlayerConfig& player);
	
	void reportKill(const PlayerConfig& killer, const PlayerConfig& victim);
	
	void reportSuicide(const PlayerConfig& player);
	

	int numberOfTeams() const;

	int numberOfPlayers() const;
	
	int numberOfPlayers(TeamID team) const;
	
	const Score& getPlayerScore(PlayerID player) const;

	Score calculateTeamScore(TeamID team) const;

	const TeamMap& getTeamMap() const;
	
private:

	TeamMap teamIDs;
	std::map<PlayerID, Score> scores;
	std::function<void()> onScoreCallback;
};

}

#endif
