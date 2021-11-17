#include "LookUpTables.h"


static const char* LookupTable[][2] = MATERIAL_LOOKUP_TABLE;


int MaterialToWikitextID(char* material)
{
    //scroll through the first column
    for(int i = 0; i < ARRAY_SIZE(LookupTable); i++)
    {
        //when there is a match, returns the index
        if(strcmp(LookupTable[i][0],material)==0)
            return i;
    }

    //material not found
    printf("error : MaterialToWikitext : lookup value not found : %s\n", material);
    return -1;
}

char* IndexToWikitext(int i)
{
    return LookupTable[i][1];
}

char* IndexToReward(int i)
{
    return LookupTable[i][0];
}
