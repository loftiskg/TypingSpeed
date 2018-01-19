#include <stdio.h>
#include <string.h>
#include <stdlib.h>




/* returns a pointer to an array of shuffled integers 0-array_len-1 */
int *
shuffle_n_integers(int array_len)
{
  int *indicies = malloc(array_len * sizeof(int));

  int i;
  for(i=0;i<array_len;i++){
    indicies[i] = i;
    printf("%d\n",indicies[i]);
  }

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
  int num_words = 9;
  const char *words[num_words];
  words[0] = "The";
  words[1] = "quick";
  words[2] = "brown";
  words[3] = "fox";
  words[4] = "jumps";
  words[5] = "over";
  words[6] = "the";
  words[7] = "lazy";
  words[8] = "dog";
  shuffle_n_integers(8); 
  printf("This is an application to test your typing speed.  Press enter to start\n");
  getchar();  /* Waits for user to press enter */
  int rand_indicies[] = {0,1,2,3,4,5,6,7,8};
  int i;
  char user_input[6];
  for(i = 0;i<num_words;i++){
    printf("Word #%d: %s ",i+1,words[i]);
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

/*
char *
get_user_input()
{
  char input[6] = 0;
  int c;
  int i;
  for(i=0;i<max_input_size;i++){
    c = getchar();
    if(c == '\n')
      return input;
    input[i] = c;
  }
  return input;
    
}

*/
