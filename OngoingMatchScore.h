#ifndef ONGOINGMATCHSCORE_H_INCLUDED
#define ONGOINGMATCHSCORE_H_INCLUDED
#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

struct Batsman
{
    char playerName[20];
    int runsScored;
    int played_ball;
    double strikeRate;
};

struct Bowler
{
    char playerName[20];
    int runsLossed;
    int over[2];
    int wicket;
};

struct Details
{
    char name[30];
    struct Batsman batsman[11];
    struct Bowler bowler[11];
    int sixes;
    int total_over[2];
    int fours;
    int Num_Wicket;
    int total_runs;
    double CurrentRR;
    double RequiredRR;

}team[2];



int number_of_overs=3;
int target;
int B_team,F_team;
int toss;
int strk,Striker1 = 0,Striker2 = 1,bow = 0;
int thisOver[8],tO=0;
int IndexArr[11],IndexArrW[11];



void ScoreTable1();
void DisplayScoreBoard();
void SummaryTable();
void MergeSort(int f,int l);
void Merge(int f,int m,int l);
void MergeSortByWicket(int f,int l);
void MergeforWicket(int f,int m,int l);



void getTeamAndPlayerNames()
{
    FILE *PNP;
    PNP = fopen("TeamAndPlaying11.txt","r");
    if(PNP == NULL)
    {
        printf("\n\"TeamAndPlaying11.txt\" file has an error\n");
        exit(1);
    }
    fscanf(PNP,"%s",team[0].name);
    printf("%s\n",team[0].name);
    fscanf(PNP,"%s",team[1].name);
    printf("%s\n",team[1].name);

    for(int i=0;i<2;i++)
    {
        for(int j=0;j<11;j++)
        {
            fscanf(PNP,"%s",team[i].batsman[j].playerName);
            //printf("%s\n",team[i].batsman[j].playerName);
        }
        for(int j=0;j<5;j++){
            fscanf(PNP,"%s",team[i].bowler[j].playerName);
            //printf("%s\n",team[i].bowler[j].playerName);
        }
    }
    fclose(PNP);
}

double CurrentRR(){
    team[B_team].CurrentRR=0.0;
    double over = (double) team[B_team].total_over[0] +(((double) team[B_team].total_over[1])/6);
    if(over!=0)
        team[B_team].CurrentRR =(double)team[B_team].total_runs/over;
    return team[B_team].CurrentRR;
}

double RequiredRR(){
    team[B_team].RequiredRR = INT_MAX;
    double over = (double)team[B_team].total_over[0] +(double) team[B_team].total_over[1]/6;
    double remainOver = (double) number_of_overs - over;
    if(remainOver!=0)
        team[B_team].RequiredRR = ((double)target - ((double)team[B_team].total_runs))/remainOver;

    return team[B_team].RequiredRR;

}

double StrikeRate(){
    for(int i=0;i<11;i++){
        if(team[B_team].batsman[i].played_ball > 0)
        team[B_team].batsman[i].strikeRate =((double)team[B_team].batsman[i].runsScored)/team[B_team].batsman[i].played_ball;
    }

}



