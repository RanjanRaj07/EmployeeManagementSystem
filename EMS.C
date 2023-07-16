#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
int choice,login1=0;
char another;
FILE *fp, *ft;
char uname[]="admin",pwd[]="123456";

struct emp
{
    int id;
    char name[50];
    char address[100];
    char gender[2];
    int age;
    char phone[11];
    float salary;
};
struct emp e;

long int size = sizeof(e);

void Ems();
void admin();
void employee();
void login();
void addEmp();
void deleteEmp();
void modifyEmp();
void searchEmp();
void displayEmp();

void admin()
{
	while(login1 == 1)
	{
		system("cls");
		printf("\n \033[0;34m*-*-*- | WELCOME TO ADMIN PAGE | *-*-*- \n");
		printf("\n 1) Add a Employee \n 2) List the Employee \n 3) Edit the Employee Details \n 4) Search the Employee \n 5) Delete the Employee Details \n 6)Logout\n");
		printf("\tEnter Your Choice:\t");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
			       addEmp();
			       break;
			case 2:
			       displayEmp();
			       break;
			case 3:
			       modifyEmp();
			       break;
			case 4:
			       searchEmp();
			       break;
			case 5:
			       deleteEmp();
			       break;
			case 6:
				   system("cls");
				   printf("\n\n\n\tYOU HAVE LOGGED OUT SUCCESSFULLY!!");
				   system("pause");
				   login1=0;
				   Ems();
				   break;
			default:
				    printf("\nInvalid Choice\n");
		}
	}
}


void employee()
{
	int echoice;
	system("cls");
		printf("\n\t \033[0;31m*-*-*- | WELCOME TO EMPLOYEE PAGE | *-*-*- \n");
		printf("\n\t 1)Search the Employee\n\t 2)Main Menu\n");
		printf("\tEnter Your Choice:\t");
		scanf("%d",&echoice);
		switch(echoice)
		{
			case 1:
			       searchEmp();
			       break;
			case 2:
			       Ems();
			       break;
			default:
				    printf("\nInvalid Choice\n");
		}
}

void login()
{
    char c,un[30],pass[30];
    int i=0;
    int checku,checkp;
	system("cls");
    printf("\033[0;36m\n\n\t\tADMIN LOGIN");
    printf("\n\t\t^-^-^-^-^-^-^-^-^-^-^-^-^");
    printf("\n\n\t\tENTER USERNAME: ");
    scanf("%s",un);
    printf("\n\n\t\tENTER PASSWORD: ");
    while((c=getch())!=13)
     {
		pass[i++]=c;
		printf("%c",'*');
    }
	pass[i]='\0';
	checku=strcmp(un,uname);
	checkp=strcmp(pass,pwd);
	if(checku==0&&checkp==0)
	{
		printf("\n\n\n\t\tYOU HAVE LOGGED IN SUCCESSFULLY!!\n");
		system("pause");
		login1=1;
		admin();
	}
	else if(checku==0&&checkp!=0)
	{
		printf("\n\n\n\t\t\tWRONG PASSWORD!! Not %s??",un);
		printf("\n\n\t\t\t\t  (Press 'y' to re-login)");
		if(getch()=='y'||getch()=='Y')
	    login();
    }
	else
	{
		printf("\n\n\n\t\t\tYou are not a Authorized User");
		system("pause");
		Ems();
	}
}

void addEmp()
{
	system("cls");
    fseek(fp, 0, SEEK_END);
    another = 'y';
	printf("\n Enter the Employee Details to be Added: \n");
    while (another == 'y')
	{
	printf("\n Enter the Employee ID : ");
	scanf("%d", &e.id);

	printf("\n Enter the Employee Name : ");
	scanf("%s", e.name);

	printf("\n Enter the Employee Address : ");
	scanf("%s", e.address);

	printf("\n Enter the Employee Gender[M/F] : ");
	scanf("%s", e.gender);

	printf("\n Enter the Employee Age : ");
	scanf("%d", &e.age);

	printf("\nEnter the Employee Phone No. : ");
	scanf("%s", e.phone);

	printf("\nEnter the Employee Salary : ");
	scanf("%f", &e.salary);

	fwrite(&e, size, 1, fp);

	printf("\n You want to add another Employee Details (y/n) : ");
	fflush(stdin);
	scanf("%c", &another);
    }
}

