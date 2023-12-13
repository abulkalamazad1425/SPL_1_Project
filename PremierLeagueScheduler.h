#ifndef PREMIERLEAGUESCHEDULER_H_INCLUDED
#define PREMIERLEAGUESCHEDULER_H_INCLUDED
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char ArrayOfTeams[50][20];
int num_matches = 0;
char ListOfMatches[100][2][20];
int Round1Matches;

void SingleElimination(int numOfQualifiedTeam){

    for(int i=0;i<numOfQualifiedTeam/2;i++){
        num_matches++;
        strcpy(ListOfMatches[num_matches][0],ArrayOfTeams[i]);
        strcpy(ListOfMatches[num_matches][1],ArrayOfTeams[numOfQualifiedTeam-i-1]);

    }

}



void roundRobinTournament(int numOfTeams )

{

        char team1[30] ;

        if(numOfTeams%2 == 0)
            {
            numOfTeams++;
            strcpy(ArrayOfTeams[numOfTeams - 1] , "NULL");
        }

        strcpy(team1,ArrayOfTeams[0]);
        do
        {
            for( int i=1;i<=numOfTeams/2;i++)
            {

                if( strcmp(ArrayOfTeams[i],"NULL") && strcmp(ArrayOfTeams[numOfTeams-i],"NULL"))
                {
                    num_matches++;
                    strcpy(ListOfMatches[num_matches][0],ArrayOfTeams[i]);
                    strcpy(ListOfMatches[num_matches][1],ArrayOfTeams[numOfTeams-i]);

                }
            }

        char t[30];
        strcpy(t,ArrayOfTeams[numOfTeams-1]);

        for( int i=numOfTeams-1;i>0;i--)
        {

               strcpy( ArrayOfTeams[i],ArrayOfTeams[i-1]);
        }
        strcpy(ArrayOfTeams[0] , t);
    }while(strcmp(team1,ArrayOfTeams[0]));

}




void PremierLeagueScheduling()
{
    int numOfTeams;
    int date ;
    int month ;
    int year ;
    int numVenue;
    int choice;

    printf("\nWhat do you want :\n");
    printf("1. BPL Scheduling.\n");
    printf("2. IPL Scheduling.\n");
    printf("3. IITPL Scheduling.\n");
    printf("Enter your choice(1,2 or 3) : ");
    scanf("%d",&choice);

    FILE *MP;
    if(choice == 1)
    {
       MP = fopen("PremierLeagueInput.txt","r");
    }
    else if(choice == 2){
       MP = fopen("IPL_PremierLeagueInput.txt","r");

    }
    else if(choice == 3){
        MP = fopen("IITPL_SchedulingInput.txt","r");
    }

    if(MP == NULL)
    {
        printf("Error occur to open PremierLeagueInput.txt file .\n");
        printf("There might be some problem.\n");
        printf("Please check\n");
        exit(1);
    }


    fscanf(MP,"%d",&numOfTeams);


    for(int i=0;i<numOfTeams;i++)
    {

        fscanf( MP,"%s",ArrayOfTeams[i] );

    }

    fscanf(MP,"%d",&numVenue);

    char Venue[numVenue][20];
    for(int i=0;i<numVenue;i++)
        {
        fscanf(MP,"%s",Venue[i]);
    }
    fscanf(MP,"%d",&date);
    fscanf(MP,"%d",&month);
    fscanf(MP,"%d",&year);

    if(choice == 3){
        roundRobinTournament(numOfTeams );
    }
    else{
        roundRobinTournament(numOfTeams );
        roundRobinTournament(numOfTeams );
    }

    Round1Matches = num_matches;
    int numOfQualifiedTeam = 4;

    strcpy(ArrayOfTeams[0],"Qualifier-1");
    strcpy(ArrayOfTeams[1],"Qualifier-2");
    strcpy(ArrayOfTeams[2],"Qualifier-3");
    strcpy(ArrayOfTeams[3],"Qualifier-4");

    SingleElimination(numOfQualifiedTeam);




    printf("\nRound 1:\n");
    for(int i=1;i <= num_matches ;i++)
        {
        printf("Match %d :\t %s vs %s\t %d.%d.%d\t %s\n",i,ListOfMatches[i][0],ListOfMatches[i][1],date,month,year,Venue[i%numVenue]);
        if(i == Round1Matches)
        {
            date = date+2;
            printf("\nRound 2:\n");
        }
        if(i%2 == 0)
            {
            date++;
            if(date > 31)
            {
                date=1;
                month++;
                if(month > 12)
                {
                    month = 1;
                    year++;
                }
            }
        }
    }

    date = date+3;
    printf("\nFinal :\n");
    printf("Match %d :\t Finalist-1 vs Finalist-2\t %d.%d.%d\t Dhalka\n",num_matches+1,date,month,year);
    num_matches=0;
    fclose(MP);
    return;
}



#endif // PREMIERLEAGUESCHEDULER_H_INCLUDED
