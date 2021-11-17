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



void InitSubLeaderboard(t_SubLeaderboard* SubLeaderboard, int Tier);
void AddSubLeaderboardRank(t_SubLeaderboard* SubLeaderboard, char* str);
int SubLeaderboardRankExists(t_SubLeaderboard* SubLeaderboard, char* str);
void AddSubLeaderboardReward(t_SubLeaderboard* SubLeaderboard, char* str, int WeekID);
int SubLeaderboardRewardExists(t_SubLeaderboard* SubLeaderboard, char* str);
int GetRankID(t_SubLeaderboard* SubLeaderboard, char* rank);
int GetRewardID(t_SubLeaderboard* SubLeaderboard, char* reward);
void AddSubLeaderboardData(t_SubLeaderboard* SubLeaderboard, char* rank, char* reward, int qty, int WeekID);
void SL_CheckRewardStates(t_SubLeaderboard* SubLeaderboard, char* rank, char* reward, int qty, int WeekID);
void FreeSubLeaderboard(t_SubLeaderboard* SubLeaderboard);



/**
TEST CODE

    t_SubLeaderboard* SubLeaderboard;
    InitSubLeaderboard(&SubLeaderboard, 6);
    AddSubLeaderboardData(&SubLeaderboard, "1500", "regs", 100);
    AddSubLeaderboardData(&SubLeaderboard, "2500", "frags", 100);
    AddSubLeaderboardData(&SubLeaderboard, "3500", "guts", 100);
    FreeSubLeaderboard(&SubLeaderboard);

**/

#endif // SUBLEADERBOARD_H_INCLUDED
