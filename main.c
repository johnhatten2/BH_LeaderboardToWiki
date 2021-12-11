#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>

#include "Leaderboard.h"
#include "Extract.h"
#include "ProjectDefines.h"
#include "unit_test.h"



//NEW tier TODO
//update ProjectDefines.h for csv links
//update LookUpTables.h for new materials
//update https://bit-heroes.fandom.com/wiki/Template:LeaderboardGenerate

// PROGRAM ASSUMPTIONS AND LIMITATIONS
// 2 consecutive weeks contains the same tiers
// The header line of each .csv should be "RewardLink,RankMin,RankMax,ZoneMin,ZoneMax,LabelDescription,Rarity,PoolQty"
// Data do not contain commas

//USEFULL INFO AND SOURCES
//https://en.wikipedia.org/wiki/Help:Table
//https://docs.google.com/spreadsheets/d/1QQvR8KsEoxJAzOj_IwPeZ0Cxrulx8TDs9-Ea2Z1NTNs/edit?usp=sharing
//https://bit-heroes.fandom.com/wiki/Template:LeaderboardGenerate


//TODO
//Extract data should not ask for NewOrCompare
//Extract leaderboard as is
//Extract leaderboard with restrictions

int main()
{
    unitTestMain();

    /*
    //init 4 leaderboards (PvP/TG and Points/Ranks)
    t_Leaderboard Leaderboards[4];
    InitLeaderboard(&Leaderboards[PVP_RANKS]);
    InitLeaderboard(&Leaderboards[PVP_POINTS]);
    InitLeaderboard(&Leaderboards[TG_RANKS]);
    InitLeaderboard(&Leaderboards[TG_POINTS]);

    //extract leaderboard data
    ExtractData(&Leaderboards[TG_RANKS], TG_RANKS_PATH, CUR_WEEK, RANKS, MAIN);
    ExtractData(&Leaderboards[TG_RANKS], EX_TG_RANKS_PATH, EX_WEEK, RANKS, EX);
    ExtractData(&Leaderboards[TG_POINTS], TG_POINTS_PATH, BOTH_WEEKS, POINTS, MAIN);
    ExtractData(&Leaderboards[PVP_RANKS], PVP_RANKS_PATH, CUR_WEEK, RANKS, MAIN);
    ExtractData(&Leaderboards[PVP_RANKS], EX_PVP_RANKS_PATH, EX_WEEK, RANKS, EX);
    ExtractData(&Leaderboards[PVP_POINTS], PVP_POINTS_PATH, BOTH_WEEKS, POINTS, MAIN);

    //generate output text
    GenerateLeaderboardPage(Leaderboards);

    //free leaderboards
    FreeLeaderboard(&Leaderboards[TG_RANKS]);
    FreeLeaderboard(&Leaderboards[TG_POINTS]);
    FreeLeaderboard(&Leaderboards[PVP_RANKS]);
    FreeLeaderboard(&Leaderboards[PVP_POINTS]);

    */
    return 0;
}





