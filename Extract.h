#ifndef EXTRACT_H_INCLUDED
#define EXTRACT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Leaderboard.h"
#include "LookUpTables.h"
#include "ProjectDefines.h"

#define DATA_SIZE 64
#define LINE_SIZE 512

/******EXTRACT FROM .CSV********/
void ExtractData(t_Leaderboard* Leaderboard, char* FilePath, int week, int PointsOrRanks, int MainOrEx);

void FormatNumberStrings(char* str);
int IsRune(char* Reward);
int MixedTiersCorrection(int i);



/********PRINT TO WIKI**********/
void GenerateLeaderboardPage(t_Leaderboard Leaderboard[]);
void PrintTopOfPage(FILE * fp, t_RewardLinks* LinksArr[]);
void GenerateTable(FILE * fp, t_SubLeaderboard* SubLeaderboard, char* TableName, int RankOrPoints);
void PrintTopOfTable(FILE * fp, t_SubLeaderboard* SubLeaderboard, int** MaterialOrdering, char* TableName);
void PrintTableContent(FILE * fp, t_SubLeaderboard* SubLeaderboard, int** MaterialOrdering, int RankOrPoints);
void PrintEndOfTable(FILE * fp);

char GetOccurenceLetter(int RewardState);void swap(int* xp, int* yp);
void swap(int* xp, int* yp);
void sort(int** arr, int n);





#endif // EXTRACT_H_INCLUDED
