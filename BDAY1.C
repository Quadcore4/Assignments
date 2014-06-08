#include<stdio.h>
#include<conio.h>
#define max_days 365
#define true 1
#define false 0

// To determine the probability of a day repeating more than once in each trial
float simulate(int num_people,int num_trial)
{
	int n=0,i;
	for(i=0;i<num_trial;i++)
		if(trial(num_people))
			n++;            // if the day repeats then increase the count
	return (float)n/num_trial;      // probability = no of times the day repeats/total trials
}

int trial(int num_people)
{
	int i,day,found,bday[max_days];
	for(i=0;i<max_days;i++)
		bday[i]=false;		// initially no day has come before.
	for(i=0;i<num_people;i++)
	{
		day=rand()%365;         // a day generated randomly
		if(bday[day]==true)     // if the day has come before then n will increase
			return true;
		if(bday[day]==false)    // if the day didnt come before
			bday[day]=true; // then mark that day true
	}
	return 0;
}

int main()
{
	int i,j,num_trial,num_people;
	float avg,prob;
	FILE *fp;
	clrscr();
	fp=fopen("BdayParadox.txt","w");
	fprintf(fp,"The birthday problem is to find the probability that, in a group of N people, there is at least one pair of people who have the same birthday.\nFor simplicity, disregard variations in the distribution, such as leap years, twins, seasonal or weekday variations, and assume that the 365 possible birthdays are equally likely.\nTherefore probability of a given birthday for a person chosen from the entire population at random is 1/365.\n\n");

	for(j=0;j<2;j++)
	{
		avg=prob=0.0;
		printf("Enter the no of trials and no of people: ");
		scanf("%d %d",&num_trial,&num_people);

		fprintf(fp,"No of Trials = %d\nNo of people = %d\n\n",num_trial,num_people);
		fprintf(fp,"Probability at each trial for %d no of people\n",num_people);
		fprintf(fp,"Trial No.\tProbability\n\n");

		// to calculate the average of all the probabilities for a certain no of people
		for(i=1;i<=num_trial;i++)
		{
			prob=simulate(num_people,i);   // prob gives probability of 1 trial
			fprintf(fp,"%d\t%.4f\n",i,prob);
			avg=avg+prob;
		}

		avg=avg/(float)num_trial;
		fprintf(fp,"Average of all probabilities for %d no of people = %.4f\n\n",num_people,avg);
	}

	// to show the pattern of probability depending on no. of people
	fprintf(fp,"Result for 100 trials each\n\n");
	fprintf(fp,"No of people\tProbability\n\n");
	for(i=5;i<=80;i=i+5)          // no. of people from 5 to 80
		fprintf(fp,"%d\t\t%.4f\n",i,simulate(i,100));
	fprintf(fp,"\nHence we see that the probability increases as the no of people increases.\nAt 23 it becomes 50% and after 57 it becomes constant i.e. 100%.\nThis proves that Birthday Paradox is indeed correct!\n");

	fclose(fp);
	getch();
	return 0;
}