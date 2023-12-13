#ifndef PLAYERRANKING_H_INCLUDED
#define PLAYERRANKING_H_INCLUDED

#include<bits/stdc++.h>
#include<stdio.h>
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

typedef struct Boller{
    char name[20];
    double wickets;
    double innings;
    double economyRate;
    double batsmenDismissed;
    double bowlerDismissed;
    double rating;

}Boller;

typedef struct Batsmen{
    char name[20];
    double run;
    double innings;
    double sR;
    char opponent[20];
    double rating;
}Batsmen;

Boller bowler[100];
Batsmen batsman[100];
int num_batsman=0;
int num_bowler=0;



double computeBatsmanRating(Batsmen batter ){

    if(batter.opponent == "strong"){
        return (strong*batter.run * perRunRating + batter.innings * perInningsRating + strong * batter.sR * perStrikeRateRating);
    }
    else if(batter.opponent == "medium"){
        return (medium * batter.run * perRunRating + batter.innings * perInningsRating + medium * batter.sR * perStrikeRateRating);
    }
    else
        return (weak * batter.run * perRunRating + batter.innings * perInningsRating +weak * batter.sR * perStrikeRateRating);

}

double computeBowlerRating(Boller boler){
    double rating = perWicketRating * perBatsmanDismissed * boler.batsmenDismissed;
    rating += perWicketRating * perBowlerDismissed * boler.bowlerDismissed;
    rating *= IdealEconomy/boler.economyRate;
    rating += perInningsRating*boler.innings;
    return rating;
}

int ListOfPlayerRanking(){
    cout<<"come"<<endl;
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

    for(int i=1;i<num_batsman-1;i++){
        for(int j=num_batsman-1;j-i>=0;j--){
            if(batsman[j].rating > batsman[j-1].rating){
                Batsmen B = batsman[j-1];
                batsman[j-1] = batsman[j];
                batsman[j] = B;
            }

        }
    }
    cout<<"\t\tBtsman Rank List"<<endl;
    cout<<"\t\t================"<<endl;
    for(int i=0;i<num_batsman;i++){
        cout << i+1<<".  "<< batsman[i].name <<"\t  "<< batsman[i].run <<" \t "<< batsman[i].innings<< "\t "<<batsman[i].sR<<"\t "<<batsman[i].rating<<endl;
    }



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
    for(int i=1;i<num_bowler-1;i++){
        for(int j=num_bowler-1;j-i>=0;j--){
            if(bowler[j].rating > bowler[j-1].rating){
                Boller B = bowler[j-1];
                bowler[j-1] = bowler[j];
                bowler[j] = B;
            }

        }
    }
    cout<<"\n\n\n\t\tBowler Rank List"<<endl;
    cout<<"\t\t================"<<endl;
    for(int i=0;i<num_bowler;i++){
        cout << i+1<<".  "<< bowler[i].name <<"\t  "<< bowler[i].wickets <<" \t "<< bowler[i].innings<< "\t "<<bowler[i].economyRate<<" \t"<<bowler[i].batsmenDismissed;
        cout<<" \t "<<bowler[i].bowlerDismissed<<" \t "<<bowler[i].rating<<endl;
    }
    cout<<"\n\n\n\n";
    fclose(freP);

    return 1;

}


#endif // PLAYERRANKING_H_INCLUDED
