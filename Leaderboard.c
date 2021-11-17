#include "Leaderboard.h"


void InitLeaderboard(t_Leaderboard* Leaderboard)
{

    //creates space for 1 sub leaderboard but does not init it
    Leaderboard->SubLeaderboard = (t_SubLeaderboard*) malloc(sizeof(t_SubLeaderboard));

    //init reward links
    t_RewardLinks RewardLinks[2];
    InitRewardLinks(&RewardLinks[MAIN]);
    Leaderboard->RewardLinks[MAIN] = RewardLinks[MAIN];
    InitRewardLinks(&RewardLinks[EX]);
    Leaderboard->RewardLinks[EX] = RewardLinks[EX];

    //other members
    Leaderboard->NbTiers = 0;
}

void AddSubLeaderboard(t_Leaderboard* Leaderboard, int tier)
{
    //init a new sub leaderboard
    t_SubLeaderboard NewSubLeaderboard;
    InitSubLeaderboard(&NewSubLeaderboard, tier);

    //realloc memory
    Leaderboard->NbTiers++;
    Leaderboard->SubLeaderboard = (t_SubLeaderboard*) realloc(Leaderboard->SubLeaderboard, Leaderboard->NbTiers*sizeof(t_SubLeaderboard));

    //link new sub leaderboard to allocated memory
    Leaderboard->SubLeaderboard[Leaderboard->NbTiers-1] = NewSubLeaderboard;
}

int SubLeaderboardExists(t_Leaderboard* Leaderboard, int tier)
{
    //if TierToIndex returns an error (-1) then the function returns false
    //if TierToIndex returns an index, index+1 will always be positive and the function returns true
    return TierToIndex(Leaderboard, tier)+1;
}

int TierToIndex(t_Leaderboard* Leaderboard, int tier)
{
    //for each registered leaderboard...
    for(int i = 0; i < Leaderboard->NbTiers; i++)
    {
        //check if the wanted tier exists and return its index
        if(Leaderboard->SubLeaderboard[i].Tier == tier)
            return i;
    }

    //return -1 if not found
    return -1;
}

void AddLeaderboardData(t_Leaderboard* Leaderboard, char* RewardLink, char* rank, char* reward, int qty, int tier, int WeekID)
{
    //creates a new SubLeaderboard if it does not exists
    if(SubLeaderboardExists(Leaderboard, tier) == 0)
        AddSubLeaderboard(Leaderboard, tier);

    //get the tier ID
    int TierID = TierToIndex(Leaderboard, tier);

    //add the reward link if needed
    if(!LinkRewardExists(&(Leaderboard->RewardLinks[MAIN]), RewardLink))
        AddRewardLink(&(Leaderboard->RewardLinks[MAIN]), RewardLink);

    //add the subleaderboard data
    AddSubLeaderboardData(&(Leaderboard->SubLeaderboard[TierID]), rank, reward, qty, WeekID);
}

void CheckRewardStates(t_Leaderboard* Leaderboard, char* RewardLink, char* rank, char* reward, int qty, int tier, int WeekID)
{
    //2 consecutive weeks must have same tiers. No check will be made to create a new tier

    //get the tier ID
    int TierID = TierToIndex(Leaderboard, tier);

    //add the reward link if needed
    if(!LinkRewardExists(&(Leaderboard->RewardLinks[EX]), RewardLink))
        AddRewardLink(&(Leaderboard->RewardLinks[EX]), RewardLink);

    //extract the right leaderboard and tunnels parameters to SL_CheckRewardStates()
    SL_CheckRewardStates(&(Leaderboard->SubLeaderboard[TierID]), rank, reward, qty, WeekID);
}

void FreeLeaderboard(t_Leaderboard* Leaderboard)
{
    //free all SubLeaderboard structures
    for(int i = 0; i < Leaderboard->NbTiers; i++)
        FreeSubLeaderboard(&(Leaderboard->SubLeaderboard[i]));

    //free the subleaderboard array
    free(Leaderboard->SubLeaderboard);
    Leaderboard->SubLeaderboard = NULL;

    //free reward links
    FreeRewardLinks(&(Leaderboard->RewardLinks));

    //other members
    Leaderboard->NbTiers = 0;
}












