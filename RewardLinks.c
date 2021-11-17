#include "RewardLinks.h"



//Init the RewardLink structure
void InitRewardLinks(t_RewardLinks* RewardLinks)
{
    RewardLinks->NbLink = 0;
    RewardLinks->Links = (char**) malloc(sizeof(char*));
    if (RewardLinks->Links == NULL)
        exit(EXIT_FAILURE);
}

//Add a link to the structure
void AddRewardLink(t_RewardLinks* RewardLinks, char* str)
{
    int NewSize = RewardLinks->NbLink + 1;
    int RewardLinkStrLen = strlen(str) + 1;

    //realloc memory for a new entry
    RewardLinks->NbLink = NewSize;
    RewardLinks->Links = (char**) realloc(RewardLinks->Links,NewSize*sizeof(char*));
    if (RewardLinks->Links == NULL)
        exit(EXIT_FAILURE);

    //create a new entry
    RewardLinks->Links[NewSize-1] = (char*) malloc(RewardLinkStrLen*sizeof(char));
    if (RewardLinks->Links[NewSize-1] == NULL)
        exit(EXIT_FAILURE);
    strcpy(RewardLinks->Links[NewSize-1],str);

}

//Check if a link is already in the structure
int LinkRewardExists(t_RewardLinks* RewardLinks, char* str)
{
    //for each Link registered...
    for(int i = 0; i < RewardLinks->NbLink; i++)
    {
        //if link exists, return true
        if(strcmp(RewardLinks->Links[i],str) == 0)
            return 1;
    }

    //if link has not been found, return false
    return 0;
}

//free the RewardLink structure
void FreeRewardLinks(t_RewardLinks* RewardLinks)
{
    //for each Link registered...
    for(int i = 0; i < RewardLinks->NbLink; i++)
    {
        //free a link
        free(RewardLinks->Links[i]);
        RewardLinks->Links[i] = NULL;
    }

    //free the rest of the structure
    free(RewardLinks->Links);
    RewardLinks->Links = NULL;
    RewardLinks->NbLink = 0;
}




