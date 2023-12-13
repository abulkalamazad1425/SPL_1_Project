#ifndef MATCHSCHEDULE_H_INCLUDED
#define MATCHSCHEDULE_H_INCLUDED
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

struct match
{

    char team1[30],team2[30];
    char format[10];
    char venue[30];
    char date[20],time[20];

}match[1000];

void UpcomingMatch(){

    FILE *fp;
    int i=0,choice=1,j=0,count=0;
    char str[30];
    fp = fopen("schedule.txt","r");
    if(fp==NULL)
        {
        printf("Error to open file.");
        exit(1);
    }

    while(!feof(fp) && (i<1000))
        {
        fscanf(fp,"%s%s%s%s%s%s",match[i].team1,match[i].team2,match[i].format,match[i].date,match[i].time,match[i].venue);
        i++;
    }
    while(choice){
            printf("What do you want: \n");
            printf("1. List of All Matces.\n");
            printf("2. Search. \n");
            printf("3. Quit\n");
            printf("Enter your choice: ");
            scanf("%d",&choice);
            printf("\n");
            switch(choice)
            {
            case 1:
                    j=0;
                    while(j<i-1)
                    {
                        printf("%s vs %s\n%s\n%s\n%s\t%s\n\n\n",match[j].team1,match[j].team2,match[j].format,match[j].venue,match[j].date,match[j].time);
                        j++;

                    }
                    break;
            case 2:

                    printf("Enter the name of the team: ");
                    j=0;
                    scanf("%s",str);
                    while(j<i)
                        {
                        if((strcmp(match[j].team1,str)==0) || (strcmp(match[j].team2,str)==0))
                        {
                            printf("%s vs %s\n%s\n%s\n%s\t%s\n",match[j].team1,match[j].team2,match[j].format,match[j].venue,match[j].date,match[j].time);
                            count++;
                        }
                        j++;
                    }
                    if(count==0)
                    {
                        printf("Not include in this list.\n");
                    }
                    break;
            case 3:
                    choice = 0;
                    break;

        }
    }

    fclose(fp);
    return;
}


#endif // MATCHSCHEDULE_H_INCLUDED