void ScoreUpdate()
{
    FILE *WS;
     WS = fopen("ScoreFile.txt","w");
    if(WS == NULL)
    {
        printf("Error occur ...\nCan't open ScoreFile.txt\n");
        exit(0);
    }
    B_team = 0;
    F_team = 1;
    printf("\n%s is going to bat now....\n\n",team[B_team].name);
    DisplayScoreBoard();
    for(int i=0;i<number_of_overs;i++)
    {

            //team[B_team].total_over[0] = i;

            int temp;
            tO = 0;
            for(int j=1;j<=6;j++)
            {


                //printf("\nOver %d.%d \nEnter  the score : ",i,j);
                //scanf("%d",&temp);
                srand(time(0));
                temp = rand()%11;
                fprintf(WS,"Ball %d.%d : %d\t",i,j,temp);
                thisOver[tO] = temp;
                tO++;

                if(temp == 5)
                {
                    j--;
                    printf("\n\t\t....Wide....\n");
                    team[B_team].total_runs += 1;
                    team[F_team].bowler[bow].runsLossed += 1;

                    //temp = 1;
                    //team[B_team].batsman[k].runsScored -= temp;
                }
                else if(temp == 7)
                {
                      printf("\n\t\t....NO ball....\n\t\tFREE HIT !!!\n");
                      j--;
                      team[B_team].total_runs += 1;
                      team[F_team].bowler[bow].runsLossed += 1;


                      int extra = rand()%7 ;
                      fprintf(WS,"extra : %d\t",extra);
                      if (extra != 5)
                      {
                             //temp=6;
                            team[B_team].total_runs += extra;
                            team[F_team].bowler[bow].runsLossed += extra;
                            team[B_team].batsman[strk].runsScored += extra;


                      }
                      team[B_team].batsman[strk].played_ball++;
                      if(extra ==1 || extra ==3)
                      {
                            if(strk == Striker1)
                            {
                                strk = Striker2;
                            }
                            else
                            {
                                strk = Striker1;
                            }
                      }

                }
                else if(temp == 8)
                {
                    temp = rand()%4 + 1;
                    fprintf(WS,"By : %d\t",temp);
                    team[B_team].total_runs += temp;
                    team[F_team].bowler[bow].runsLossed += temp;
                    //team[B_team].batsman[strk].runsScored += temp;
                    team[B_team].batsman[strk].played_ball++;
                }
                else if((temp == 9)&& (thisOver[tO-2]!=7))
                {
                      //printf("Player %d has been out :");
                      team[B_team].Num_Wicket++;
                      team[B_team].batsman[strk].played_ball++;
                      team[F_team].bowler[bow].wicket++;
                      int out = rand()%2 +1;
                      fprintf(WS,"out %d\t",out);
                      if(strk == Striker1)
                      {
                            Striker1 = Striker2;
                            Striker2++;
                      }
                      else
                        Striker2++;

                      if(out == 1)
                      {
                            printf("\t\t....Bold Out....\n");


                            strk = Striker2;
                      }
                      else if(out == 2)
                      {
                            printf("\n\t\t....Catch Out....\n");

                            int run_half = rand()%2;
                            if(run_half)
                            {
                                strk = Striker1;
                            }
                            else
                                strk = Striker2;
                      }

                      if(team[B_team].Num_Wicket==10)
                        break;

                }
                else if(temp ==10)
                {
                    printf("\n\t\t....Run out....\n");
                    team[B_team].batsman[strk].played_ball++;

                    team[B_team].Num_Wicket++;
                    int batting_end = rand()%2;
                    if(batting_end){
                        int r_out = rand()%3+1;
                        team[B_team].batsman[strk].runsScored += r_out-1;
                        team[B_team].total_runs += r_out-1;
                        team[F_team].bowler[bow].runsLossed +=r_out-1;
                        if(r_out == 1 || r_out==3){
                            if(strk == Striker1){
                                Striker2++;
                                strk = Striker2;
                            }
                            else{
                                Striker1 = Striker2;
                                Striker2++;
                                strk = Striker2;
                            }
                        }
                        else{
                            if(strk == Striker2){
                                Striker2++;
                                strk = Striker2;
                            }
                            else{
                                Striker1 = Striker2;
                                Striker2++;
                                strk = Striker2;
                            }
                        }
                    }
                    else{
                        int r_out = rand()%3+1;
                        team[B_team].batsman[strk].runsScored += r_out-1;
                        team[B_team].total_runs += r_out-1;
                        team[F_team].bowler[bow].runsLossed +=r_out-1;
                        if(r_out == 1 || r_out==3){
                            if(strk == Striker2){
                                Striker2++;
                                strk = Striker1;
                            }
                            else{
                                Striker1 = Striker2;
                                Striker2++;
                                strk = Striker1;
                            }
                        }
                        else{
                            if(strk == Striker1){
                                Striker2++;
                                strk = Striker1;
                            }
                            else{
                                Striker1 = Striker2;
                                Striker2++;
                                strk = Striker1;
                            }
                        }

                    }

                    if(team[B_team].Num_Wicket==10)
                        break;
                }
                else if(temp <= 6)
                {
                        if(temp == 6)
                        {
                            team[B_team].sixes++;
                        }
                        else if(temp == 4 )
                        {
                            team[B_team].fours++;
                        }


                        team[B_team].total_runs += temp;
                        team[B_team].batsman[strk].runsScored += temp;
                        team[F_team].bowler[bow].runsLossed += temp;
                        team[B_team].batsman[strk].played_ball++;

                }
                team[B_team].total_over[1] = j;
                team[F_team].bowler[bow].over[1]=j;
                DisplayScoreBoard();



                if( temp==1 || temp ==3 )
                {
                    if(strk == Striker1)
                    {
                        strk = Striker2;
                    }
                    else
                        strk = Striker1;
                }

                fprintf(WS,"\n");
                //printf("\nNext..");
                //getchar();

            }
            if(team[B_team].Num_Wicket==10)
                        break;
            if(strk == Striker1)
            {
                strk = Striker2;
            }
            else
            {
                strk = Striker1;
            }
            team[B_team].total_over[0]++;
            team[B_team].total_over[1] = 0;


            team[F_team].bowler[bow].over[0]++;
            team[F_team].bowler[bow].over[1]=0;
            bow++;
            if(bow==5){
                bow=0;
            }
    }
    StrikeRate();
    ScoreTable1();
    target = team[B_team].total_runs+1;
    //printf("\n%s set the target %d runs\n",team[B_team].name,team[B_team].total_runs+1);
    B_team = 1;
    F_team = 0;
    strk = 0;
    Striker1 = 0;
    Striker2 = 1;
    bow = 0;
    tO=0;
    printf("\n%s is going to bat now....\n\n",team[B_team].name);
    DisplayScoreBoard();
    for(int i=0;i<number_of_overs;i++)
    {

            //team[B_team].total_over[0] = i;
            srand(time(0));
            int temp;
            tO=0;
            for(int j=1;j<=6;j++)
            {

                //printf("\nOver %d.%d \nEnter  the score : ",i,j);
                //scanf("%d",&temp);
                temp = rand()%11;
                fprintf(WS,"Ball %d.%d : %d\t",i,j,temp);
                thisOver[tO]=temp;
                tO++;

                if(temp == 5)
                {
                    printf("\n\t\t....Wide....\n");
                    j--;
                    team[B_team].total_runs += 1;
                    team[F_team].bowler[bow].runsLossed += 1;

                    //temp = 1;
                    //team[B_team].batsman[k].runsScored -= temp;
                }
                else if(temp == 7)
                {
                      printf("\n\t\t....NO ball\n\t\tFREE HIT !!!!\n");
                      j--;
                      team[B_team].total_runs += 1;
                      team[F_team].bowler[bow].runsLossed += 1;


                      int extra = rand()%7 ;
                      fprintf(WS,"extra : %d\t",extra);
                      if (extra != 5)
                      {
                             //temp=6;
                            team[B_team].total_runs += extra;
                            team[F_team].bowler[bow].runsLossed += extra;
                            team[B_team].batsman[strk].runsScored += extra;


                      }
                      team[B_team].batsman[strk].played_ball++;
                      if(extra ==1 || extra ==3)
                      {
                            if(strk == Striker1)
                            {
                                strk = Striker2;
                            }
                            else{
                                strk = Striker1;
                            }
                      }

                }
                else if(temp == 8)
                {
                    int temp = rand()%4 + 1;
                    fprintf(WS,"By : %d\t",temp);
                    team[B_team].total_runs += temp;
                    team[F_team].bowler[bow].runsLossed += temp;
                    //team[B_team].batsman[strk].runsScored += temp;
                    team[B_team].batsman[strk].played_ball++;
                }
                else if((temp == 9)&& (thisOver[tO-2]!=7))
                {
                      //printf("Player %d has been out :");
                      team[B_team].Num_Wicket++;
                      team[B_team].batsman[strk].played_ball++;
                      team[F_team].bowler[bow].wicket++;
                      int out = rand()%2 +1;
                      fprintf(WS,"out %d\t",out);
                      if(strk == Striker1)
                      {
                            Striker1 = Striker2;
                            Striker2++;
                      }
                      else
                        Striker2++;

                      if(out == 1)
                      {
                            printf("\t\t....Bold Out....\n");
                            strk = Striker2;
                      }
                      else if(out == 2)
                      {
                            printf("\n\t\t....Catch Out....\n");

                            int run_half = rand()%2;
                            if(run_half){
                                strk = Striker1;
                            }
                            else
                                strk = Striker2;
                      }

                      if(team[B_team].Num_Wicket==10)
                        break;

                }
                else if(temp ==10)
                {
                    printf("\n\t\t....Run out....\n");
                    team[B_team].batsman[strk].played_ball++;

                    team[B_team].Num_Wicket++;
                    int batting_end = rand()%2;
                    if(batting_end){
                        int r_out = rand()%3+1;
                        team[B_team].batsman[strk].runsScored += r_out-1;
                        team[B_team].total_runs += r_out-1;
                        team[F_team].bowler[bow].runsLossed += r_out-1;
                        if(r_out == 1 || r_out==3){
                            if(strk == Striker1){
                                Striker2++;
                                strk = Striker2;
                            }
                            else{
                                Striker1 = Striker2;
                                Striker2++;
                                strk = Striker2;
                            }
                        }
                        else{
                            if(strk == Striker2){
                                Striker2++;
                                strk = Striker2;
                            }
                            else{
                                Striker1 = Striker2;
                                Striker2++;
                                strk = Striker2;
                            }
                        }
                    }
                    else{
                        int r_out = rand()%3+1;
                        team[B_team].batsman[strk].runsScored += r_out-1;
                        team[B_team].total_runs += r_out-1;
                        team[F_team].bowler[bow].runsLossed +=r_out-1;
                        if(r_out == 1 || r_out==3){
                            if(strk == Striker2){
                                Striker2++;
                                strk = Striker1;
                            }
                            else{
                                Striker1 = Striker2;
                                Striker2++;
                                strk = Striker1;
                            }
                        }
                        else{
                            if(strk == Striker1){
                                Striker2++;
                                strk = Striker1;
                            }
                            else{
                                Striker1 = Striker2;
                                Striker2++;
                                strk = Striker1;
                            }
                        }

                    }
                    if(team[B_team].Num_Wicket==10)
                        break;
                }
                else if(temp<=6){


                        if(temp == 6)
                        {
                            team[B_team].sixes++;
                        }
                        else if(temp == 4 )
                        {
                            team[B_team].fours++;
                        }


                        team[B_team].total_runs += temp;
                        team[B_team].batsman[strk].runsScored += temp;
                        team[F_team].bowler[bow].runsLossed += temp;
                        team[B_team].batsman[strk].played_ball++;

                }
                team[B_team].total_over[1] = j;
                team[F_team].bowler[bow].over[1]=j;
                DisplayScoreBoard();
                if(team[B_team].total_runs>team[F_team].total_runs)
                {
                    //printf("\n\n\t\t\t\t%s win the match....\n\n",team[B_team].name);
                    //cout<<"\n\n\t\t\t\t"<<team[1].name<<" has beaten "<<team[0].name<<"........!";
                    //check=0;
                    break;
                }


                if( temp==1 || temp ==3 ){
                    if(strk == Striker1){
                        strk = Striker2;
                    }
                    else{
                        strk = Striker1;
                    }

                }
                fprintf(WS,"\n");
                //printf("\nNext..");
                //getchar();

            }
             if((team[B_team].Num_Wicket==10) || (team[B_team].total_runs > team[F_team].total_runs))
            {
                break;
            }
            if(strk == Striker1){
                strk = Striker2;
            }
            else{
                strk = Striker1;
            }
            team[B_team].total_over[0]++;
            team[B_team].total_over[1] = 0;
            team[F_team].bowler[bow].over[0]++;
            team[F_team].bowler[bow].over[1]=0;
            bow++;
            if(bow==5){
                bow=0;
            }
    }

    //if((team[B_team].Num_Wicket==10) || (team[B_team].total_runs > team[F_team].total_runs)){
                    if(team[B_team].total_runs > team[F_team].total_runs){
                        printf("\n\n\t\tCongratulations...\n\t\t%s win the match by %d wicket...\n",team[B_team].name,(10-team[B_team].Num_Wicket));
                    }
                    else if(team[B_team].total_runs == team[F_team].total_runs){
                        printf("\n\n\t\t\t\tMATCH DRAWN....\n");
                    }
                    else{
                        printf("\n\n\t\tCongratulations...\n\t\t%s win the match by %d runs...\n",team[F_team].name,(team[F_team].total_runs-team[B_team].total_runs));

                    }
                    StrikeRate();
                    ScoreTable1();


            //}
    fclose(WS);
}

