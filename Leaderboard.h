#ifndef LEADERBOARD_H_INCLUDED
#define LEADERBOARD_H_INCLUDED

#include "RewardLinks.h"
#include "SubLeaderboard.h"
#include "ProjectDefines.h"




//contains every leaderboards plus additionnal data
typedef struct
{
    int NbTiers;
    t_SubLeaderboard** SubLeaderboard; //array of leaderboards, 1 for each tier. (with mixed tiers ex. 1, 2, 3, only tier 3 is created)
}t_Leaderboard;




void InitLeaderboard(t_Leaderboard* Leaderboard);
int SubLeaderboardExists(t_Leaderboard* Leaderboard, int tier);
void AddSubLeaderboard(t_Leaderboard* Leaderboard, int tier);
void AddLeaderboardData(t_Leaderboard* Leaderboard, char* rank, char* reward, int qty, int tier, int WeekID);
void FreeLeaderboard(t_Leaderboard* Leaderboard);

int TierToIndex(t_Leaderboard* Leaderboard, int tier);


void CheckRewardStates(t_Leaderboard* Leaderboard, char* RewardLink, char* rank, char* reward, int qty, int tier, int WeekID);





#endif // LEADERBOARD_H_INCLUDED
