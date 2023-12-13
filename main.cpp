
#include <bits/stdc++.h>

#include "MatchSchedule.h"
#include "OngoingMatchScore.h"
#include "PlayerInformation.h"
#include "PremierLeagueScheduler.h"
#include "RandomDecissionTree.h"
#include "PlayerRanking.h"

using namespace std;



int main(){

    printf("\n\n\t\t\tCricket Score Board\n\n");
    int option=1;
    while(option){
            printf("1. Upcoming Matches.\n");
            printf("2. Schedule a Tournament.\n");

            printf("3. Player Information.\n");
            printf("4. Ongoing Match Score Update.\n");
            printf("5. Predict the winner.\n");
            printf("6. Show Player Rank List.\n");
            printf("Select One( 0 for quit) : ");
            scanf("%d",&option);

            if(option==1)
                UpcomingMatch();
            else if(option == 2)
                PremierLeagueScheduling();
            else if(option == 3)
                PlayerInformation();
            else if(option == 4){
                UpdateScore();
            }
            else if(option == 5){
                Prediction();
            }
            else if(option == 6){
                ListOfPlayerRanking();
            }
            else
                printf("Choose correctly");
    }
    return 0;
}

