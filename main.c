
/*****************************************************************************
 * Copyright (C) Ankita V. Chavan ankitavchavan@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/


#include <crypt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include "project.h"

int main()
{
  	int ret;
  	char ch,c,c1;
        FILE *fp; 
        train_berth(); 
	   
        printf("\n\twelcome :");
	printf("\nEnter 1 for Log In : Enter 2 for Sign Up:");
	scanf("%c",&ch);
	if(ch == '2')
		Sign_Up();
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
                                //printmenu();

   			}
			printmenu();
                                                        
   			fclose(fp);
		  	
                  }                   
        	  
	}
	while(1) {
	printf("\nDo you want to continue or logout\nPress 1 to continue and 3 for logout\n");
	scanf(" %c", &c1);
	if((c1 == '3')) {
		 Logout(c1, &ret);
		 break;
		 exit (1);
		
			
	}
	else if(c1 == '1')
		printmenu();
	}
	return 0;

}