void DisplayScoreBoard(){
    printf("\n-------------------------------------------------------------------------------------\n");
    printf("%s vs  | %s | %d / %d |",team[F_team].name,team[B_team].name,team[B_team].total_runs,team[B_team].Num_Wicket);
    printf(" %d . %d  |",team[B_team].total_over[0],team[B_team].total_over[1]);
    printf("%s | %d  (%d.%d)  |",team[F_team].bowler[bow].playerName,team[F_team].bowler[bow].runsLossed,team[F_team].bowler[bow].over[0],team[F_team].bowler[bow].over[1]);
    if(B_team==1)
        printf("  %d |",target);
    printf("\n-------------------------------------------------------------------------------------\n");
    printf("%s \t|  %d  (%d)   | ",team[B_team].batsman[Striker1].playerName,team[B_team].batsman[Striker1].runsScored,team[B_team].batsman[Striker1].played_ball);
    printf("%s \t|  %d  (%d)   |",team[B_team].batsman[Striker2].playerName,team[B_team].batsman[Striker2].runsScored,team[B_team].batsman[Striker2].played_ball);
    for(int i=0;i<tO;i++){
        printf("%d ",thisOver[i]);
    }
    printf("| %.1lf |",CurrentRR());
    if(B_team==1)
        printf(" %.1lf |",RequiredRR());

    printf("\n-------------------------------------------------------------------------------------\n");

    printf("NEXT");
    Sleep(1000);
    //getchar();
}