void deleteEmp()
{
    int id;
    another = 'y';
    system("cls");

    while (another == 'y') {
	printf("\n Enter the Employee ID to delete : ");
	scanf("%d",&id);

	ft = fopen("tempd.bin", "wb+");
	rewind(fp);

	while (fread(&e, size,1, fp) == 1)
		{
	    if (id != e.id)
		fwrite(&e, size, 1, ft);
	}

	fclose(fp);
	fclose(ft);
	remove("empd.bin");
	rename("tempd.bin", "empd.bin");
	fp = fopen("empd.bin", "rb+");

	printf("\n You want to Delete another Employee Details (y/n) : ");
	fflush(stdin);
	scanf("%c", &another);
    }
}

void modifyEmp()
{
	int id;
    another = 'y';
    system("cls");

    while (another == 'y')
	{
	printf("\nEnter the Employee ID to modify : ");
	scanf("%d",&id);
	rewind(fp);
	while (fread(&e, size, 1, fp) == 1)
		{
	    if (id == e.id)
			{
		printf("\n Enter the Employee New ID : ");
				scanf("%d", &e.id);

				printf("\n Enter the Employee New Name : ");
				scanf("%s", e.name);

				printf("\n Enter the Employee New Address : ");
				scanf("%s", e.address);

				printf("\n Enter the Employee Gender[M/F] : ");
				scanf("%s", e.gender);

				printf("\n Enter the Employee New Age : ");
				scanf("%d", &e.age);

				printf("\nEnter the Employee New Phone No. : ");
				scanf("%s", e.phone);

				printf("\nEnter the Employee New Salary : ");
				scanf("%f", &e.salary);

		fseek(fp, -size, SEEK_CUR);
		fwrite(&e, size, 1, fp);
		break;
	    }
	}
		printf("\n You want to Modify another Employee Details (y/n) : ");
	fflush(stdin);
	scanf("%c", &another);
	}
}

void searchEmp()
{
	FILE *fptr;
	int found=0, id;
	system("cls");
	fptr = fopen("empd.bin","rb+");
	if(fptr==NULL)
	{
		printf("File could not open");
		exit(0);
	}
	printf("\n Enter ID of Employee to Search Record->");
	scanf("%d",&id);
	while((fread(&e,size,1,fptr)==1))
	{
		if(e.id == id)
		{
			found=1;
			printf("\nRecord of Employee With ID-> %d is as follows:\n",id);
			printf("\t-----------------------------------------------------------------\n");
			printf("\n\tID\tNAME\tADDRESS\tGENDER\tAGE\tPHONE\t       SALARY \n");
			printf("\t-----------------------------------------------------------------\n");
			printf("\n\t%d\t%s\t%s\t%s\t%d\t%s\t%.2f\n", e.id, e.name, e.address, e.gender, e.age, e.phone, e.salary);
			break;
		}
	}
	if(found==0)
		printf("\n Record Not found in this file!");
	fclose(fptr);
	system("pause");
}

void displayEmp()
{
	system("cls");
    rewind(fp);
    printf("\t-----------------------------------------------------------------\n");
    printf("\n\tID\tNAME \tADDRESS\tGENDER \tAGE\tPHONE    \tSALARY \n");
    printf("\t-----------------------------------------------------------------\n");
    while (fread(&e, size, 1, fp) == 1)
	printf("\n\t%d\t%s\t%s\t%s\t%d\t%s\t%.2f", e.id, e.name, e.address, e.gender, e.age, e.phone, e.salary);
    printf("\n\n\n\t");
    system("pause");
}
void Ems ()
{
	int mainc;
	system("cls");
    fp = fopen("empd.bin", "rb+");
    if (fp == NULL)
	{
	fp = fopen("empd.bin", "wb+");
	if (fp == NULL)
		{
	    printf("\nCannot open file...");
	    exit(1);
	}
    }
	while(1)
	{
		system("cls");
		printf("\n \033[0;35m*-*-*- | MAIN MENU | *-*-*- \n");
		printf("\n \033[0;36m1) Admin\n 2) Employee\n 3) Exit\n");
		printf("Enter Your Choice:\t");
		scanf("%d",&mainc);
		switch(mainc)
		{
			case 1:
			       login();
			       break;
			case 2:
			       employee();
			       break;
			case 3:
				   fclose(fp);
			       exit(0);
			default:
				    printf("\nInvalid Choice\n");
		}
	}
}

void main()
{
	system("cls");
	printf("\n \033[0;34m::::::::::::::::::::::  | EMPLOYEES MANAGEMENT SYSTEM|  :::::::::::::::::::::: \n");
	printf("\n \033[0;36m*| A R M Y  T E A M  M E M B E R S |* \n");
	printf("\n \033[0;31m1. AMARNATH \n 2. RANJAN \n 3. MOHAMMED SULAIMAN \n 4. Yashwanth \n");
	system("pause");
	Ems();
	getch();
}