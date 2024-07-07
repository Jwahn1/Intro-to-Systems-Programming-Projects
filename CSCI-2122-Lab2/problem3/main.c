#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void count(char *word,int *alphabet);
void printLine(int *alphabet);

int main(){
	    int alphabet[26];
	        char word[30];
		    bool notDot = true; 
		        char *dot=".";

			    memset(alphabet,0, sizeof(alphabet)); 

			        while(notDot){
					 
					        scanf("%s",&word);
						       
						        count(word,alphabet);
							        notDot = strcmp(word,dot); 
								    }
				        
				        printLine(alphabet);
					    return 0;
}


 void count(char *word,int *alphabet){

	     int i = 0; 
	         for(int j = 0; j<strlen(word);j++){
			         bool done = true;
				         while(done){
						             if(word[j] == 97+i && i<26){ 
								                     alphabet[i]+= 1; 
										                     done = false;
												                 }
							     if(i == 26){
								done = false;
							     }
							             i++;
								             } 
					     i = 0;
						        }
 }


void printLine(int *alphabet){
	    for(int i = 0; i<26 ; i++){
		            if(alphabet[i] >0 ){
				              
				                int letter = 97+i;
						            char converted = letter; 
							                printf("%c : ",converted);
									            for(int j = 0; j<alphabet[i]; j++){
											                    printf("*");
													                }
										                printf("\n");
												        }
			        }
}
