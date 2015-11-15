
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

#define _XOPEN_SOURCE
#define _GNU_SOURCE         
#include <crypt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "project.h"
int mktime1();
int chktime1(struct tm );
int mktime2();
int chktime2(struct tm);

int Log_In() {
	char username[BUFSIZ], *password; 
  	char buf[BUFSIZ];               
  	char *user_file, *pass_file;       
  	char filename[BUFSIZ];             
  	FILE *infile;                      
        int flag = 0;   
	strcpy(filename, "password_file.txt");
  	printf("Username: ");
  	scanf("%s", username);
  	password = getpass("Password: ");
  	if((infile = fopen(filename, "r")) == NULL) {

    		printf("\nFile error!\nAborting...\n");

  	} 
	else {
  		while (!feof(infile)) {
      			buf[0] = '\0';
      			fscanf(infile, "%s", buf);
     			if(strlen(buf) == 0) 
				continue;
     			user_file = buf;
      			pass_file = strchr(buf, ':');
      			pass_file[0] = '\0';
      			pass_file++;
      			if(strcmp(user_file, username) == 0) {
        			if(strcmp(crypt(password, pass_file), pass_file) == 0) {

          				printf("Correct password...\n");
                                        flag = 1;
					
                                 } 
				else {

          				printf("Invalid password!\n\n");
                                        flag=0;

        			}  
        		break;

      			}  
			else {
			printf("\nusername does not exit!!! Please Sign in\n");
			return 0;
			}
			    		
		} 

  	}  
  fclose(infile);
  return(flag);
  
} 

void Sign_Up() {
	char salt[2];                                     
 	const char *salt_chars = "abcdefghijklmnopqrstuvwxyz"  
                           "ABCDEFGHIJKLMNOPQRSTUVWXYZ"  
                           "0123456789";

  	char username[BUFSIZ], password1[BUFSIZ], password2[BUFSIZ], *buf;
  	char filename[BUFSIZ];                         
  	FILE *outfile;                                                          
  	/* Build salt */
  	srand(time(NULL));
  	salt[0] = salt_chars[rand() % 62];
  	salt[1] = salt_chars[rand() % 62];
  	
	strcpy(filename, "password_file.txt");

  	/* Get the username */
  	printf("Username: ");
  	scanf("%s", username);

  	do {

    		buf = getpass("Password: ");
    		sprintf(password1, "%s", buf);
    		buf = getpass("Enter Again: ");
    		sprintf(password2, "%s", buf);
    		if(strcmp(password1, password2) != 0)
      			printf("\nPasswords do not match!\nTry again.\n\n");

  	}while(strcmp(password1, password2) != 0);

  	/* Encrypt the password */
  	buf = crypt(password1, salt);
  	if((outfile = fopen(filename, "a+")) == NULL){

    		printf("\nFile error!");

  	} 
	else {
    		fprintf(outfile, "%s:%s\n", username, buf);

  	}  
  	
  	fclose(outfile);

}  

void printmenu() {
	int choice, rval = 0, flag = 0, c;
	
	printf("\n\tEnter 1 for reservation(solapur to pune) :\n\t2. reservation(pune to solapur)\n\t3.canellation\n\t4.enquiry\n\t5.Exit");
	printf("Choice : ");
	scanf("%d", &choice);
	switch(choice) {
		case 1:
			rval = mktime1();
			if(rval == 1) 
				book_ticket1(rval);
			else {
				printf("\nEnter 3 for urgent booking:\n");
				scanf("%d", &c);
				if(c == 3) 
					book_ticket1(c);
				else 
					printmenu();
			}
			break;
		case 2:
			flag = mktime2();
			if(flag == 1)
				book_ticket2(flag);
			else {
				printf("\nEnter 3 for urgent booking:\n");
				scanf("%d", &c);
				if(c == 3) 
					book_ticket2(c);
				else 
					printmenu();
			}
			break;
		case 3:
			cancel();
			break;
		case 4:
			enquiry();
			break;  
		case 5:
			exit(1);
		default:
			printf("Not a valid choice");
	}
}
int mktime1() {
	struct tm strtime;
	//time_t timeoftheday;
	int rval;
	strtime.tm_year = 2015-1900;
	strtime.tm_mon = 11;
	strtime.tm_mday = 17;
	strtime.tm_hour = 07;
	strtime.tm_min =00;
	strtime.tm_sec = 00;
	//timeoftheday = mktime(&strtime);
	rval = chktime1(strtime);
	return rval;
}
int chktime1(struct tm strtime) {
	int flag = 0;
	struct tm tm;
	time_t curtime;
	curtime = time(NULL);
	tm = *localtime(&curtime);
	if(((tm.tm_year)==(strtime.tm_year))&&((strtime.tm_mon<=tm.tm_mon+1))) {
	
		if((strtime.tm_mday>tm.tm_mday)) {
			flag = 1;
			//return flag;
		}
	  	else if(strtime.tm_mday==tm.tm_mday) {
			if(((strtime.tm_hour)-(tm.tm_hour))>=4) {
				flag = 1;
				//return flag;
			}
			else {
				flag = 0;
				//return flag;
			}
		}
	}
	return flag;
}
 

