#include <crypt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include "project1.h"

int main()
{
  	int ch1,ret;
  	char ch,c;
        FILE *fp; 
        train_berth(); 
	//train_berth2();    
        printf("\n\twelcome :");
	printf("\nEnter 1 for Log In : Enter 2 for Sign Up:");
	scanf("%c",&ch);
	if(ch == '1') {
		ret = Log_In();
                if(ret == 1){  
                  	fp = fopen("tr.txt","r");
        		while(1) {
                        	c = fgetc(fp);
      				if( feof(fp) ) {
      
          				break;
      				}
                                                
                                           
                                printf("%c", c);
                                printmenu();
   			}
                                      
                                        
   			fclose(fp);
		  	
                  }                   
        	  
	}


}
