#include "Scoreboard.hpp"

#include "jam-engine/Utility/Assert.hpp"

namespace con
{

Scoreboard::Scoreboard(const std::function<void()>& onScoreCallback)
	:teamIDs()
	,scores()
	,onScoreCallback(onScoreCallback)
{
}

/*			mutators			*/

void Scoreboard::registerPlayer(const PlayerConfig& player)
{
	scores[player.playerID] = Score();
	teamIDs[player.team].push_back(player.playerID);
}

void Scoreboard::unregisterPlayer(const PlayerConfig& player)
{
	JE_ASSERT_MSG(scores.count(player.playerID), "Trying to unregister player who was never registered");
	PlayerIDList& playerIDs = teamIDs[player.team];
	for (PlayerID& playerID : playerIDs)
	{
		if (playerID == player.playerID)
		{
			playerID = playerIDs.back();
			playerIDs.pop_back();
			break;
		}
	}
}

void Scoreboard::reportKill(const PlayerConfig& killer, const PlayerConfig& victim)
{
	++scores[killer.playerID].kills;
	++scores[victim.playerID].deaths;
	onScoreCallback();
}

void Scoreboard::reportSuicide(const PlayerConfig& player)
{
	++scores[player.playerID].suicides;
	onScoreCallback();
}


/*			accessors			*/

int Scoreboard::numberOfTeams() const
{
	return teamIDs.size();
}

int Scoreboard::numberOfPlayers() const
{
	int total = 0;
	for (auto& ids : teamIDs)
		total += ids.second.size();
	return total;
}

const Scoreboard::Score& Scoreboard::getPlayerScore(PlayerID player) const
{
	return scores.at(player);
}

Scoreboard::Score Scoreboard::calculateTeamScore(TeamID team) const
{
	Score teamScore;

	auto it = teamIDs.find(team);
	JE_ASSERT(it != teamIDs.end());
	for (PlayerID playerID : it->second)
	{
		auto scoreIt = scores.find(playerID);
		JE_ASSERT(scoreIt != scores.end());
		teamScore.kills += scoreIt->second.kills;
		teamScore.deaths += scoreIt->second.deaths;
		teamScore.suicides += scoreIt->second.suicides;
	}

	return teamScore;
}

const Scoreboard::TeamMap& Scoreboard::getTeamMap() const
{
	return teamIDs;
}

}