int UpdateScore(){
    printf("\nEnter the number of over: ");
    scanf("%d",&number_of_overs);
    getTeamAndPlayerNames();
    ScoreUpdate();
    SummaryTable();
    return 0;
}


void ScoreTable1(){
    printf("\n\n\t\t %s\n",team[B_team].name);
    for(int i=0;i<11;i++){
        printf("%12s\t\t\t%d(%d)\t%lf\n",team[B_team].batsman[i].playerName,team[B_team].batsman[i].runsScored,team[B_team].batsman[i].played_ball,team[B_team].batsman[i].strikeRate);
    }
    printf("Total = %d / %d \t (%d.%d)\n",team[B_team].total_runs,team[B_team].Num_Wicket,team[B_team].total_over[0],team[B_team].total_over[1]);
    printf("\n\n\t\t %s\n",team[F_team].name);
    for(int i=0;i<5;i++){
        printf("%12s\t\t %d \t %d \t (%d.%d)\n",team[F_team].bowler[i].playerName,team[F_team].bowler[i].runsLossed,team[F_team].bowler[i].wicket, team[F_team].bowler[i].over[0],team[F_team].bowler[i].over[1]);

    }
    printf("\n\n");
}

void SummaryTable(){

    for(int i=0;i<11;i++){
        IndexArr[i]=i;
        IndexArrW[i]=i;
    }
    B_team = 1;
    F_team = 0;

    MergeSort(0,10);
    MergeSortByWicket(0,4);

    printf("\n\n\t\t %s\t %d/%d\t(%d.%d)\n",team[B_team].name,team[B_team].total_runs,team[B_team].Num_Wicket,team[B_team].total_over[0],team[B_team].total_over[1]);
    printf("\t\t===========================\n");
    for(int i=0;i<3;i++){
        printf("\n\t%12s\t %d(%d)\t",team[B_team].batsman[IndexArr[i]].playerName,team[B_team].batsman[IndexArr[i]].runsScored,team[B_team].batsman[IndexArr[i]].played_ball);
        if(team[F_team].bowler[IndexArrW[i]].over[0]!=0 || team[F_team].bowler[IndexArrW[i]].over[1]!=0){
            printf(" %12s\t %d/%d",team[F_team].bowler[IndexArrW[i]].playerName,team[F_team].bowler[IndexArrW[i]].runsLossed,team[F_team].bowler[IndexArrW[i]].wicket);
            printf("(%d.%d)",team[F_team].bowler[IndexArrW[i]].over[0],team[F_team].bowler[IndexArrW[i]].over[1]);
        }
    }
    printf("\n\t\t===========================\n");


     for(int i=0;i<11;i++){
        IndexArr[i]=i;
        IndexArrW[i]=i;
    }
    B_team = 0;
    F_team = 1;

    MergeSort(0,10);
    MergeSortByWicket(0,4);

    printf("\n\n\t\t %s\t %d/%d\t(%d.%d)\n",team[B_team].name,team[B_team].total_runs,team[B_team].Num_Wicket,team[B_team].total_over[0],team[B_team].total_over[1]);
    printf("\t\t===========================\n");
    for(int i=0;i<3;i++){
        printf("\n\t%12s\t %d(%d)\t",team[B_team].batsman[IndexArr[i]].playerName,team[B_team].batsman[IndexArr[i]].runsScored,team[B_team].batsman[IndexArr[i]].played_ball);
        if(team[F_team].bowler[IndexArrW[i]].over[0] !=0 || team[F_team].bowler[IndexArrW[i]].over[1]!= 0){
            printf(" %12s\t %d/%d",team[F_team].bowler[IndexArrW[i]].playerName,team[F_team].bowler[IndexArrW[i]].runsLossed,team[F_team].bowler[IndexArrW[i]].wicket);
            printf("(%d.%d)",team[F_team].bowler[IndexArrW[i]].over[0],team[F_team].bowler[IndexArrW[i]].over[1]);

        }
    }
    printf("\n\t\t===========================\n");

}

