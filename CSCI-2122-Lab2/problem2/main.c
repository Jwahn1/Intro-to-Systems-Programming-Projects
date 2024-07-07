#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main()
{
	char word[30];
	char stringPrevious[30];
	bool notDot = true;
	char *dot=".";

	while(notDot){

		scanf("%s",&word);//takes in new word

		if(strcmp(word,stringPrevious) && strcmp(word,".")){
			printf("%s\n",word);
		 }
	
		strcpy(stringPrevious,word); //copys new word into the previousWord slot
		notDot = strcmp(word,dot); // if the new word == '.' then the while loop is over
								       
	  }
	  return 0;
}

