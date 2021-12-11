#ifndef SUBLEADERBOARD_H_INCLUDED
#define SUBLEADERBOARD_H_INCLUDED


#include <stdlib.h>
#include <string.h>


enum RewardState
{
    UNINITIALIZED = 0,
    GAUNTLET_WEEK = 1,
    TRIAL_WEEK = 2,
    BOTH_WEEKS = 3
};


//a leaderboard for a specific tier
typedef struct
{
    int Tier;           //sub-leaderboard's tier
    int NbRanks;       //y axis of Qty attribute, and number of Ranks strings
    int NbRewards;     //x axis of Qty attribute, and number of Rewards strings
    int** Qty;          //2D array [Ranks][Rewards] containing quantities
    char** Ranks;       //array of rank strings
    char** Rewards;     //array of reward strings
    int* RewardState;   //used to compare 2 weeks.
}t_SubLeaderboard;




t_SubLeaderboard* InitSubLeaderboard(int Tier);
void AddSubLeaderboardData(t_SubLeaderboard* SubLeaderboard, char* rank, char* reward, int qty, int WeekID);
void FreeSubLeaderboard(t_SubLeaderboard* SubLeaderboard);

void AddSubLeaderboardRank(t_SubLeaderboard* SubLeaderboard, char* str);
int SubLeaderboardRankExists(t_SubLeaderboard* SubLeaderboard, char* str);
void AddSubLeaderboardReward(t_SubLeaderboard* SubLeaderboard, char* str, int WeekID);
int SubLeaderboardRewardExists(t_SubLeaderboard* SubLeaderboard, char* str);
void UpdateRewardState(t_SubLeaderboard* SubLeaderboard, int RewardPos, int WeekID);
int GetRankPos(t_SubLeaderboard* SubLeaderboard, char* rank);
int GetRewardPos(t_SubLeaderboard* SubLeaderboard, char* reward);




#endif // SUBLEADERBOARD_H_INCLUDED
