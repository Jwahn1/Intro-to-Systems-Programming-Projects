#include <stdio.h>
#include <string.h>

int main(){
       	int listSize;
   	int amount;
	char *productName[30];
	float unitCost;
    	float totalSum = 0;
	float calculation = 0;	
			    
	scanf("%d",&listSize);

	for (int i = 0; i < listSize; i++){
		scanf("%d %s %f",&amount,&productName,&unitCost);
		calculation = amount*unitCost;
		totalSum+= calculation; 
	 	printf("%s : %.2f\n",productName,calculation);
	}	
	
	printf("Total : %.2f\n",totalSum);	
			    
	return 0;
}
