#ifndef LEADERBOARD_H_INCLUDED
#define LEADERBOARD_H_INCLUDED

#include "RewardLinks.h"
#include "SubLeaderboard.h"
#include "ProjectDefines.h"




//contains every leaderboards plus additionnal data
typedef struct
{
    int NbTiers;
    t_SubLeaderboard* SubLeaderboard; //array of leaderboards, 1 for each tier. (with mixed tiers ex. 1, 2, 3, only tier 3 is created)
    t_RewardLinks RewardLinks[2]; //[0] is main week, [1] is EX week
}t_Leaderboard;




void InitLeaderboard(t_Leaderboard* Leaderboard);
void AddSubLeaderboard(t_Leaderboard* Leaderboard, int tier);
int SubLeaderboardExists(t_Leaderboard* Leaderboard, int tier);
int TierToIndex(t_Leaderboard* Leaderboard, int tier);
void AddLeaderboardData(t_Leaderboard* Leaderboard, char* RewardLink, char* rank, char* reward, int qty, int tier, int WeekID);
void CheckRewardStates(t_Leaderboard* Leaderboard, char* RewardLink, char* rank, char* reward, int qty, int tier, int WeekID);
void FreeLeaderboard(t_Leaderboard* Leaderboard);


/**
TEST CODE

    t_Leaderboard Leaderboard;
    InitLeaderboard(&Leaderboard);
    AddLeaderboardData(&Leaderboard, "pool1", "1000", "frags", 100, 3, GAUNTLET_WEEK);
    AddLeaderboardData(&Leaderboard, "pool1", "1000", "frags", 101, 6, GAUNTLET_WEEK);
    AddLeaderboardData(&Leaderboard, "pool1", "2000", "mguts", 102, 3, GAUNTLET_WEEK);
    AddLeaderboardData(&Leaderboard, "pool2", "1000", "frags", 103, 3, GAUNTLET_WEEK);
    AddLeaderboardData(&Leaderboard, "pool1", "1000", "mguts", 104, 3, GAUNTLET_WEEK);
    FreeLeaderboard(&Leaderboard);

**/


#endif // LEADERBOARD_H_INCLUDED
