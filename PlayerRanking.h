#ifndef PLAYERRANKING_H_INCLUDED
#define PLAYERRANKING_H_INCLUDED
#include<bits/stdc++.h>
using namespace std;

#define perRunRating .5
#define perInningsRating .3
#define perStrikeRateRating .2
#define strong 1
#define medium .8
#define weak .5

#define perWicketRating  2.5
#define perBatsmanDismissed 2
#define perBowlerDismissed 1.5
#define IdealEconomy 5

typedef struct Player{
    char name[20];
    double run;
    double wickets;
    double innings;
    double sR;
    char opponent[20];
    double economyRate;
    double batsmenDismissed;
    double bowlerDismissed;
    double rating;

}Player;


double computeBatsmanRating(Player batter ){

    if(batter.opponent == "strong"){
        return (strong*batter.run * perRunRating + batter.innings * perInningsRating + strong * batter.sR * perStrikeRateRating);
    }
    else if(batter.opponent == "medium"){
        return (medium * batter.run * perRunRating + batter.innings * perInningsRating + medium * batter.sR * perStrikeRateRating);
    }
    else
        return (weak * batter.run * perRunRating + batter.innings * perInningsRating +weak * batter.sR * perStrikeRateRating);

}

double computeBowlerRating(Player boler){
    double rating = perWicketRating * perBatsmanDismissed * boler.batsmenDismissed;
    rating += perWicketRating * perBowlerDismissed * boler.bowlerDismissed;
    rating *= IdealEconomy/boler.economyRate;
    rating += perInningsRating*boler.innings;
    return rating;
}

void mergeS(Player player[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Player leftArr[n1];
    Player rightArr[n2];

    for (int i = 0; i < n1; i++)
        leftArr[i] = player[left + i];

    for (int j = 0; j < n2; j++)
        rightArr[j] = player[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i].rating >= rightArr[j].rating) {
            player[k] = leftArr[i];
            i++;
        } else {
            player[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        player[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        player[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSort(Player player[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(player, left, mid);
        mergeSort(player, mid + 1, right);

        mergeS(player, left, mid, right);
    }
}

int ListOfPlayerRanking(){
    Player bowler[100];
    Player batsman[100];
    int num_batsman=0;
    int num_bowler=0;

    FILE * freP = fopen("BatsmanRank.txt", "r");
    if(freP == 0){
        cout<< "Error"<<endl;
    }

    for(int i=0;1;i++){
        fscanf(freP,"%s",batsman[i].name) ;

        if( strcmp(batsman[i].name,"END")==0){
            break;
        }
        num_batsman++;
        fscanf(freP,"%lf",&batsman[i].run) ;

        fscanf(freP,"%lf",&batsman[i].innings) ;
        fscanf(freP,"%lf",&batsman[i].sR) ;
        fscanf(freP,"%s",batsman[i].opponent) ;

        batsman[i].rating = computeBatsmanRating(batsman[i]);

    }

    mergeSort(batsman,0,num_batsman-1);


    cout<<"\t\tBtsman Rank List"<<endl;
    cout<<"\t\t================"<<endl;
    cout<<"No:  Name \t Run\t Innings s/r\t Rating\n";
    cout<<"===============================================\n";

    for(int i=0;i<num_batsman;i++){
        cout << i+1<<".  "<< batsman[i].name <<"\t  "<< batsman[i].run <<" \t "<< batsman[i].innings<< "\t "<<batsman[i].sR<<"\t "<<batsman[i].rating<<endl;
    }
    cout<<"===============================================\n\n";



    for(int i=0;1;i++){
        fscanf(freP,"%s",bowler[i].name) ;

        if( strcmp(bowler[i].name,"END")==0){
            break;
        }
        num_bowler++;
        fscanf(freP,"%lf",&bowler[i].wickets) ;

        fscanf(freP,"%lf",&bowler[i].innings) ;
        fscanf(freP,"%lf",&bowler[i].economyRate) ;
        fscanf(freP,"%lf",&bowler[i].batsmenDismissed) ;
        fscanf(freP,"%lf",&bowler[i].bowlerDismissed) ;

        bowler[i].rating = computeBowlerRating(bowler[i]);



    }
    mergeSort(bowler,0,num_bowler-1);

    cout<<"\n\n\n\t\tBowler Rank List"<<endl;
    cout<<"\t\t================"<<endl;
    cout<<"No:  Name \t Wicket\t Innings e/r Btsmandis Bowler_dis Rating\n";
    cout<<"========================================================================\n";
    for(int i=0;i<num_bowler;i++){
        cout << i+1<<".  "<< bowler[i].name <<"\t  "<< bowler[i].wickets <<" \t "<< bowler[i].innings<< "\t "<<bowler[i].economyRate<<" \t"<<bowler[i].batsmenDismissed;
        cout<<" \t "<<bowler[i].bowlerDismissed<<" \t "<<bowler[i].rating<<endl;
    }
    cout<<"========================================================================\n";
    cout<<"\n\n\n\n";
    fclose(freP);


    return 1;

}


#endif // PLAYERRANKING_H_INCLUDED
