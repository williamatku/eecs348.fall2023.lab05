#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// give programmer control of program compute boundaries via macros
#define MAX_PLAYS 50
#define MAX_TOUCHDOWNS MAX_PLAYS
#define MAX_FIELDGOALS MAX_PLAYS
#define MAX_SAFETIES MAX_PLAYS

/*
    Dev:            William A. Morris
    Created:        2023-10-12
    Last Modified:  2023-10-13

    KUID:           3057236
    Email:          morris.william@ku.edu
    Class:          EECS 348 
    Lab Section:    Thursdays @11am

    Description:    
        A simple (and probably unsafe) C Program to calculate possible play breakdowns of NFL Football scores.
*/
int main(int argc, char** argv) {
    // DEFINE point values for every play
    const int TD_POINTS = 6; 
    const int FG_POINTS = 3;
    const int SAFETY_POINTS = 2;
    const int TD2P_POINTS = 8;
    const int TDFG_POINTS = 7;

    // DEFINE max plays for each play to compute
    const int TD_MAX = MAX_TOUCHDOWNS;
    const int FG_MAX = MAX_FIELDGOALS;
    const int SAFETY_MAX = MAX_SAFETIES;
    const int TD2P_MAX = MAX_TOUCHDOWNS;
    const int TDFG_MAX = MAX_TOUCHDOWNS;

    // program should always be running on execution
    int running = 1;

    int dest_score;
    // if the user entered a score when calling the program...
    if (argc == 2) { 
        // retrieve score from args
        dest_score = atoi(argv[1]); 
    } else {
        // ask the user to enter a score after program begins execution
        printf("Enter a score: "); 
        // and save score
        scanf("%d",&dest_score);
    }

    // define buffer for user to input a second score to tabulate possibilities
    char buffer[10] = "not zero";

    // and print results
    printf("Listing all possibilities found w/ score: %d...\n", dest_score);

    // while the program is calculating results...
    while (running) {
        // run thru the entire range of each play 0 -> max
        for (int td2p = 0; td2p < TD2P_MAX; td2p++) {
        for (int tdfg = 0; tdfg < TDFG_MAX; tdfg++) {
        for (int td = 0; td < TD_MAX; td++) {
        for (int fg = 0; fg < FG_MAX; fg++) {
        for (int safety = 0; safety < SAFETY_MAX; safety++) {
            // and for every final score within programming-specified range...
            int score // calculate score
                = TD_POINTS*td 
                + FG_POINTS*fg 
                + SAFETY_POINTS*safety 
                + TD2P_POINTS*td2p 
                + TDFG_POINTS*tdfg;

            // and print out if score adds up to user's desired score
            if (score == dest_score)
                // print results
                printf("\t%d TD + 2p, %d TD + FG, %d TD, %d 3pt FG, %d Safety\n",
                    td2p, tdfg, td, fg, safety);
            
        }}}}}

        // after tabulation, prompt the user to continue or terminate the program
        printf("Input 0 or 1 to exit, or enter a score to generate results.\n");

        // keep running the program until the user exits
        scanf("%s",buffer); 

        // close the program on zero/one input
        if (!strcmp(buffer, "0") || !strcmp(buffer, "1")) running = 0;
        // or run again with new score
        else dest_score = atoi(buffer); 
    }

    // after the user exists the program, print friendly message
    printf("Goodbye :)\n");
    // and return with no errors
    return 0;
}