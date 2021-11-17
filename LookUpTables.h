#ifndef LOOKUPTABLES_H_INCLUDED
#define LOOKUPTABLES_H_INCLUDED

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))


#define RUNE_ARRAY {"Relic Rune", "Minor Rune", "Major Rune", "Meta Rune", "Artifact Rune"}

//see excel table for changes
#define MATERIAL_LOOKUP_TABLE {\
    {"Rune-mythic","[[File:Rune MinorMythicRandom.png|center|24px|link=Runes]]"},\
    {"Rune-legendary","[[File:Rune MinorLegendaryRandom.png|center|24px|link=Runes]]"},\
    {"Rune-epic","[[File:Rune_MinorEpicRandom.png|center|24px|link=Runes]]"},\
    {"Rune-rare","[[File:Rune_MinorRareRandom.png|center|24px|link=Runes]]"},\
    {"Rune-common","[[File:Rune_MinorCommonRandom.png|center|24px|link=Runes]]"},\
    {"Cosmetic Chest","[[File:Consumable CosmeticChest.png|center|24px|link=Cosmetics]]"},\
    {"Mythic Material Chest","[[File:Chest MythicMaterial.png|center|24px|link=]]"},\
    {"Item Chest-legendary","[[File:Chest LegendaryItem.png|center|24px|link=]]"},\
    {"Item Chest-epic","[[File:Chest EpicItem.png|center|24px|link=]]"},\
    {"Item Chest-rare","[[File:Chest RareItem.png|center|24px|link=]]"},\
    {"Hyper Shard","[[File:Material HyperShard.png|center|24px|link=Materials#Hyper_Shard]]"},\
    {"Doubloon","[[File:Material Doubloon.png|center|24px|link=Materials#Doubloon]]"},\
    {"Rom Bit","[[File:Material RomBit.png|center|24px|link=Materials#Rom_Bit]]"},\
    {"Luminous Stone","[[File:Material LuminousStone.png|center|24px|link=Materials#Luminous_Stone]]"},\
    {"Beanstalk","[[File:Material Beanstalk.png|center|24px|link=Materials#Beanstalk]]"},\
    {"Crubble","[[File:Material Crubble.png|center|24px|link=Materials#Crubble]]"},\
    {"Fire Blossom","[[File:Material FireBlossom.png|center|24px|link=Materials#Fire_Blossom]]"},\
    {"Power Stone","[[File:Material PowerStone.png|center|24px|link=Materials#Power_Stone]]"},\
    {"Monster Cell","[[File:Material MonsterCell.png|center|24px|link=Materials#Monster_Cell]]"},\
    {"Sand clock","[[File:Material SandClock.png|center|24px|link=Materials#Sand_Clock]]"},\
    {"Administratium","[[File:Material Administratium.png|center|24px|link=Materials#Administratium]]"},\
    {"golden harp","[[File:Material_GoldenHarp.png|center|24px|link=Materials#Golden_Harp]]"},\
    {"Rare Material","[[File:Material RareMaterial.png|center|24px|link=Materials#Rare_Material]]"},\
    {"Epic Material","[[File:Material_EpicMaterial.png|center|24px|link=Materials#Epic_Material]]"},\
    {"gold","[[File:Currency Gold.png|center|24px|link=]]"},\
    {"gems","[[File:Currency Gems.png|center|24px|link=]]"},\
    {"Rune Fragment","[[File:Material_RuneFragment.png|center|24px|link=Materials#Rune_Fragment]]"},\
    {"Elemental Fragment","[[File:Material_ElementalFragment.png|center|24px|link=Materials#Elemental_Fragment]]"},\
    {"Regulator","[[File:Material_Regulator.png|center|24px|link=Materials#Regulator]]"},\
    {"Mount Guts","[[File:Material_MountGuts.png|center|24px|link=Materials#Mount_Guts]]"}}




    int MaterialToWikitextID(char* material);
    char* IndexToWikitext(int i);
    char* IndexToReward(int i);




/**
TEST CODE

    int pos;
    char* str = (char*)malloc(128*sizeof(char));
    pos = MaterialToWikitext(str, "Doubloon");
    printf("%d:%s\n",pos,str);

**/




#endif // LOOKUPTABLES_H_INCLUDED
