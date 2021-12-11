#include "Extract.h"






/***********************************/
/*        EXTRACT FROM .CSV       **/
/***********************************/

void ExtractData(t_Leaderboard* Leaderboard, char* FilePath, int week, int PointsOrRanks, int MainOrEx)
{
    //init the file pointer and a string variable
    char * line = malloc(LINE_SIZE*sizeof(char));
    strcpy(line, WORKSPACE);
    strcat(line, FilePath);

    FILE * fp;
    fp = fopen(line, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    //extraction variables
    char RewardLink[DATA_SIZE];
    char RankMin[DATA_SIZE];
    char RankMax[DATA_SIZE];
    char Rank[DATA_SIZE];
    char ZoneMin[DATA_SIZE];
    char ZoneMax[DATA_SIZE];
    char Reward[DATA_SIZE];
    char Rarity[DATA_SIZE];
    char Qty[DATA_SIZE];


    //read the header line. Exit if not compliant to expected HEADER_LINE
    fgets(line, LINE_SIZE, fp);
    if(strcmp(line, HEADER_LINE))
    {
        printf("HeaderLine error : %s",line);
        printf("Expected :         %s",HEADER_LINE);
        return;
    }

    //for every line...
    while(fgets(line, LINE_SIZE, fp))
    {
        //*****EXTRACT DATA*******//

        //first data aka RewardLink
        char* token = strtok(line, ",");
        strcpy(RewardLink,token);

        //second data aka RankMin
        token = strtok(NULL, ",");
        strcpy(RankMin,token);

        //third data aka RankMax
        token = strtok(NULL, ",");
        strcpy(RankMax,token);

        //4th data aka ZoneMin
        token = strtok(NULL, ",");
        strcpy(ZoneMin,token);

        //5th data aka ZoneMax
        token = strtok(NULL, ",");
        strcpy(ZoneMax,token);

        //6th data aka LabelDescription aka Reward
        token = strtok(NULL, ",");
        strcpy(Reward,token);

        //7th data aka Rarity
        token = strtok(NULL, ",");
        strcpy(Rarity,token);

        //8th data aka Qty
        token = strtok(NULL, ",");
        strcpy(Qty,token);



        //*****PARSE DATA*******//

        //if the reward is a rune, exclude rune type, include rune rarity
        if(IsRune(Reward))
        {
            strcpy(Reward, "Rune-");
            strcat(Reward, Rarity);
        }

        //if the reward is a an item chest, include rarity
        if(strcmp(Reward, "Item Chest") == 0)
        {
            strcat(Reward, "-");
            strcat(Reward, Rarity);
        }

        //points logic
        if(PointsOrRanks == POINTS)
        {
            //format numbers to a new format (7.5K, 99M)
            FormatNumberStrings(RankMin);

            //points works on lower bounds
            strcpy(Rank,RankMin);
        }

        //ranks logic
        else if (PointsOrRanks == RANKS)
        {
            //if lower and upper bounds are the same, save only 1 of them
            if(strcmp(RankMax, RankMin) == 0)
                strcpy(Rank,RankMax);

            //if they are different...
            else
            {
                //save a range (ex. 1001-2000)
                strcpy(Rank,RankMin);
                strcat(Rank, "-");
                strcat(Rank, RankMax);
            }
        }

        //when PointsOrRanks is UNINITIALIZED
        else
            break;



        //*****SEND DATA*******//

        //for each tier between ZoneMin and ZoneMax
        for(int i = atoi(ZoneMin); i < atoi(ZoneMax) + 1; i++)
        {
            //for tier bracketing
            i = MixedTiersCorrection(i);

            //main data acquisition
            if(MainOrEx == MAIN)
                AddLeaderboardData(Leaderboard, Rank, Reward, atoi(Qty), i, week);

            //secondary data acquisition
            else if(MainOrEx == EX) //TODO
                CheckRewardStates(Leaderboard, RewardLink, Rank, Reward, atoi(Qty), i, week);
        }
    }

    //close file and exit
    fclose(fp);
    free(line);
    line = NULL;
}

void FormatNumberStrings(char* str)
{
    char EndLetter[2] = {0,'\0'};
    char SignificantNumbers[4] = {0,0,0,'\0'};

    //get a copy of the number as a long
    char* endptr;
    long nbr = strtol(str, &endptr, 10);

    //number in billions
    if(nbr >= 1000000000)
    {
        EndLetter[0] = 'G';
        nbr /= 1000000;
    }

    //number in millions
    else if(nbr >= 1000000)
    {
        EndLetter[0] = 'M';
        nbr /= 1000;
    }

    //number in thousands
    else if(nbr >= 1000)
        EndLetter[0] = 'K';

    //number in units
    else
        return;

    //extract significant numbers.
    if(nbr < 10000)
    {
        //9900 becomes 9.9
        SignificantNumbers[0] = str[0];
        SignificantNumbers[1] = '.';
        SignificantNumbers[2] = str[1];
    }

    else if(nbr < 100000)
    {
        //99000 becomes 99
        SignificantNumbers[0] = str[0];
        SignificantNumbers[1] = str[1];
        SignificantNumbers[2] = '\0';
    }

    else
    {
        //750000 becomes 750
        SignificantNumbers[0] = str[0];
        SignificantNumbers[1] = str[1];
        SignificantNumbers[2] = str[2];
    }

    //returns the input string in the new format
    strcpy(str, SignificantNumbers);
    strcat(str, EndLetter);
}

//TODO update to include augments
int IsRune(char* Reward)
{
    const char* RuneArray[] = RUNE_ARRAY;

    //scroll through the rune table
    for(int i = 0; i < ARRAY_SIZE(RuneArray); i++)
    {
        //if the reward is a rune, return true
        if(strcmp(Reward, RuneArray[i]) == 0)
            return 1;
    }

    //if the rewards is not a rune, return false
    return 0;
}

int MixedTiersCorrection(int i)
{
    //mixed tiers. Add lines for mixed tier events
    if(i==1) return 3;  //tier 1 is considered tier 3
    if(i==2) return 3;  //tier 2 is considered tier 3


    return i;           //no correction needed;
}






/***********************************/
/*         PRINT TO WIKI          **/
/***********************************/


void GenerateLeaderboardPage(t_Leaderboard Leaderboard[])
{
    FILE * fp;
    fp = fopen ("output.txt", "w");

    //starts printing
    //PrintTopOfPage(fp,LinksArr);
    fprintf(fp, "{{LastEdit}}\n");

    //for each tier...
    for(int TierIndex = 0; TierIndex < Leaderboard[0].NbTiers; TierIndex++)
    {
        //small header for table of content
        fprintf(fp, "== Tier %d ==\n", Leaderboard[TG_RANKS].SubLeaderboard[TierIndex]->Tier);
        fprintf(fp, "\n");

        //generate the 4 tables
        GenerateTable(fp, &(Leaderboard[TG_RANKS].SubLeaderboard[TierIndex]), "T/G Ranking Rewards", RANKS);
        GenerateTable(fp, &(Leaderboard[PVP_RANKS].SubLeaderboard[TierIndex]), "PvP Ranking Rewards", RANKS);
        GenerateTable(fp, &(Leaderboard[TG_POINTS].SubLeaderboard[TierIndex]), "T/G Points Rewards", POINTS);
        GenerateTable(fp, &(Leaderboard[PVP_POINTS].SubLeaderboard[TierIndex]), "PvP Points Rewards", POINTS);
    }

    //End of page
    fprintf(fp, "\n");
    fprintf(fp, "<noinclude> \n");
    fprintf(fp, "Template used by [[User:Johnhatten2|John_hatten2]] to insert the tables into the Leaderboard Rewards page.\n");
    fprintf(fp, "\n");
    fprintf(fp, "{{WLH}}\n");
    fprintf(fp, "</noinclude>\n");
    fprintf(fp, "\n");
    fprintf(fp, "<!--\n");//start of comment
    fprintf(fp, "\n");
    fprintf(fp, "\n");
    fprintf(fp, "Me when the autogeneration works : \n");
    fprintf(fp, "https://www.youtube.com/watch?v=vx0lCdRRL-Q\n");
    fprintf(fp, "-->\n");//end of comment

    //close output file
    fclose(fp);
}

void PrintTopOfPage(FILE * fp, t_RewardLinks* LinksArr[])
{
    //TODO update this
    //start of wiki page
    fprintf(fp, "{{TOC right}}\n");
    fprintf(fp, "This page has been autogenerated by [[User:ChubbyDaemon|ChubbyDaemon]] and [[User:John_hatten2|John_hatten2]].\n");
    fprintf(fp, "\n");
    fprintf(fp, "PLEASE CONTACT THEM IF YOU WANT TO MAKE CHANGES TO THIS PAGE. The autogeneration code will overwrite any changes made here.\n");
    fprintf(fp, "\n");
    fprintf(fp, "\n");
    fprintf(fp, "This page contains the all the [[PvP]], [[Trials|Trial and Gauntlet]] leaderboard's rewards. These rewards depends on the tier you were after you first PvP or T/G battle, after the weekly reset.\n");
    fprintf(fp, "\n");
    fprintf(fp, "* Players from tier 1, 2 and 3 are on the same leaderboard. Every tier after is a separate leaderboard.\n");
    fprintf(fp, "* The rune type changes every week (minor, major, meta, artifact, relic). They can be replaced by accessories and pets too on special occasions.\n");
    fprintf(fp, "* T/G and PVP ranking rewards in T13, T14, and T15 will rotate between Regulators and Gems (while one is gems, the other one is regulators). We identify them by a letter. A reward marked with T means it is only available while trial event is active\n");
    fprintf(fp, "\n");
    fprintf(fp, "{| class=\"article-table\" style=\"text-align: center;\"\n");
    fprintf(fp, "|-\n");
    fprintf(fp, "|colspan=\"2\" | Reward Occurence\n");
    fprintf(fp, "|-\n");
    fprintf(fp, "|B\n");
    fprintf(fp, "|Both weeks\n");
    fprintf(fp, "|-\n");
    fprintf(fp, "|G\n");
    fprintf(fp, "|Gauntlet week only\n");
    fprintf(fp, "|-\n");
    fprintf(fp, "|T\n");
    fprintf(fp, "|trial week only\n");
    fprintf(fp, "|}\n");
    fprintf(fp, "\n");
    fprintf(fp, "\n");
}

void GenerateTable(FILE * fp, t_SubLeaderboard* SubLeaderboard, char* TableName, int RankOrPoints)
{
    int NbRewards = SubLeaderboard->NbRewards;
    int** MaterialOrdering = (int**)malloc(NbRewards*sizeof(int*));

    //for each reward...
    for(int i = 0; i < NbRewards; i++)
    {
        MaterialOrdering[i] = (int*)malloc(2*sizeof(int));  //Column 0 is LeaderboardRewards index, column 1 is WikiLookupTable index

        //gather material indices
        MaterialOrdering[i][0] = i;
        MaterialOrdering[i][1] = MaterialToWikitextID(SubLeaderboard->Rewards[i]);
    }

    //sort MaterialOrdering table
    sort(MaterialOrdering, NbRewards);

    //print the whole table
    PrintTopOfTable(fp, SubLeaderboard, MaterialOrdering, TableName);
    PrintTableContent(fp, SubLeaderboard, MaterialOrdering, RankOrPoints);
    PrintEndOfTable(fp);

    //free Material ordering table
    for(int i = 0; i < NbRewards; i++)
    {
        free(MaterialOrdering[i]);
        MaterialOrdering[i] = NULL;
    }

    free(MaterialOrdering);
    MaterialOrdering = NULL;
}

void PrintTopOfTable(FILE * fp, t_SubLeaderboard* SubLeaderboard, int** MaterialOrdering, char* TableName)
{
    int NbRewards = SubLeaderboard->NbRewards;
    int tier = SubLeaderboard->Tier;

    //starts printing table
    fprintf(fp, "{| class=\"mw-collapsible mw-collapsed article-table\" style=\"text-align: center;\"\n");
    fprintf(fp, "|colspan=\"%d\" | T%d %s\n", NbRewards+1, tier, TableName);
    fprintf(fp, "|-\n");
    fprintf(fp, "| '''Occurence'''\n");

    //occurence header
    for(int i = 0; i < NbRewards; i++)
        fprintf(fp, "|%c\n", GetOccurenceLetter(SubLeaderboard->RewardState[MaterialOrdering[i][0]]));

    fprintf(fp, "|-\n");
    fprintf(fp, "| '''Rank'''\n");

    //Material images (wikitext format)
    for(int i = 0; i < NbRewards; i++)
        fprintf(fp, "|%s\n", IndexToWikitext(MaterialOrdering[i][1]));
}

void PrintTableContent(FILE * fp, t_SubLeaderboard* SubLeaderboard, int** MaterialOrdering, int RankOrPoints)
{
    int row;

    //for each row...
    for(int i = 0; i < SubLeaderboard->NbRanks; i++)
    {
        //ranks means lower number on top
        if(RankOrPoints == RANKS)
            row = i;

        //points means higher numbers on top
        else
            row = SubLeaderboard->NbRanks - i - 1;

        //new line and rank
        fprintf(fp, "|-\n");
        fprintf(fp, "| '''%s'''\n", SubLeaderboard->Ranks[row]);

        //for each rewards...
        for(int j = 0; j < SubLeaderboard->NbRewards; j++)
        {
            //print "-" if Qty is null
            if(SubLeaderboard->Qty[row][MaterialOrdering[j][0]] == 0)
                fprintf(fp, "| -\n");

            //else, print the Qty
            else
                fprintf(fp, "| %d\n",SubLeaderboard->Qty[row][MaterialOrdering[j][0]]);
        }
    }
}

void PrintEndOfTable(FILE * fp)
{
    fprintf(fp, "|}\n");
    fprintf(fp, "\n");
}

char GetOccurenceLetter(int RewardState)
{
    if(RewardState == GAUNTLET_WEEK)
        return 'G';

    if(RewardState == TRIAL_WEEK)
        return 'T';

    if(RewardState == BOTH_WEEKS)
        return 'B';

    //else
    return ' ';
}

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Function to perform Selection Sort
// https://www.geeksforgeeks.org/c-program-to-sort-an-array-in-ascending-order/
void sort(int** arr, int n)
{
    int i, j, min_idx;

    // One by one move boundary of unsorted subarray
    for (i = 0; i < n - 1; i++) {

        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j][1] < arr[min_idx][1])
                min_idx = j;

        // Swap the found minimum element
        // with the first element
        swap(&arr[min_idx][1], &arr[i][1]);
        swap(&arr[min_idx][0], &arr[i][0]);
    }
}

