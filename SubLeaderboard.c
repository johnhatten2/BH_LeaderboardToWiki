#include "SubLeaderboard.h"





t_SubLeaderboard* InitSubLeaderboard(int Tier)
{
    t_SubLeaderboard* SubLeaderboard = (t_SubLeaderboard*) malloc(sizeof(t_SubLeaderboard));
    if (SubLeaderboard->RewardState == NULL)
        exit(EXIT_FAILURE);

    SubLeaderboard->RewardState = (int*) malloc(sizeof(int*));
    if (SubLeaderboard->RewardState == NULL)
        exit(EXIT_FAILURE);

    SubLeaderboard->Qty = (int**) malloc(sizeof(int*));
    if (SubLeaderboard->Qty == NULL)
        exit(EXIT_FAILURE);

    SubLeaderboard->Qty[0] = (int*) malloc(sizeof(int));
    if (SubLeaderboard->Qty[0] == NULL)
        exit(EXIT_FAILURE);

    SubLeaderboard->Ranks = (char**) malloc(sizeof(char*));
    if (SubLeaderboard->Ranks == NULL)
        exit(EXIT_FAILURE);

    SubLeaderboard->Rewards = (char**) malloc(sizeof(char*));
    if (SubLeaderboard->Rewards == NULL)
        exit(EXIT_FAILURE);

    SubLeaderboard->Qty[0][0] = 0;
    SubLeaderboard->Tier = Tier;
    SubLeaderboard->NbRanks = 0;
    SubLeaderboard->NbRewards = 0;
    SubLeaderboard->RewardState[0] = 0;

    return SubLeaderboard;
}

void AddSubLeaderboardRank(t_SubLeaderboard* SubLeaderboard, char* str)
{
    int NewSize = SubLeaderboard->NbRanks + 1;
    int RankStrLen = strlen(str) + 1;

    //realloc Qty rows, malloc new row
    SubLeaderboard->Qty = (int**) realloc(SubLeaderboard->Qty, NewSize*sizeof(int*));
    if (SubLeaderboard->Qty == NULL)
        exit(EXIT_FAILURE);

    SubLeaderboard->Qty[NewSize-1] = (int*) malloc(SubLeaderboard->NbRewards*sizeof(int));
    if (SubLeaderboard->Qty[NewSize-1] == NULL)
        exit(EXIT_FAILURE);

    //realloc ranks, malloc new rank
    SubLeaderboard->Ranks = (char**) realloc(SubLeaderboard->Ranks, NewSize*sizeof(char*));
    if (SubLeaderboard->Ranks == NULL)
        exit(EXIT_FAILURE);

    SubLeaderboard->Ranks[NewSize-1] = (char*) malloc(RankStrLen*sizeof(char));
    if (SubLeaderboard->Ranks[NewSize-1] == NULL)
        exit(EXIT_FAILURE);

    //init and update them
    SubLeaderboard->NbRanks = NewSize;
    strcpy(SubLeaderboard->Ranks[NewSize-1], str);
    for(int i = 0; i < SubLeaderboard->NbRewards; i++)
        SubLeaderboard->Qty[NewSize-1][i] = 0;
}

int SubLeaderboardRankExists(t_SubLeaderboard* SubLeaderboard, char* str)
{
    //for each existing Rank...
    for(int i = 0; i < SubLeaderboard->NbRanks; i++)
    {
        //if Rank exists, return true
        if(strcmp(SubLeaderboard->Ranks[i],str) == 0)
            return 1;
    }

    //if rank has not been found, return false
    return 0;
}

