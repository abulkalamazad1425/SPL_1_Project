#ifndef PLAYERINFORMATION_H_INCLUDED
#define PLAYERINFORMATION_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct Player_inf
{
    char name[30];
    int age;
    char status[10];
    int matches;
    int total_Run;
    double average;
    double strikeRate;
    int Fifty;
    int Hundred;
    char Country[30];
}Batsman[1000];

struct Player_inf2
{
    char name[30];
    int  age;
    char status[10];
    int matches;
    int wkt;
    double economy;
    int lowScore;
    int mostWkt;
    char Country[30];
}Bowler[1000];


int PlayerInformation()
{
    int option=1;
    FILE *BIFP,*BOIFP ;
    BIFP =  fopen("BatsmanInformation.txt","r");
    if(BIFP == NULL)
        {
        printf("\nError occur while open \"BatsmanInformation.txt\" file\n" );
        printf("Please check....\n");
        exit(1);
    }


    BOIFP =  fopen("BowlerInformation.txt","r");
    if(BOIFP == NULL)
        {
        printf("\nError occur while open \"BowlerInformation.txt\" file\n" );
        printf("Please check....\n");
        exit(1);
    }

    int Bowler_Index = 0;
    while(!feof(BOIFP)){

        if(Bowler_Index >= 1000){
            break;
        }

        fscanf(BOIFP,"%s",Bowler[Bowler_Index].name);

        fscanf(BOIFP,"%d",&Bowler[Bowler_Index].age);
        fscanf(BOIFP,"%s",Bowler[Bowler_Index].status);
        fscanf(BOIFP,"%d",&Bowler[Bowler_Index].matches);
        fscanf(BOIFP,"%d",&Bowler[Bowler_Index].wkt);
        fscanf(BOIFP,"%lf",&Bowler[Bowler_Index].economy);
        fscanf(BOIFP,"%d",&Bowler[Bowler_Index].lowScore);
        fscanf(BOIFP,"%d",&Bowler[Bowler_Index].mostWkt);
        fscanf(BOIFP,"%s",Bowler[Bowler_Index].Country);
        Bowler_Index++;
    }


    int Batsman_Index=0;
    while(!feof(BIFP)){
        if(Batsman_Index >= 1000){
            break;
        }
        fscanf(BIFP,"%s",Batsman[Batsman_Index].name);
        fscanf(BIFP,"%d",&Batsman[Batsman_Index].age);
        fscanf(BIFP,"%s",Batsman[Batsman_Index].status);
        fscanf(BIFP,"%d",&Batsman[Batsman_Index].matches);
        fscanf(BIFP,"%d",&Batsman[Batsman_Index].total_Run);
        fscanf(BIFP,"%lf",&Batsman[Batsman_Index].average);
        fscanf(BIFP,"%lf",&Batsman[Batsman_Index].strikeRate);
        fscanf(BIFP,"%d",&Batsman[Batsman_Index].Fifty);
        fscanf(BIFP,"%d",&Batsman[Batsman_Index].Hundred);
        fscanf(BIFP,"%s",Batsman[Batsman_Index].Country);
        Batsman_Index++;
    }

    do
    {


            printf("\nWhat types of information do you need :\n ");
            printf("1. Batting Statistics of a player.\n");
            printf("2. Bowling Statistics of a player.\n");
            printf("Choose one option (0 for quit) : ");
            scanf("%d",&option);
            if(option==0){
                break;
            }
            else if(option==1)
            {
                int i=0;
                char player_Name[30];
                printf("Enter the name of player : ");
                scanf("%s",player_Name);
                printf("\nName\tAge \tPlaying Role\tMat\tRuns\tFiftys\tHundreds\tAverage\t\tStrike Rate\tCountry\n");
                do
                {
                    if(!strcmp(player_Name,Batsman[i].name))
                    {
                        printf("%s\t",Batsman[i].name);
                        printf("%d\t",Batsman[i].age);
                        printf("%s\t\t",Batsman[i].status);
                        printf("%d\t",Batsman[i].matches);
                        printf("%d\t",Batsman[i].total_Run);
                        printf("%d\t",Batsman[i].Fifty);
                        printf("%d\t\t",Batsman[i].Hundred);
                        printf("%lf\t",Batsman[i].average);
                        printf("%lf\t",Batsman[i].strikeRate);
                        printf("%s\t",Batsman[i].Country);

                        break;
                    }
                    i++;
                }while(i<Batsman_Index);
                if(i==Batsman_Index)
                    {
                    printf("\nPlayer %s's information does not include in this list.\n",player_Name);

                }




            }
            else if(option==2)
            {
                int i=0;
                char player_Name[30];
                printf("Enter the name of player : ");
                scanf("%s",player_Name);
                printf("\nName\tAge \tPlaying Role\tMat\tWickets\tEconomy\t\tBest Figure\tMost Wicket\tCountry\n");
                do
                {
                    if(!strcmp(player_Name,Bowler[i].name))
                    {
                        printf("%s\t",Bowler[i].name);
                        printf("%d\t",Bowler[i].age);
                        printf("%s\t",Bowler[i].status);
                        printf("%d\t",Bowler[i].matches);
                        printf("%d\t",Bowler[i].wkt);
                        printf("%lf\t",Bowler[i].economy);
                        printf("%d/10\t\t",Bowler[i].lowScore);
                        printf("%d\t\t",Bowler[i].mostWkt);
                        printf("%s\t",Bowler[i].Country);
                        break;
                    }
                    i++;
                }while(i<Bowler_Index);
                if(i == Bowler_Index)
                    {
                    printf("\nPlayer %s's information does not include in this list.\n",player_Name);

                }
            }
        }while(1);

        fclose(BIFP);
        fclose(BOIFP);
        return 0;

}



#endif // PLAYERINFORMATION_H_INCLUDED
