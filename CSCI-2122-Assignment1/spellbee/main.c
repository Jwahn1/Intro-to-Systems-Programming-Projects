/*
Author:Javier Wahn 
B0:B00935618
Date:20/9/2023
Program:takes inputted words and outputs which ones are panagrams, the letters in the panagram
and how many words can be written with those letters which are contained in the dictionnary of the program
*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//input pattern is
//number of words to be inputed
//word with all capital letters(under 30 characters)
//repeat until all words are inputed


void count(char *word,int *alphabet);
int checkPanagram(int *alphabet);
int possibleCombinations(int *alphabet,int dictionnarySize,char dictionnary[][30]);

int main(int argc, char const *argv[])
{
    int wordAmount;
    int panagramSize=0;
    
    char word[30];
    scanf("%d",&wordAmount);
    int dictionnarySize = wordAmount;

    char dictionnary[20000][30]; //stores the word list
    memset(dictionnary,0,sizeof(dictionnary)); //zeroes out the word list

    char panagrams[20000][30];//stores the words that qualify as panagrams
    memset(panagrams,0,sizeof(panagrams));

    int alphabet[26];
    memset(alphabet,0, sizeof(alphabet)); // sets all values from alphabet[26] to equal 0 since in c ram is filled with trash

    for(int i =0; i<wordAmount;i++){
        scanf("%s",&word);//current word
        strcpy(dictionnary[i],word);//stores every word

        
        //word check process
        count(word,alphabet);//gets alphabet of current word
        int checkedWord =  checkPanagram(alphabet); //checks the generated alphabet to see if theres 7 letters with >1 value

        //if its a panagram lets store it
        if(checkedWord == 1){
            strcpy(panagrams[panagramSize],word);
            panagramSize+=1;//keeps track of how many panagrams are actually stored
        }

        memset(alphabet,0, sizeof(alphabet));

    }

    //after this point both arrays should be correctly filled
    for(int i =0; i<panagramSize;i++){
        strcpy(word,panagrams[i]);//current word will cycle through all panagrams
        
        //word check process
        count(word,alphabet);//gets alphabet of current word
        
        printf("%s : ",word);
        //printout of the alphabet
        for(int j = 0; j<26;j++){
            if(alphabet[j] >0){
                int letter = 65+j;//dereferences the ascii value based on the position of the array
                char converted = letter; //dereference
                printf("%c ",converted);//print char CHANGE INTO STRING APPEND
            }
        }

        //block here for the number of possible words writable with the panagram alphabet
        int wordCombos =  possibleCombinations(alphabet,dictionnarySize,dictionnary);
        printf("; %d\n",wordCombos);


        memset(alphabet,0, sizeof(alphabet));//clears alphabet for next panagram
    }   

    //we should try now to implement problem 3 now in the algorithm above 

    return 0;
}


//function keeps count of the letters in each word used and stores it in alphabet[]
 void count(char *word,int *alphabet){
    int i = 0;  //this will determine what letter is being measured
    for(int j = 0; j<strlen(word);j++){//goes through the entire letter
        bool done = true;
        while(done){
            if(word[j] == 65+i && i<26){ //if word is == to "A" or "the letter i letters after "A"/
                alphabet[i]+= 1; //adds 1 count to the corresponding letter
                done = false;
            }
            if(i == 26){ // in case the character inputed is NOT a-z then it will time out here
                done = false;
            }
        i++;
        } 
    i = 0;//after the letter is found it resets the i back to the letter "a"
   }
}

//function checks whether an inputed word is a panagram via checking the related alphabet[] array
int checkPanagram(int *alphabet){
    int unique = 0;
    for(int i = 0; i<26;i++){ //alphabet is 26 elements wide
        if(alphabet[i] >0){
            unique +=1; //each time alphabet[i] => 1 that letter is in the current word
        }
    }
    if(unique == 7){ // if only 7 array elements were above or equal to 1
        return 1; //its a panagram
    }
    return 0;
}

//functions checks how many words in dictionnary[] can be written with the alphabet of the current panagram
int possibleCombinations(int *alphabet,int dictionnarySize,char dictionnary[][30]){
    //return variable
    int combinationCounter =0;
    int counter = 0;//for alphabet comparison
    int sizeAlphabet = 0; //if the number of letters in otherAlhabet ==  counter, then its a possible combination


    //alphabet initalized for current word in dictionnary[i]
    int otherAlphabet[26];
    memset(otherAlphabet,0,sizeof(otherAlphabet));

    for(int i =0; i<dictionnarySize;i++){//will stop loop before it exceeds slots with actual strings in them
        count(dictionnary[i],otherAlphabet);//gets alphabet of current dictionnary word
        
        //block compares current dictionnary[i] word to panagra
        for(int j = 0; j<26 ;j++){
            //now both alphabets are ready, we can compare them
            if(otherAlphabet[j] > 0){
                sizeAlphabet+=1;
             }
             if(otherAlphabet[j]>0 && alphabet[j]>0){
                 counter+=1;
             }
        }
        if(sizeAlphabet == counter){
            combinationCounter+=1;
        }
        
        //prepare alphabet and variables for next word
        memset(otherAlphabet,0,sizeof(otherAlphabet));
        counter=0;
        sizeAlphabet=0;
    }
    return combinationCounter;
}