void AddSubLeaderboardReward(t_SubLeaderboard* SubLeaderboard, char* str, int WeekID)
{
    int NewSize = SubLeaderboard->NbRewards + 1;
    int RewardStrLen = strlen(str) + 1;

    //for each Qty row...
    for(int i = 0; i < SubLeaderboard->NbRanks; i++)
    {
        //realloc to add a column
        SubLeaderboard->Qty[i] = (int*) realloc(SubLeaderboard->Qty[i], NewSize*sizeof(int));
        if (SubLeaderboard->Qty[i] == NULL)
            exit(EXIT_FAILURE);
    }

    //realloc Rewards strings
    SubLeaderboard->Rewards = (char**) realloc(SubLeaderboard->Rewards, NewSize*sizeof(char*));
    if (SubLeaderboard->Rewards == NULL)
        exit(EXIT_FAILURE);

    //malloc new string
    SubLeaderboard->Rewards[NewSize-1] = (char*) malloc(RewardStrLen*sizeof(char));
    if (SubLeaderboard->Rewards[NewSize-1] == NULL)
        exit(EXIT_FAILURE);

    //realloc RewardState
    SubLeaderboard->RewardState = (int*) realloc(SubLeaderboard->RewardState, NewSize*sizeof(int));
    if (SubLeaderboard->RewardState == NULL)
        exit(EXIT_FAILURE);

    //init and update other stuff
    SubLeaderboard->NbRewards = NewSize;
    SubLeaderboard->RewardState[NewSize-1] = WeekID;
    strcpy(SubLeaderboard->Rewards[NewSize-1], str);
    for(int i = 0; i < SubLeaderboard->NbRanks; i++)
        SubLeaderboard->Qty[i][NewSize-1] = 0;
}

int SubLeaderboardRewardExists(t_SubLeaderboard* SubLeaderboard, char* str)
{
    //for each existing Reward...
    for(int i = 0; i < SubLeaderboard->NbRewards; i++)
    {
        //if Reward exists, return true
        if(strcmp(SubLeaderboard->Rewards[i],str) == 0)
            return 1;
    }

    //if Reward has not been found, return false
    return 0;
}

void UpdateRewardState(t_SubLeaderboard* SubLeaderboard, int RewardPos, int WeekID)
{
    //TODO
    //|= (1 << WeekID )

}

int GetRankPos(t_SubLeaderboard* SubLeaderboard, char* rank)
{
    //for each rank...
    for(int i = 0; SubLeaderboard->NbRanks; i++)
    {
        //if the rank matches, returns the ID
        if(strcmp(SubLeaderboard->Ranks[i],rank)==0)
            return i;
    }

    //if no rank found, return -1
    return -1;
}

int GetRewardPos(t_SubLeaderboard* SubLeaderboard, char* reward)
{
    //for each reward...
    for(int i = 0; SubLeaderboard->NbRewards; i++)
    {
        //if the reward matches, returns the ID
        if(strcmp(SubLeaderboard->Rewards[i],reward)==0)
            return i;
    }

    //if no reward found, return -1
    return -1;

}

//creates new ranks (rows) and rewards (columns) if needed. insert a data at the specified place
void AddSubLeaderboardData(t_SubLeaderboard* SubLeaderboard, char* rank, char* reward, int qty, int WeekID)
{
    //check if rank exists
    if(!SubLeaderboardRankExists(SubLeaderboard, rank))
        AddSubLeaderboardRank(SubLeaderboard, rank);

    //check if reward exists
    if(!SubLeaderboardRewardExists(SubLeaderboard, reward))
        AddSubLeaderboardReward(SubLeaderboard, reward, WeekID);

    //get IDs
    int RankPos = GetRankPos(SubLeaderboard, rank);
    int RewardPos = GetRewardPos(SubLeaderboard, reward);

    //Insert data...
    if(SubLeaderboard->Qty[RankPos][RewardPos] == 0)
        SubLeaderboard->Qty[RankPos][RewardPos] = qty;

    //or update RewardState
    else
}



void FreeSubLeaderboard(t_SubLeaderboard* SubLeaderboard)
{
    for(int i = 0; i < SubLeaderboard->NbRanks; i++)
    {
        free(SubLeaderboard->Qty[i]);
        free(SubLeaderboard->Ranks[i]);
    }

    for(int i = 0; i < SubLeaderboard->NbRewards; i++)
    {
        free(SubLeaderboard->Rewards[i]);
    }

    free(SubLeaderboard->Qty);
    free(SubLeaderboard->Ranks);
    free(SubLeaderboard->Rewards);
    free(SubLeaderboard->RewardState);
    free(SubLeaderboard);
}
