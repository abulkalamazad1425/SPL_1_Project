#ifndef REGRESSIONPREDICTOR_H_INCLUDED
#define REGRESSIONPREDICTOR_H_INCLUDED
#include<bits/stdc++.h>
using namespace std;

void calculateSums_Means(double x[],double y[]);
void calculate_m_c(double x[],double y[]);
double FittedValue(double xi);
double calculate_R_Square(double x[],double y[]);

int n;
double m, c;
double x_mean, y_mean;
double sumXY, sumX, sumY, sumX_square, sumY_square, Syy, SSR;

void calculate_m_c(double x[],double y[])
{

    calculateSums_Means(x,y);

    m = sumXY - (n * x_mean * y_mean);
    m/= sumX_square - ( n * x_mean* x_mean);
    c = y_mean - m*x_mean;
}


void calculateSums_Means(double x[],double y[])
{

    for(int i=0; i<n; i++)
    {
        sumX += x[i];
        sumY += y[i];
        sumXY += x[i]*y[i];
        sumX_square += x[i]*x[i];
        sumY_square += y[i]*y[i];
    }
    x_mean= sumX/ n;
    y_mean= sumY/n;
}

double FittedValue(double xi)
{
    double yi= c + (m * xi);
    return yi;
}


double calculate_R_Square(double x[],double y[]){
    double R_sq;

    Syy= 0, SSR=0;
    calculate_m_c(x,y);
    for(int i=0; i<n; i++)
    {
        Syy += (y[i]- y_mean) * (y[i]- y_mean);
        double pred= FittedValue(x[i]);
        SSR += (y[i]- pred)* (y[i]- pred);
    }

    R_sq = 1- (SSR/ Syy);
    return R_sq;
}
int predictByRegression(){
    double DataSet[6][1000];
    FILE *fp=fopen("Regression.txt","r");

    double maxR_sq=0.0;
    double predictedScore;
    double team1Score;
    cout<<"\n\n\tWinner prediction by Linear Regression\n";
    cout<<"\t=======================================\n\n";
    cout<<"Enter the team1 score : ";
    cin >>team1Score;

    n=0;
    int Col_max_Rsq=-1;
    for(int i=0;!feof(fp);i++){
        fscanf(fp,"%lf %lf %lf %lf %lf %lf",&DataSet[0][i],&DataSet[1][i],&DataSet[2][i],&DataSet[3][i],&DataSet[4][i],&DataSet[5][i]);
        n++;
    }
    for(int i=0;i<5;i=i+2){
        double R_sq = calculate_R_Square(DataSet[i],DataSet[i+1]);
        cout << R_sq <<" ";
        if(R_sq> maxR_sq){
            maxR_sq = R_sq;
            cout <<m<<"m c"<<c<<endl;

            Col_max_Rsq = i;
            predictedScore = FittedValue(team1Score);
        }
    }
    cout << predictedScore<<endl;

    if(predictedScore > team1Score){
        cout<<"\n\nPredicted Winner : team-2\n\n";
    }
    else if(predictedScore == team1Score){
        cout<<"\n\nMatch Draw\n\n";
    }
    else{
       cout<<"\n\nPredicted Winner : team-1\n\n";
    }

    cout << "Here the dependency between team-1 and team-2 score is: "<<maxR_sq*100<<"%"<<endl<<endl<<endl;
    return 0;

}



#endif // REGRESSIONPREDICTOR_H_INCLUDED