void train_berth() {
        FILE *fp, *tr;
        char d[8][3]={{"S1"},{"S2"},{"S3"},{"S4"},{"S5"},{"S6"},{"S7"},{"S8"}};
	train *p, *q;
	berth *s;
        int i=0,count=0;
	struct tm strtime, strtime2;
	time_t timeoftheday, timeoftheday2;
	strtime.tm_year = 2015-1900;
	strtime.tm_mon = 11;
	strtime.tm_mday = 17;
	strtime.tm_hour = 07;
	strtime.tm_min =00;
	strtime.tm_sec = 00;
	timeoftheday = mktime(&strtime);
	//printf("%s", ctime(&timeoftheday));
	p = (struct train *)malloc(sizeof(train));
	strcpy(p->train_no, "4156");
	strcpy(p->train_name, "Solapur_to_Pune");
	strtime2.tm_year = 2015-1900;
	strtime2.tm_mon = 11;
	strtime2.tm_mday = 17;
	strtime2.tm_hour = 11;
	strtime2.tm_min =00;
	strtime2.tm_sec = 00;
	timeoftheday2 = mktime(&strtime2);
	q = (struct train *)malloc(sizeof(train));
	strcpy(q->train_no, "4526");
	strcpy(q->train_name,  "Pune_to_Solapur");
	fp = fopen("tr.txt", "r");
	if(fp == NULL) {
		fp = fopen("tr.txt", "w");
		fprintf(fp, "%s\n%s\n%sis departure time\n", p->train_no, p->train_name, ctime(&timeoftheday));
		
		fprintf(fp, "%s\n%s\n%sis departure time\n" , q->train_no, q->train_name, ctime(&timeoftheday2));
		fclose(fp);
	}

        
	tr = fopen("Solapur_to_Pune.txt", "r");
	s = (struct berth *)malloc(sizeof(berth));
	strcpy(s->coano, d[0]);
	strcpy(s->status, "V");
	if(tr == NULL) {
		tr = fopen("Solapur_to_Pune.txt", "w");
		for(i=1;i<=73;i++) {
		   	if(i>72) {
				count++;
				strcpy(s->coano, d[count]);
				i=1;
		   	}
			if(count == 8)
				break;
			s->seat_no = i;
			fprintf(tr,"%d%s-%s\n",s->seat_no,s->coano,s->status);

	    	}
	}
	fclose(tr);
	
	tr = fopen("Pune_to_Solapur.txt", "r");
	s = (struct berth *)malloc(sizeof(berth));
	strcpy(s->coano, d[0]);
	strcpy(s->status, "V");
	if(tr == NULL) {
		tr = fopen("Pune_to_Solapur.txt", "w");
		count = 0;
		for(i=1;i<=73;i++) {
		   	if(i>72) {
				count++;
				strcpy(s->coano, d[count]);
				i=1;
		   	}
			if(count == 8)
				break;
			s->seat_no = i;
			fprintf(tr,"%d%s-%s\n",s->seat_no,s->coano,s->status);

	    	}
	}
	fclose(tr);


}
int book_ticket1(int choice) {
	//char username[BUFSIZ]; 
  	char buf[BUFSIZ];               
  	char *user_file, *pass_file;       
  	char filename[BUFSIZ]; 
	FILE *fp1,*fp;
   	int len,id=10,flag;
   	char ch1;
	info *a;
   	a = (info*)malloc(sizeof(info));
   	fp1 = fopen("Solapur_to_Pune.txt", "r+");
	if(fp1 == NULL) {
		printf("\nFile error!\nAborting...\n");

  	} 
	else {
		while (!feof(fp1)) {
      			buf[0] = '\0';
      			fscanf(fp1, "%s", buf);
     			if(strlen(buf) == 0) 
				continue;
     			user_file = buf;
      			pass_file = strchr(buf, '-');
      			pass_file[0] = '\0';
      			pass_file++;
      			if(strcmp(pass_file, "V") == 0) {
        			flag=0;
				ch1 = 'O';
				fseek(fp1,-1,SEEK_CUR);  
       				fwrite(&ch1,1,1,fp1);
				//printf("\n%s",user_file);
				break;
					
                         } 
		}
			
	}
	
	fclose(fp1);
	if(choice == 1)
		strcpy(filename, "Solapur_to_Punebooking.txt");
	else if(choice == 3)
		strcpy(filename, "Solapur_to_Punebooking1.txt");
   	fp = fopen(filename, "r");
   	fseek(fp,0,SEEK_END);
   	len = ftell(fp);
   	//printf("len = %d",len);
   	fclose(fp);
	if(flag == 0) {
   		fp = fopen(filename, "a+");
   		if(len == 0) {
			printf("\nfirstname:");
    			scanf("%s",a->fname);
    			printf("\nlastname:");
    			scanf("%s",a->lname);
    			printf("\nage:");
    			scanf("%d",&a->age);
    			a->tid = id;
			printf("\n %s is your berthno and %d is your id:\n", user_file, id);
    			fprintf(fp,"%s%s%d#%s:%d\n",a->fname,a->lname,a->age,user_file,a->tid);
   		}
   		else {
    			fseek(fp,-3,SEEK_END);
    			fscanf(fp,"%d",&a->tid);
    			id = a->tid;
    			id++;
    			printf("\nfirstname:");
    			scanf("%s",a->fname);
    			printf("\nlastname:");
    			scanf("%s",a->lname);
    			printf("\nage:");
    			scanf("%d",&a->age);
    			printf("\n %s is your berthno and %d is your id:\n", user_file, id);
    			fprintf(fp,"%s%s%d#%s:%d\n",a->fname,a->lname,a->age,user_file,id);
   		}
   	}
   	fclose(fp);
  
   	return(0);
}
int mktime2() {
	struct tm strtime;
	//time_t timeoftheday;
	int rval;
	strtime.tm_year = 2015-1900;
	strtime.tm_mon = 11;
	strtime.tm_mday = 17;
	strtime.tm_hour = 11;
	strtime.tm_min =00;
	strtime.tm_sec = 00;
	//timeoftheday = mktime(&strtime);
	rval = chktime2(strtime);
	return rval;
}
int chktime2(struct tm strtime) {
	int flag = 0;
	struct tm tm;
	time_t curtime;
	curtime = time(NULL);
	tm = *localtime(&curtime);
	if(((tm.tm_year)==(strtime.tm_year))&&((strtime.tm_mon<=tm.tm_mon+1))) {
	
		if((strtime.tm_mday>tm.tm_mday)) {
			flag = 1;
			//return flag;
		}
	  	else if(strtime.tm_mday==tm.tm_mday) {
			if(((strtime.tm_hour)-(tm.tm_hour))>=4) {
				flag = 1;
				//return flag;
			}
			else {
				flag = 0;
				//return flag;
			}
		}
	}
	return flag;
}	

