#define _XOPEN_SOURCE
#define _GNU_SOURCE         
#include <crypt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "project1.h"
int Log_In() {
	char username[BUFSIZ], *password; 
  	char buf[BUFSIZ],c;               
  	char *user_file, *pass_file;       
  	char filename[BUFSIZ];             
  	FILE *infile, *fp;                      
        int flag = 0,z=0,a=0,flag1 =0;   
  	printf("Enter Password Filename: ");
  	scanf("%s", filename);
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
    		} 

  	}  
  fclose(infile);
  return(flag);
  
} 

void printmenu() {
	int choice;
	printf("\n\tEnter 1 for reservation(solapur to pune) :\n\t2. reservation(pune to solapur)\n\t3.canellation\n\t4.enquiry\n\t5.Exit");
	printf("Choice : ");
	scanf("%d", &choice);
	switch(choice) {
		case 1:
			ticket_book1();
			break;
		case 2:
			ticket_book2();
			break;
	/*	case 3:
			cancel();
			break;
		case 4:
			enquiry();
			break;  */
		case 5:
			exit(1);
		default:
			printf("Not a valid choice");
	}
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
  	printf("Enter Password Filename: ");
  	scanf("%s", filename);

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





void train_berth() {
        FILE *fp, *tr;
        char d[8][3]={{"S1"},{"S2"},{"S3"},{"S4"},{"S5"},{"S6"},{"S7"},{"S8"}};
	train *p, *q;
	berth *r,*s;
	char ch,c;
        int i=0,count=0,val,ch1;
	p = (struct train *)malloc(sizeof(train));
	strcpy(p->train_no, "4156");
	strcpy(p->train_name, "Solapur_to_Pune");
	q = (struct train *)malloc(sizeof(train));
	strcpy(q->train_no, "4526");
	strcpy(q->train_name,  "Pune_to_Solapur");
	fp = fopen("tr.txt", "r");
	if(fp == NULL) {
		fp = fopen("tr.txt", "w");
		fprintf(fp, "%s\n%s\n", p->train_no, p->train_name);
		
		fprintf(fp, "%s\n%s\n" , q->train_no, q->train_name);
		fclose(fp);
	}

        
	tr = fopen("berth_1.txt", "r");
	s = (struct berth *)malloc(sizeof(berth));
	strcpy(s->coano, d[0]);
	strcpy(s->status, "V");
	if(tr == NULL) {
		tr = fopen("berth_1.txt", "w");
		for(i=1;i<=73;i++) {
		   	if(i>72) {
				count++;
				strcpy(s->coano, d[count]);
				i=1;
		   	}
			if(count == 8)
				break;
			s->seat_no = i;
			fprintf(tr,"%d  %s  %s\n",s->seat_no,s->coano,s->status);

	    	}
	}
	fclose(tr);
	
	tr = fopen("berth_2.txt", "r");
	s = (struct berth *)malloc(sizeof(berth));
	strcpy(s->coano, d[0]);
	strcpy(s->status, "V");
	if(tr == NULL) {
		tr = fopen("berth_2.txt", "w");
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
			fprintf(tr,"%d  %s  %s\n",s->seat_no,s->coano,s->status);

	    	}
	}
	fclose(tr);


}



void ticket_book1() {
	FILE *fp1,*fp;
   	int len,i,id=10;
   	char ch,ch1,str[10];
   	char gen[2];
  	 info *a;
   	a = (info*)malloc(sizeof(info));
   	fp1 = fopen("berth_1.txt", "r+");
   
   	printf("\nticket_book1\n");
   	if( fp1 == NULL ) {
        	perror ("Error opening file");
      		//return(-1);
   	}
   
   	fseek(fp1, 0, SEEK_SET);
   
  	 while(!feof(fp1)) {
     
     		while(fread(&ch,1,1,fp1)) {
       			if(ch == 'V')
       				break;
       			if(ch == 'O') { 
         			i = 0;    
       			}
      			else {
         			if(ch!='\n') { 
          				str[i] = ch;
          				i++;
        			}  
       			} 
     		}
     		str[i] = '\0';
     		if(ch == 'V') {
        
       			printf("\nin if = %c\n",ch);
       			ch1 = 'O';
       			fseek(fp1,-1,SEEK_CUR);  
       			fwrite(&ch1,1,1,fp1);
       
    		 }
    
     		printf("\nstr = %s",str);
     
     		if(ch == 'V')
     			break;
     		if(ch == 'O')
     			continue;
   	}
   	fclose(fp1);
   	fp = fopen("book_1.txt","r");
   	fseek(fp,0,SEEK_END);
   	len = ftell(fp);
   	printf("len = %d",len);
   	fclose(fp);
   	fp = fopen("book_1.txt","a+");
   	if(len == 0) {
    
    		printf("\nfname:");
    		scanf("%s",a->fname);
    		printf("\nlname:");
    		scanf("%s",a->lname);
    		printf("\nage:");
    		scanf("%d",&a->age);
    		a->tid = id;
    		fprintf(fp,"%s\n%s\n%d\n%s\n%d\n",a->fname,a->lname,a->age,str,a->tid);
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
    
   		fprintf(fp,"%s\n%s\n%d\n%s\n%d\n",a->fname,a->lname,a->age,str,id);
   	}
   
   	fclose(fp);
  
   //return(0);
}


void ticket_book2() {
	FILE *fp1,*fp;
   	int len,i,id=10;
   	char ch,ch1,str[10];
   	char gen[2];
  	 info *a;
   	a = (info*)malloc(sizeof(info));
   	fp1 = fopen("berth_2.txt", "r+");
   
   	printf("\nticket_book1\n");
   	if( fp1 == NULL ) {
        	perror ("Error opening file");
      		//return(-1);
   	}
   
   	fseek(fp1, 0, SEEK_SET);
   
  	 while(!feof(fp1)) {
     
     		while(fread(&ch,1,1,fp1)) {
       			if(ch == 'V')
       				break;
       			if(ch == 'O') { 
         			i = 0;    
       			}
      			else {
         			if(ch!='\n') { 
          				str[i] = ch;
          				i++;
        			}  
       			} 
     		}
     		str[i] = '\0';
     		if(ch == 'V') {
        
       			printf("\nin if = %c\n",ch);
       			ch1 = 'O';
       			fseek(fp1,-1,SEEK_CUR);  
       			fwrite(&ch1,1,1,fp1);
       
    		 }
    
     		printf("\nstr = %s",str);
     
     		if(ch == 'V')
     			break;
     		if(ch == 'O')
     			continue;
   	}
   	fclose(fp1);
   	fp = fopen("ticbook2.txt","r");
   	fseek(fp,0,SEEK_END);
   	len = ftell(fp);
   	printf("len = %d",len);
   	fclose(fp);
   	fp = fopen("ticbook2.txt","a+");
   	if(len == 0) {
    
    		printf("\nfname:");
    		scanf("%s",a->fname);
    		printf("\nlname:");
    		scanf("%s",a->lname);
    		printf("\nage:");
    		scanf("%d",&a->age);
    		a->tid = id;
    		fprintf(fp,"%s\n%s\n%d\n%s\n%d\n",a->fname,a->lname,a->age,str,a->tid);
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
    
   		fprintf(fp,"%s\n%s\n%d\n%s\n%d\n",a->fname,a->lname,a->age,str,id);
   	}
   
   	fclose(fp);
  
   //return(0);
}