void MergeSort(int f,int l){
    if(f<l){
        int m = (f+l)/2;
        MergeSort(f,m);
        MergeSort(m+1,l);
        Merge(f,m,l);
    }
}

void Merge(int f,int m,int l){
    int i,j,k;
    int n1 = m-f+1;
    int n2 = l-m;
    int L[n1],R[n2];
    for(i=0;i<n1;i++){
        L[i] = IndexArr[f+i];
    }
    for(j=0;j<n2;j++){
        R[j] = IndexArr[m+j+1];
    }

    i=0;
    j=0;
    for(k=f;(k<=l) && (i<n1) && (j<n2);k++){
        //if(value[L[i]] <= value[R[j]]){
        if(team[B_team].batsman[L[i]].runsScored > team[B_team].batsman[R[j]].runsScored){
            IndexArr[k] = L[i];
            i++;
        }
        else if(team[B_team].batsman[L[i]].runsScored == team[B_team].batsman[R[j]].runsScored){
            if(team[B_team].batsman[L[i]].played_ball <= team[B_team].batsman[R[j]].played_ball){
                IndexArr[k] = L[i];
                i++;
            }
            else{
               IndexArr[k] = R[j];
               j++;
            }
        }
        else{
            IndexArr[k] = R[j];
            j++;
        }
    }
    if(i==n1){
        for( ;k<=l;k++){
            IndexArr[k] = R[j];
            j++;
        }
    }

    else if(j==n2){
       for( ;k<=l;k++){
            IndexArr[k] = L[i];
            i++;
        }
    }

}



