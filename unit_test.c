#include "unit_test.h"

int faultNb = 0;





static void TestSubLeaderboard(void);
static void TestLeaderboard(void);

/***********************************/
/*         MAIN FUNCTIONS         **/
/***********************************/

void unitTestMain(void)
{
    TestSubLeaderboard();
    TestLeaderboard();

    printf("\nunit tests ends SUCCESSFULLY with %d faults\n", faultNb);
}

void validateData(const char* caller, int line, int testCondition)
{
    if (!testCondition)
    {
        faultNb++;
        printf("Unit test failed at %s line %d\n", caller, line);
    }
}

/***********************************/
/*         TEST FUNCTIONS         **/
/***********************************/

static void TestSubLeaderboard(void)
{
    t_SubLeaderboard* SubLeaderboard = InitSubLeaderboard(6);
    validateData(__FUNCTION__, __LINE__, SubLeaderboard->NbRanks == 0);
    validateData(__FUNCTION__, __LINE__, SubLeaderboard->NbRewards == 0);
    validateData(__FUNCTION__, __LINE__, SubLeaderboard->Tier == 6);

    AddSubLeaderboardData(SubLeaderboard, "1500", "regs", 100, 1);
    AddSubLeaderboardData(SubLeaderboard, "2500", "frags", 100, 1);
    AddSubLeaderboardData(SubLeaderboard, "3500", "guts", 100, 2);
    validateData(__FUNCTION__, __LINE__, SubLeaderboard->NbRanks == 3);
    validateData(__FUNCTION__, __LINE__, SubLeaderboard->NbRewards == 3);
    validateData(__FUNCTION__, __LINE__, !strcmp(SubLeaderboard->Ranks[1], "2500"));
    validateData(__FUNCTION__, __LINE__, !strcmp(SubLeaderboard->Rewards[2], "guts"));
    validateData(__FUNCTION__, __LINE__, SubLeaderboard->RewardState[0] == 1);
    validateData(__FUNCTION__, __LINE__, SubLeaderboard->RewardState[2] == 2);
    validateData(__FUNCTION__, __LINE__, SubLeaderboard->Qty[0][0] == 100);
    validateData(__FUNCTION__, __LINE__, SubLeaderboard->Qty[0][1] == 0);

    AddSubLeaderboardRank(SubLeaderboard, "123");
    validateData(__FUNCTION__, __LINE__, SubLeaderboard->NbRanks == 4);
    validateData(__FUNCTION__, __LINE__, !strcmp(SubLeaderboard->Ranks[3], "123"));

    AddSubLeaderboardReward(SubLeaderboard, "potato", 1);
    validateData(__FUNCTION__, __LINE__, SubLeaderboard->NbRewards == 4);
    validateData(__FUNCTION__, __LINE__, !strcmp(SubLeaderboard->Rewards[3], "potato"));
    validateData(__FUNCTION__, __LINE__, SubLeaderboard->RewardState[3] == 1);

    int rank = GetRankPos(SubLeaderboard, "3500");
    int reward = GetRewardPos(SubLeaderboard, "guts");
    validateData(__FUNCTION__, __LINE__, rank == 2);
    validateData(__FUNCTION__, __LINE__, reward == 2);

    FreeSubLeaderboard(SubLeaderboard);
}

static void TestLeaderboard(void)
{

    t_Leaderboard Leaderboard;
    InitLeaderboard(&Leaderboard);
    validateData(__FUNCTION__, __LINE__, Leaderboard.NbTiers == 0);

    AddLeaderboardData(&Leaderboard, "1000", "frags", 100, 3, 1);
    AddLeaderboardData(&Leaderboard, "1000", "frags", 101, 6, 1);
    AddLeaderboardData(&Leaderboard, "2000", "mguts", 102, 3, 2);
    validateData(__FUNCTION__, __LINE__, Leaderboard.NbTiers == 2);
    validateData(__FUNCTION__, __LINE__, Leaderboard.SubLeaderboard[0]->Tier == 3);
    validateData(__FUNCTION__, __LINE__, Leaderboard.SubLeaderboard[1]->Tier == 6);
    validateData(__FUNCTION__, __LINE__, Leaderboard.SubLeaderboard[0]->NbRanks == 2);
    validateData(__FUNCTION__, __LINE__, Leaderboard.SubLeaderboard[0]->NbRewards == 2);
    validateData(__FUNCTION__, __LINE__, Leaderboard.SubLeaderboard[0]->Qty[0][0] == 100);
    validateData(__FUNCTION__, __LINE__, Leaderboard.SubLeaderboard[0]->Qty[1][1] == 102);

    AddLeaderboardData(&Leaderboard, "1000", "frags", 103, 3, 1);
    AddLeaderboardData(&Leaderboard, "1000", "mguts", 104, 3, 0);
    validateData(__FUNCTION__, __LINE__, Leaderboard.SubLeaderboard[0]->Qty[0][0] == 103);
    validateData(__FUNCTION__, __LINE__, Leaderboard.SubLeaderboard[0]->Qty[1][1] == 102);
    validateData(__FUNCTION__, __LINE__, Leaderboard.SubLeaderboard[0]->Qty[0][1] == 104);
    validateData(__FUNCTION__, __LINE__, Leaderboard.SubLeaderboard[0]->Qty[1][0] == 0);

    FreeLeaderboard(&Leaderboard);
}





