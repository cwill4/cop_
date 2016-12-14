/*
Christopher Cefalu
COP 3223, Section 3
Project #8, charityrun.c
December 2nd, 2016

The following portions of this assignment have been implemented:
- Processing Individual Registrations
- Processing Team Registrations
- Processing run events
- Calculating total donations
*/


/* Included libraries*/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

/*Constants*/

#define TEAMS 200
#define RUNNERS 10000
#define LENGTH 20
#define TEAMSIZE 50

/*Structures*/

struct person {
    char name[LENGTH];
    int number;
    int age;
    int event;
    float money;
    float time;
};

struct team {
    char name[LENGTH];
    int nummembers;
    float money;
    struct person members[TEAMSIZE];
};

struct members {
    char name[LENGTH];
    int number;
    int age;
    int event;
    float money;
    float time;
};

/* Function prototypes */

void determineWinner5k (char [], float, char[], float);
void determineWinner10k (char [], float, char[], float);
void calculateTotal (float registration, float teams, float individuals);



int main () {

    /* Variable declarations and initializations.*/

    int i, j, k, t, header_1, header_2, header_3, runner_id;
    int runner_count = 1, team_count = 1, counter = 1;
    float early_registrants = 0, regular_registrants = 0, team_registrants = 0;
    float runner_time, fastest_time_5 = 5000, fastest_time_10 = 5000, fastest_time_42 = 5000, fastest_time_5_team = 5000, fastest_time_10_team = 5000, fastest_time_42_team = 5000;
    char winner_5[LENGTH], winner_10[LENGTH], winner_42[LENGTH];
    char winner_5_team[LENGTH], winner_10_team[LENGTH], winner_42_team[LENGTH];
    char file_name [30], name[LENGTH], team_name[LENGTH], label[5];
    char test_INDV [5], test_TEAM[5];
    float early_registration_cost, regular_registration_cost, team_registration_cost, total_money_from_registration, total_raised_from_teams, total_raised_from_indv_donations, total_team_money[TEAMS];
    float max, max_2, max_3;
    int location, location_2, location_3, start_age, end_age, qualifying_time;

    struct person runner[RUNNERS];
    struct team running_team[TEAMS];

    /* Used to compare data when being read from a file, to allow for data to be assigned to either an individual or team. */

    strcpy(test_INDV, "INDV");
    strcpy(test_TEAM, "TEAM");

    printf("What is the name of the file that you would like to open?\n");
    scanf("%s", &file_name);

    FILE * ifp;
    ifp = fopen(file_name, "r");

    /* Checks to ensure that a valid file is opened.*/

    while (ifp == NULL) {
        printf("Please enter the name of the file.\n");
        scanf("%s", &file_name);
        ifp = fopen (file_name, "r");
    }

    /*Scans in the registration costs, as well as the first header*/

    fscanf(ifp,"%f",&early_registration_cost);
    fscanf(ifp,"%f",&regular_registration_cost);
    fscanf(ifp,"%f",&team_registration_cost);
    fscanf(ifp, "%d", &header_1);

    /* Scans first label. Label is then compared to two previously defined strings (INDV, TEAM) to determine whether this
       data is for an individual or a member of a team. The data is then read in and assigned. */

    for(i=1; i<header_1+1; i++) {
        fscanf(ifp,"%s", &label);
            if (strcmp(test_INDV, label) == 0) {
                fscanf(ifp,"%s", name);
                runner[runner_count].number = runner_count;
                strcpy(runner[runner_count].name, name);
                fscanf(ifp, "%d", &runner[runner_count].age);
                fscanf(ifp, "%d", &runner[runner_count].event);
                fscanf(ifp, "%f", &runner[runner_count].money);

                if (runner[runner_count].event == 42)
                    printf("%s registered for the marathon race! They have been assigned the number %d.", runner[runner_count].name, runner[runner_count].number);
                else
                    printf("%s registered for the %dk race! They have been assigned the number %d.", runner[runner_count].name, runner[runner_count].event, runner[runner_count].number);
                /* The runner counter is incremented after every individual or team member is added. Registration type for each is also incremented to later determine cost.*/
                runner_count++;
                early_registrants++;
            }

            if (strcmp(test_TEAM, label) == 0) {
                fscanf(ifp, "%s", team_name);
                running_team[team_count].nummembers = team_count;
                strcpy(running_team[team_count].name, team_name);
                fscanf(ifp, "%d", &header_2);
                printf("\n%s team registered for the event. They have %d members:\n", running_team[team_count].name, header_2);
                    for(j=1; j<header_2 + 1; j++) {
                        fscanf(ifp,"%s", name);
                        running_team[team_count].members[j].number = runner_count;
                        strcpy(running_team[team_count].members[j].name, name);
                        fscanf(ifp, "%d", &running_team[team_count].members[j].age);
                        fscanf(ifp, "%d", &running_team[team_count].members[j].event);
                        fscanf(ifp, "%f", &running_team[team_count].members[j].money);

                        if (running_team[team_count].members[j].event == 42)
                            printf("%s registered for the marathon race! They have been assigned the number %d.\n", running_team[team_count].members[j].name, running_team[team_count].members[j].number);
                        else
                            printf("%s registered for the %dk race! They have been assigned the number %d.\n", running_team[team_count].members[j].name, running_team[team_count].members[j].event, running_team[team_count].members[j].number);

                        runner_count++;
                        team_registrants++;
                    }
                team_count++;
              }
            printf("\n");
     }


    fscanf(ifp, "%d", &header_3);
    for (i=1; i<header_3 + 1; i++) {
         fscanf(ifp,"%s", name);
                runner[runner_count].number = runner_count;
                strcpy(runner[runner_count].name, name);
                fscanf(ifp, "%d", &runner[runner_count].age);
                fscanf(ifp, "%d", &runner[runner_count].event);
                fscanf(ifp, "%f", &runner[runner_count].money);

                if (runner[runner_count].event == 42)
                   printf("%s registered for the marathon race! They have been assigned the number %d.\n", runner[runner_count].name, runner[runner_count].number);
                else
                printf("%s registered for the %dk race! They have been assigned the number %d.\n", runner[runner_count].name, runner[runner_count].event, runner[runner_count].number);

                runner_count++;
                regular_registrants++;
    }

    /* Scanning in the running times, and then assigning them to each runner.*/

    for (i=1; i < runner_count; i++) {
        fscanf(ifp, "%d", &runner_id);
        fscanf(ifp, "%f", &runner_time);

        if (runner[i].number == runner_id) {
            runner[i].time = runner_time;
            continue;
        }

        else
            for (j=1; j<TEAMS + 1; j++)
                for (k=1; k<TEAMSIZE; k++)
                    if  (running_team[j].members[k].number == runner_id)
                        running_team[j].members[k].time = runner_time;
                        continue;
    }

    /* Two loops are run to find out which individuals were the fastest in the 5k for team members and individuals.
       The determineWinner5k function is then called to evaluate the data and make a final determination on the winner.*/

    for (i=1; i<runner_count + 1; i++) {
        if (runner[i].event == 0)
            continue;
        if (runner[i].event == 5)
            if (runner[i].time < fastest_time_5) {
                fastest_time_5 = runner[i].time;
                strcpy(winner_5, runner[i].name);
            }
    }

    for (i=1; i<runner_count+1; i++)
        for (j=0; j<TEAMS; j++)
            for (k=0; k<TEAMSIZE; k++)
                if (running_team[j].members[k].event == 5)
                    if (running_team[j].members[k].time < fastest_time_5_team) {
                        fastest_time_5_team = running_team[j].members[k].time;
                        strcpy(winner_5_team, running_team[j].members[k].name);
                    }

    determineWinner5k (winner_5, fastest_time_5, winner_5_team, fastest_time_5_team);

    /* This section runs two for loops - one for the individuals, and one for the team members.
       It will determine the fastest runner in each group.
       Then, the determineWinner10k function is called to compare each person and declare a winner. */

    for (i=1; i<runner_count + 1; i++) {
        if (runner[i].event == 0)
            continue;
        if (runner[i].event == 10)
            if (runner[i].time < fastest_time_10) {
                fastest_time_10 = runner[i].time;
                strcpy(winner_10, runner[i].name);
            }
    }

    for (i=1; i<runner_count+1; i++)
        for (j=0; j<TEAMS; j++)
            for (k=0; k<TEAMSIZE; k++)
                if (running_team[j].members[k].event == 10)
                    if (running_team[j].members[k].time < fastest_time_10_team) {
                        fastest_time_10_team = running_team[j].members[k].time;
                        strcpy(winner_10_team, running_team[j].members[k].name);
                    }

    determineWinner10k (winner_10, fastest_time_10, winner_10_team, fastest_time_10_team);


    /* This loop scans in the age ranges and qualifying time for the marathon. With each iteration,
       it cycles through the runners and team runners to determine who qualifies.*/

    for (i=0; i<9; i++) {

        fscanf(ifp, "%d", &start_age);
        fscanf(ifp, "%d", &end_age);
        fscanf(ifp, "%d", &qualifying_time);

        for (t=1;t<runner_count+1; t++)
            if (runner[t].event == 42)
                if (runner[t].age >= start_age)
                    if (runner[t].age <= end_age)
                        if (runner[t].time < qualifying_time)
                            printf("%s qualified in the marathon run with a time of %.1f minutes!\n", runner[t].name, runner[t].time);

        for (j=1; j<TEAMS; j++)
            for (k=1; k<TEAMSIZE; k++)
                if (running_team[j].members[k].event == 42)
                    if (running_team[j].members[k].age >= start_age)
                        if (running_team[j].members[k].age <= end_age)
                            if (running_team[j].members[k].time < qualifying_time)
                                printf("%s qualified in the marathon run with a time of %.1f minutes!\n", running_team[j].members[k].name, running_team[j].members[k].time);
    }


    /*Finds which team raised the most money. A new array is initialized to store the
      donation totals for each team. A nested loop is then used to load the total donations
      from each team into the array. The final loop finds which team donated the most money,
      and then the information is printed to the screen.*/

    for (i=0;i<TEAMS;i++)
        total_team_money[i] = 0;


    for (j=1; j<TEAMS; j++)
        for (k=1; k<TEAMSIZE; k++)
            total_team_money[j] += running_team[j].members[k].money;

    for (i=1; i<TEAMS; i++)
        if (total_team_money[i] > max) {
            max = total_team_money[i];
            location = i;
        }

    printf("\nThe %s team raised the most money with a team donation of $%.2f!\n", running_team[location].name, max);

    /* This loop evaluates all team members and prints out the person that raised the most money on each team.*/

   for (i=1; i<TEAMS+1; i++) {
        for (j=1; j<TEAMSIZE+1; j++)
            if (running_team[i].members[j].money > max_2) {
                max_2 = running_team[i].members[j].money;
                location_2 = j;
            }
        printf("%s raised the most money on team %s with a donation of $%.2f!\n", running_team[i].members[location_2].name, running_team[i].name, max_2);
        max_2 = 0;
        if (running_team[i+1].nummembers == 0)
            break;
    }

    /* Finds the individual runner that made the largest donation, then prints the name and the amount to the screen.*/

    for (i=1; i<runner_count + 1; i++) {
        if (runner[i].money > max_3) {
            max_3 = runner[i].money;
            location_3 = i;
        }
        if (runner[i+1].name == NULL)
            break;
    }

    printf("%s raised $%.2f!\n", runner[location_3].name, max_3);

    /* Calculating total raised from individual donations. */

    for (i=1; i<runner_count+1; i++) {
        if (runner[i].money > 0)
            total_raised_from_indv_donations += runner[i].money;
    }

    /* Calculating total raised from team donations.*/

    for (i=1;i<TEAMS;i++) {
        if (total_team_money[i] > 0)
            total_raised_from_teams += total_team_money[i];
    }

    /* Calculates the total amount of money generated from registrations, and then calls the calculateTotal function to give a final amount for all money raised.*/

    total_money_from_registration = (early_registrants*early_registration_cost) + (regular_registrants*regular_registration_cost) + (team_registrants*team_registration_cost);

    calculateTotal(total_money_from_registration, total_raised_from_teams, total_raised_from_indv_donations);

    return 0;

}


