typedef struct train {
	char train_no[10];
	char train_name[20];
}train;
typedef struct berth{
	int seat_no;
	char coano[3];
	char status[1];
}berth;
typedef struct info{
        char fname[20];
        char lname[20];
        int age;
        int tid;
}info;
//char d[8][3]={{"S1"},{"S2"},{"S3"},{"S4"},{"S5"},{"S6"},{"S7"},{"S8"}};
int Log_In();
void Sign_Up();
void printmenu();
void ticket_book1();
void ticket_book2();

