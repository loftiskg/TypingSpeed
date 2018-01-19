#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>




/* returns a pointer to an array of shuffled integers 0-array_len-1 */
int *
shuffle_n_integers(int array_len)
{
  int *indicies = malloc(array_len * sizeof(int));
  int temp_values[array_len];
  int index_tracker[array_len];
  int i;
  
  for(i=0;i<array_len;i++){
    temp_values[i]=i;     // temporary ordered list
    index_tracker[i] = 1; // keeps track of what indicies have already been used
  }
  
  int j = 0;
  for(i=0;i<array_len;i++){
    j = rand() % (array_len - i);  // pick an index between 0 and array_len-i
    while(1) {
      if(index_tracker[j] == 0)    // see if the index has already been used
	j++;                       // if it has go to the next value in array
      else
	break;                     // break if found unused value
    }
    index_tracker[j] = 0;          // mark value as used
    indicies[i] = temp_values[j];  // set indicies[i] equal to the j_th value in temp_values
  }
  return indicies;
}



/*clears buffer*/
int
flush(void){
  int c;
  while((c = getchar()) != '\n' && c != EOF)
        ;
  return 0;
}





/* This application will time how fast you can type a random assortment of words.  A single word will appear,
   the user will have to type it as fast as possible and press enter.  Then another word will appear.  This 
   will repeat until the end of the test.  At the end,  the program will print how how long it took you to
   type all of the words collectively.*/

int
main(){
  srand(time(0));
  int num_words = 9;
  const char *words[]={"The","quick","brown","fox","jumps","over","the","lazy","dog"};

  printf("This is an application to test your typing speed.  Press enter to start\n");
  getchar();  /* Waits for user to press enter */


  int *rand_indicies = shuffle_n_integers(num_words);
  int i;
  char user_input[6];
  for(i = 0;i<num_words;i++){
    printf("Word #%d: %s ",i+1,words[rand_indicies[i]]);
    scanf("%6s",user_input); // chose 6 b/c the words that we are matching are no longer than 6 chars.
    flush();
    
    while((strncmp(words[rand_indicies[i]], user_input, strlen(words[rand_indicies[i]]))) != 0){
      printf("Incorrect, try again.\n");
      scanf("%6s",user_input);
      flush();
    }
  }

  return 0;
}