/*This function takes in a string, float, string, and a final float. The values represent the names and times of the fastest
  individuals in the 5k race from the individuals and teams. This function determines the winner of the 5k race based on those values.*/
void determineWinner5k (char winner_5[], float fastest_time_5, char winner_5_team[], float fastest_time_5_team) {

    if (winner_5 < winner_5_team)
        printf("\n\n5k race: %s had the fastest time with %.1f minutes!\n", winner_5, fastest_time_5);
    else if (winner_5_team < winner_5)
        printf("\n\n5k race: %s had the fastest time with %.1f minutes!\n", winner_5_team, fastest_time_5_team);
    return;
}



/* This function takes in a string, float, string, and a float. These items are previously determined from the results of the 10k.
  This function will take in and evaluate these items to make a final determination on the winner of the 10k. */
void determineWinner10k (char winner_10[], float fastest_time_10, char winner_team_10[], float fastest_time_10_team) {

    if (fastest_time_10 < fastest_time_10_team)
        printf("10k race: %s had the fastest time with %.1f minutes!\n", winner_10, fastest_time_10);
    else if (fastest_time_10_team < fastest_time_10)
        printf("10k race: %s had the fastest time with %.1f minutes!\n", winner_team_10, fastest_time_10_team);
    return;
}

/* This function takes in three previously calculated float values, and then sums the floats to generate the total amount of money raised from the charity run.
   The function then prints the results to the screen. */
void calculateTotal (float registration, float teams, float individuals) {

    float total_raised;
    total_raised = (registration + teams+ individuals);
    printf("\nThe runners raised $%.2f for charity!\n", total_raised);
    return;
}