int book_ticket2(int choice) {
	//char username[BUFSIZ]; 
  	char buf[BUFSIZ];               
  	char *user_file, *pass_file;       
  	char filename[BUFSIZ]; 
	FILE *fp1, *fp;
   	int len, id=10, flag;
   	char  ch1;
   	//char gen[2];
	info *a;
   	a = (info*)malloc(sizeof(info));
   	fp1 = fopen("Pune_to_Solapur.txt", "r+");
	if(fp1 == NULL) {
		printf("\nFile error!\nAborting...\n");

  	} 
	else {
		while (!feof(fp1)) {
      			buf[0] = '\0';
      			fscanf(fp1, "%s", buf);
     			if(strlen(buf) == 0) 
				continue;
     			user_file = buf;
      			pass_file = strchr(buf, '-');
      			pass_file[0] = '\0';
      			pass_file++;
      			if(strcmp(pass_file, "V") == 0) {
        			flag=0;
				ch1 = 'O';
				fseek(fp1,-1,SEEK_CUR);  
       				fwrite(&ch1,1,1,fp1);
				printf("\n%sis",user_file);
				break;
					
                         } 
		}
			
	}
	
	fclose(fp1);
   //	fp = fopen("Pune_to_Solapurbooking.txt","r");
	if(choice == 1)
		strcpy(filename, "Pune_to_Solapurbooking.txt");
	else if(choice == 3)
		strcpy(filename, "Pune_to_Solapurbooking1.txt"); 
	fp = fopen(filename, "r");
   	fseek(fp,0,SEEK_END);
   	len = ftell(fp);
   	printf("len = %d",len);
   	fclose(fp);
	if(flag == 0) {
   		fp = fopen(filename, "a+");
   		if(len == 0) {
			printf("\nfirstname:");
    			scanf("%s",a->fname);
    			printf("\nlastname:");
    			scanf("%s",a->lname);
    			printf("\nage:");
    			scanf("%d",&a->age);
    			a->tid = id;
			printf("\n%s is your berthno and %d is your id\n", user_file, id);
    			fprintf(fp,"%s%s%d#%s:%d\n",a->fname,a->lname,a->age,user_file,a->tid);
   		}
   		else {
    			fseek(fp,-3,SEEK_END);
    			fscanf(fp,"%d",&a->tid);
    			id = a->tid;
    			id++;
    			printf("\nfirstname:");
    			scanf("%s",a->fname);
    			printf("\nlastname:");
    			scanf("%s",a->lname);
    			printf("\nage:");
    			scanf("%d",&a->age);
    			printf("\n%s is your berthno and %d is your id\n", user_file, id);
    			fprintf(fp,"%s%s%d#%s:%d\n",a->fname,a->lname,a->age,user_file,id);
   		}
   	}
   	fclose(fp);
  
   	return(0);
}

