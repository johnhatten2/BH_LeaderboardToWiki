#ifndef PROJECTDEFINES_H_INCLUDED
#define PROJECTDEFINES_H_INCLUDED

#define EX_WEEK TRIAL_WEEK
#define CUR_WEEK GAUNTLET_WEEK

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

enum LeaderboardID
{
    PVP_RANKS = 0,
    PVP_POINTS = 1,
    TG_RANKS = 2,
    TG_POINTS = 3,
};


// PROGRAM ASSUMPTIONS
// 2 consecutive weeks contains the same tiers
// The header line of each .csv should be "RewardLink,RankMin,RankMax,ZoneMin,ZoneMax,LabelDescription,Rarity,PoolQty"
// Data do not contain commas


#endif // PROJECTDEFINES_H_INCLUDED
