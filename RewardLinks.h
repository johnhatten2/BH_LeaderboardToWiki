#ifndef REWARDLINKS_H_INCLUDED
#define REWARDLINKS_H_INCLUDED

#include <stdlib.h>
#include <string.h>


//contains few Reward Links. A set of Reward Links defines leaderboard rewards for a given week.
typedef struct
{
    char** Links;
    int NbLink;
}t_RewardLinks;




void InitRewardLinks(t_RewardLinks* RewardLinks);
void AddRewardLink(t_RewardLinks* RewardLinks, char* str);
int LinkRewardExists(t_RewardLinks* RewardLinks, char* str);
void FreeRewardLinks(t_RewardLinks* RewardLinks);

/**
TEST CODE

    t_RewardLinks RewardLinks;
    InitRewardLinks(&RewardLinks);
    AddRewardLink(&RewardLinks, "semaine 1");
    AddRewardLink(&RewardLinks, "semaine 2");
    if(LinkRewardExists(&RewardLinks, "semaine 3")
        AddRewardLink(&RewardLinks, "semaine 3");
    FreeRewardLinks(&RewardLinks);

**/


#endif // REWARDLINKS_H_INCLUDED
