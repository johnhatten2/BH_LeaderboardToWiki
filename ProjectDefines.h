#ifndef PROJECTDEFINES_H_INCLUDED
#define PROJECTDEFINES_H_INCLUDED


#define WORKSPACE "C:\\Users\\john-\\OneDrive\\Documents\\workspace\\CodeBlock\\LeaderboardsToWikiText\\DataPump\\"
#define TG_RANKS_PATH "2021-06-06\\TG Rank Rewards.csv"
#define EX_TG_RANKS_PATH "2021-05-31\\TG Rank Rewards.csv"
#define TG_POINTS_PATH "2021-06-06\\TG Point Rewards.csv"
#define PVP_RANKS_PATH "2021-06-06\\PvP Rank Rewards.csv"
#define EX_PVP_RANKS_PATH "2021-05-31\\PvP Rank Rewards.csv"
#define PVP_POINTS_PATH "2021-06-06\\PvP Point Rewards.csv"

#define HEADER_LINE "RewardLink,RankMin,RankMax,ZoneMin,ZoneMax,LabelDescription,Rarity,PoolQty\n"



enum MainOrEx
{
    MAIN = 0,
    EX = 1
};

enum PointsOrRanks
{
    POINTS = 0,
    RANKS = 1
};


#define PVP_RANKS 0
#define PVP_POINTS 1
#define TG_RANKS 2
#define TG_POINTS 3
#define EVENT_RANKS 4
#define EVENT_POINTS 5



#endif // PROJECTDEFINES_H_INCLUDED
