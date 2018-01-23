
/* Copyright © 2018 Kevin Loftis */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <assert.h>
#include <errno.h>



/*  This application will time how fast you can type a random assortment 
    of words.  A single word will appear, the user will have to type 
    it as fast as possible and press enter.Then another word will appear. 
    This will repeat until the end of the test.  At the end, 
    the program will print how how long it took you to
    type all of the words collectively.
*/


/*returns the current time in seconds*/
double
get_time_seconds(void) 
{
    struct timeval tv;
    double currtime = 0;

    if(gettimeofday( & tv, NULL) == 0){
        currtime = ((double) tv.tv_sec + (double) tv.tv_usec / 1000000);
    }
    else{
        fprintf(stderr, "ERROR: %s\n", strerror(errno));
        exit(0);
    }

    return currtime;
}

/* returns a pointer to an array of shuffled integers 0-array_len-1. 
   Uses Fisher-Yates shuffle to return the shuffled array. */
int *
shuffle_n_integers(int array_len) 
{
    int * indicies = malloc(array_len * sizeof(int));
    assert(indicies != NULL);
    int temp_values[array_len];
    int index_tracker[array_len];
    int i;

    for (i = 0; i < array_len; i++) {
        temp_values[i] = i;    // temporary ordered list
        index_tracker[i] = 1;  // tracks indicies used
    }

    int j = 0;
    for (i = 0; i < array_len; i++) {
        j = rand() % (array_len - i); // # betwenn 0 and array_len-i
        while (1) {
            if (index_tracker[j] == 0) // see if the index has already been used
                j++; // if it has go to the next value in array
            else
                break; // break if found unused value
        }

        index_tracker[j] = 0;          // mark value as used

        indicies[i] = temp_values[j];  // set indicies[i] equal 
                                       // to the j_th value in temp_values
    }
    return indicies;
}

/*clears buffer*/
int
flush(void) 
{
    int c = 0;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
    return 0;
}


int
main() 
{
    srand(time(0));
    int num_words = 9;
    const char * words[] = {
        "The",
        "quick",
        "brown",
        "fox",
        "jumps",
        "over",
        "the",
        "lazy",
        "dog"
    };
    double tic, toc = 0; //variables used to time the user
    int * rand_indicies = shuffle_n_integers(num_words); //used to index words
    char user_input[6]; // buffer to hold user input

    printf("This is an application to test your typing speed."  
            "Press enter to start\n");
    getchar(); /* Waits for user to press enter */

    tic = get_time_seconds();
    int i;
    for (i = 0; i < num_words; i++) {
        printf("Word #%d: %s ", i + 1, words[rand_indicies[i]]);
        scanf("%6[a-zA-z]", user_input); //char limit to 6 because max 
                                        // word length is less than 6
        flush(); 

        // checks if user input matches word[i] else prints incorrect and 
        // scans for now input.
        while ((strncmp(words[rand_indicies[i]], user_input, 
                strlen(words[rand_indicies[i]]))) != 0) {

            printf("Incorrect, try again.\n");
            printf("Word #%d: %s ", i + 1, words[rand_indicies[i]]);
            scanf("%6[a-zA-z]", user_input);
            flush();
        }
    }
    toc = get_time_seconds();
    free(rand_indicies);
    printf("It took you %lf seconds!\n", toc - tic);
    return 0;
}