void MergeSortByWicket(int f,int l){
     if(f<l){
        int m = (f+l)/2;
        MergeSortByWicket(f,m);
        MergeSortByWicket(m+1,l);
        MergeforWicket(f,m,l);
    }
}
void MergeforWicket(int f,int m,int l){
    int i,j,k;
    int n1 = m-f+1;
    int n2 = l-m;
    int L[n1],R[n2];
    for(i=0;i<n1;i++){
        L[i] = IndexArrW[f+i];
    }
    for(j=0;j<n2;j++){
        R[j] = IndexArrW[m+j+1];
    }

    i=0;
    j=0;
    for(k=f;(k<=l) && (i<n1) && (j<n2);k++){
        if(team[F_team].bowler[L[i]].wicket >
            team[F_team].bowler[R[j]].wicket){
            IndexArrW[k] = L[i];
            i++;
        }
        else if(team[F_team].bowler[L[i]].wicket == team[F_team].bowler[R[j]].wicket){
            if(team[F_team].bowler[L[i]].runsLossed <= team[F_team].bowler[R[j]].runsLossed){
                IndexArrW[k] = L[i];
                i++;
            }
            else{
               IndexArrW[k] = R[j];
               j++;
            }
        }
        else{
            IndexArrW[k] = R[j];
            j++;
        }
    }
    if(i==n1){
            for( ;k<=l;k++){
                IndexArr[k] = R[j];
                j++;
            }
    }

    else if(j==n2){
           for( ;k<=l;k++){
                IndexArrW[k] = L[i];
                i++;
            }
    }

}



#endif // ONGOINGMATCHSCORE_H_INCLUDED