void cancel() {
	char filename[BUFSIZ], userid[5];             
  	FILE  *fp, *fileptr2;  
	int count=0, temp=0; 
	char buf[BUFSIZ], ch1, buf11[BUFSIZ], buf1[BUFSIZ],choice;                   
        char *user_file, *pass_file,*user_file1, *pass_file1 ; 
  	printf("\n\tEnter 1 for deletion of ticket from solapur to pune:\n\tEnter 2 for deletion of ticket from pune to solapur: \n");
  	scanf(" %c", &choice);
	if(choice == '1')
		strcpy(filename, "Solapur_to_Punebooking.txt");
	else if(choice == '2')
		strcpy(filename, "Pune_to_Solapurbooking.txt"); 
	if((fp = fopen(filename, "r")) == NULL){

    		printf("\nFile error!");

  	} 
	else {
		printf("\nEnter your id\n");
		scanf("%s", userid);
		while (!feof(fp)) {
      			buf[0] = '\0';
      			if((fscanf(fp, "%s", buf))==1)
				count++;
     			if(strlen(buf) == 0) 
				continue;
     			
      			pass_file = strchr(buf, ':');
      			pass_file[0] = '\0';
      			pass_file++;
			if(strcmp(pass_file, userid) == 0) {
				user_file = strchr(buf, '#');
				user_file[0] = '\0';
				user_file++;
				//printf("\n%dline to be deleted\n", count);
				printf("%s\n", user_file);
				break;
				
			}
		}
	}
	rewind(fp);
	fileptr2 = fopen("replica.c", "w");
	while (!feof(fp)) {
	
		buf1[0] = '\0';
     		if((fscanf(fp,"%s", buf1))==1);
			temp++;
		if(strlen(buf1) == 0) 
			continue;
      
            //except the line to be deleted

            	if (temp != count) {

                //copy all lines in file replica.c

               		fprintf(fileptr2,"%s\n",buf1);

            	}

    	}

    	fclose(fp);

    	fclose(fileptr2);

    	remove(filename);

    //rename the file replica.c to original name

    	rename("replica.c", filename);
	if(choice == '1')
		strcpy(filename, "Solapur_to_Pune.txt");
	else if(choice == '2')
		strcpy(filename, "Pune_to_Solapur.txt"); 
	fp = fopen(filename, "r+");
	if(fp == NULL) {
		printf("\nFile error!\nAborting...\n");

  	} 
	else {
		while (!feof(fp)) {
      			buf11[0] = '\0';
      			fscanf(fp, "%s", buf11);
     			if(strlen(buf11) == 0) 
				continue;
     			user_file1 = buf11;
      			pass_file1 = strchr(buf11, '-');
      			pass_file1[0] = '\0';
      			pass_file1++;
      			if(strcmp(user_file, user_file1) == 0) {
        			//flag=0;
				ch1 = 'V';
				fseek(fp,-1,SEEK_CUR);  
       				fwrite(&ch1,1,1,fp);
				//printf("\n%s\t%s",user_file1,user_file);
				break;
					
                         } 
		}
			
	}
	fclose(fp);
}
		

void enquiry() {
	char filename[BUFSIZ];
  	char buf[BUFSIZ];               
  	char *pass_file, choice;       
  	//char filename[BUFSIZ];             
  	FILE *infile;                      
  	printf("\tEnter 1 for solapur to pune train:\n\tEnter 2 for pune to solapur:\n");
  	scanf(" %c", &choice);
  	if(choice == '1')
		strcpy(filename, "Solapur_to_Pune.txt");
	else if(choice == '2')
		strcpy(filename, "Pune_to_Solapur.txt"); 

  	if((infile = fopen(filename, "r")) == NULL) {

    		printf("\nFile error!\nAborting...\n");

  	} 
	else {
  		while (!feof(infile)) {
      			buf[0] = '\0';
      			fscanf(infile, "%s", buf);
     			if(strlen(buf) == 0) 
				continue;
     			//user_file = buf;
      			pass_file = strchr(buf, '-');
      			pass_file[0] = '\0';
      			pass_file++;
			if(strcmp(pass_file, "V") == 0) {
				printf("\n%s\t%s", buf, pass_file);
			}
		}
	}
	fclose(infile);
}
void Logout(char c, int *a) {
	
	if(c == '3') {
		*a = 0;
		
	}
}



