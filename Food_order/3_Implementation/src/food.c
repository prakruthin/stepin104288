#include "food.h"
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

/* reads from keypress, doesn't echo */
int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

/* reads from keypress, echoes */
int getche(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}


struct menu
{

	//char name[30];
	int id;
	char name[30];
	//char DOB[10];
	int price;
};
struct menu m;

struct employee
{

	char name[30];
	int id;
	//char DOB[10];
	int dd; int mm; int yyyy;
	int YOJ;
	char place[20];
	float salary;
	char department[20];

	int quantity;
};
struct employee e;

FILE *fp,*ft,*dp,*dt;

int s;
char findrecord;
int again;
int quantity;
double total=0;
int t;
char password[20]="123321";
/*
int main()
{
	mainmenu();
	return 0;
}
*/
int add(int a, int b)
{
	return a+b;
}

void mainmenu(void)
{
	system("cls");
	printf("                           **************************************************************************\n");
	printf("                                          WELCOME TO FOOD ORDER MANAGEMENT SYSTEM\n");
	printf("                           **************************************************************************\n\n\n");
	printf("          1. ADMINISTRATION SECTION--> \n\n          2. CUSTOMER SECTION--> \n\n          3. Exit--> \n\n\n             Enter Your Choice --->");
	int choice;
	scanf("%d",&choice);
	if(choice==1)
	{
	    Password();
		administration();
	}
	else if(choice==2)
	{
		//customer();
		viewmenu();

    }
	else if(choice==3)
	{
		system("cls");
		printf("\n\n\n");
		printf("*********************************************************THANK YOU****************************************************************\n");

		printf("*************************************************Feeling HUNGRY ? Call or Walk-In***********************************************\n\n");
		exit(0);
	}
	else
	{
		printf("Wrong Input !! PLease Re-enter The Correct Option");
		if(getch())
		mainmenu();
	}
}

void administration(void)
{
	system("cls");
	printf("\n\n*************************************************WELCOME TO THE ADMIN SECTION****************************************************\n\n");
	printf("          1. Add New Record\n\n          2. Search Record\n\n          3. Delete Record\n\n          4. View Employee Records\n\n          5. View previous orders\n\n          6. Add Food\n\n          7. Delete Food\n\n          8. View Menu\n\n          0. Back To Main Menu \n\n             Enter Your Choice --->");
	int n;
	scanf("%d",&n);
		printf("\n\n");
	int wait;
	//printf("In progress :");
	for(wait=0;wait<=10000;wait++)
	{
		printf("\rIn progress : %d",wait/100);
	}
	printf("\n\n");
	if(n==1)
	{
		addrecord();
	}
	else if(n==2)
	{
		searchrecord();
	}
	else if(n==3)
	{
		deleterecord();
	}
	else if(n==4)
	{
		viewrecord();
	}
		else if(n==5)
	{
		FILE *view;
		char viw;
		view = fopen("order.txt","rt");
		system("cls");
		while((viw=fgetc(view))!=EOF)
		{
			printf("%c",viw);
		}
		fclose(view);
	}
	else if(n==6)
    {
        system("cls");
        addfood();
    }
    else if(n==7)
    {
        system("cls");
        deletefood();
    }
    else if(n==8)
    {
        system("cls");
        viewmenu1();
    }
	else if(n==0)
	{
		system("cls");
		mainmenu();
	}
	else
	{
		printf("Wrong Input !! PLease Re-enter The Correct Option");
		if(getch())
		administration();
	}

}

void addrecord(void)
{
	system("cls");
	//fp=fopen("record.txt","a");
	if(getdata()==1)
	{
	    fp=fopen("record.txt","a");
		fseek(fp,0,SEEK_END);
		fwrite(&e,sizeof(e),1,fp);
		fclose(fp);
		printf("\n\n");
		printf("The Record Is Successfully Saved ! !\n\n");
		printf("Save any more?(Y / N): ");
		if(getch()=='n')
	    	administration();
		else
	    	system("cls");
	    	addrecord();
	}
}

void searchrecord(void)
{
	system("cls");
	char findrecord='f';
    int d;
    printf("\n\n**************************************************Search Employees Record********************************************************\n\n");
    printf("                  1. Search By ID\n");
    printf("                  2. Search By Name\n\n");
    printf("                  Enter Your Choice---> ");
    fp=fopen("record.txt","r"); //open file for reading propose
    rewind(fp);   //move pointer at the begining of file
    switch(getch())
    {
	  case '1':
		{
	    	system("cls");
	    	printf("\n\n****************************************************Search Record By ID**********************************************************\n\n");
	    	printf("                Enter The Employee ID : ");
	    	scanf(" %d",&d);
	    	printf("\n\n");
			printf("Searching........");
	    	while(fread(&e,sizeof(e),1,fp)==1)
	    	{
				if(e.id==d)
				{
		    		printf("\n\n");
                    printf("....................................................The Record is available......................................................\n\n");
				    printf("       ID : %d\n\n",e.id);
				    printf("       Name : %s\n\n",e.name);
				    printf("       Date OF Birth :%d/%d/%d\n\n",e.dd,e.mm,e.yyyy);
				    printf("       Year Of Joining :%d\n\n",e.YOJ);
				    printf("       Department :%s\n\n",e.department);
				    printf("       Place :%s\n\n",e.place);
				    findrecord='t';
				}

	    }
	    if(findrecord!='t')  //checks whether conditiion enters inside loop or not
	    {
	    	printf("\aNo Record Found\a");
	    	printf("\n\n");
	    }
	    printf("Try Another Search ? (y/n)");
	    if(getch()=='y')
	    searchrecord();
	    else
	    administration();
	    break;
	}
	case '2':
	{
	    char s[15];
	    system("cls");
	    printf("\n\n**************************************************Search Employees By Name*******************************************************\n\n");
	    printf("               Enter Employee Name : ");
	    scanf(" %s",s);
	    int d=0;
	    while(fread(&e,sizeof(e),1,fp)==1)
	    {
		if(strcmp(e.name,(s))==0) //checks whether a.name is equal to s or not
		{
		    printf("\n\n...................................................The Record is available.....................................................\n\n\n");
			printf("       ID : %d\n\n",e.id);
			printf("       Name : %s\n\n",e.name);
			printf("       Date OF Birth :%d/%d/%d\n\n",e.dd,e.mm,e.yyyy);
			printf("       Year Of Joining :%d\n\n",e.YOJ);
			printf("       Department :%s\n\n",e.department);
			printf("       Place :%s\n\n",e.place);
		    d++;
		}

	    }
	    if(d==0)
	    {
	    	printf("\aNo Record Found\a");
	    }
	    printf("Try Another Search ? (Y/N)");
	    if(getch()=='y')
	    searchrecord();
	    else
	    administration();
	    break;
	}
	default :
	getch();
	searchrecord();
    }
    fclose(fp);
}

void deleterecord(void)
{
	system("cls");
    int d;
    char another='y';
    findrecord='f';
    while(another=='y')  //infinite loop
    {
	system("cls");
	printf("                Enter The Employee ID To Delete :");
	scanf(" %d",&d);
	fp=fopen("record.txt","r+");
	rewind(fp);
	while(fread(&e,sizeof(e),1,fp)==1)
	{
	    if(e.id==d)
	    {
			printf("\n\n");
			printf("\n\n..............................................The Employee Record Is Available...................................................\n\n");
			printf("               Employee Name Is %s\n\n",e.name);
			printf("               Employee's Date  OF Birth Is %d/%d/%d\n\n",e.dd,e.mm,e.yyyy);
			findrecord='t';
	    }
	}
	if(findrecord!='t')
	{
	    printf("\n\n............................................No record is found modify the search.................................................\n\n");
	    if(getch())
	    administration();
	}
	if(findrecord=='t' )
	{
	    printf("Do You Want To Delete THe Record ? (Y/N) ");
	    if(getch()=='y')
	    {
			ft=fopen("test1.txt","w");  //temporary file for delete
			rewind(fp);
			while(fread(&e,sizeof(e),1,fp)==1)
			{
		    	if(e.id!=d)
		    	{
					fseek(ft,0,SEEK_CUR);
					fwrite(&e,sizeof(e),1,ft); //write all in tempory file except that
		    	}                              //we want to delete
			}
			fclose(ft);
			fclose(fp);
			remove("record.txt");
			rename("test1.txt","record.txt"); //copy all item from temporary file to fp except that
			fp=fopen("record.txt","r");    //we want to delete
			if(findrecord=='t')
			{
		    	printf("        THE RECORD IS SUCCESSFULLY DELETED.\n\n");
		    	printf("        Delete Another Record ? (Y/N) : ");
			}
	    }
		else
		administration();
		fflush(stdin);
		another=getch();
	}
    }
administration();
}


void viewrecord(void)
{
    system("cls");
    printf("\n\n**************************************************** Employee Details************************************************************\n\n");
    printf("                 ID        EMPLOYEE NAME           D.O.B            Y.O.J        PLACE         DEPARTMENT\n\n");

    fp=fopen("record.txt","r");
    while(fread(&e,sizeof(e),1,fp)==1)
    {
		printf("                 %d",e.id);
		//printf("        %d",e.id);
		printf("        %s",e.name);
		printf("                   %d/%d/%d",e.dd,e.mm,e.yyyy);
		printf("        %d",e.YOJ);
		printf("        %s",e.place);
		printf("        %s",e.department);
		printf("\n\n");
	}

      fclose(fp);
      returnfunc();
}

void returnfunc(void)
{
    {
		printf(" Press ENTER to return to main menu");
    }
    e:
    if(getch()==13) //allow only use of enter
    administration();
    else
    goto e;
}

int checkid(int c)  //check whether the record is exist in list or not
{

    int temp=1;
	//rewind(fp);
	//printf("%d",fp);
	fp=fopen("record.txt","r");
	//printf("outside while\n");
	//printf("%d\n",fread(&e,sizeof(struct employee),1,fp));
	//printf("%d",e.id);
	while(fread(&e,sizeof(struct employee),1,fp)==1)
	{
	    if(e.id==c)
        {
            temp=0;  //returns 0 if employee exits
            break;
        }
	}
	return temp; //return 1 if it not
}
int getdata()
{
	//*int t;
	printf("        Employee ID :\t");
	scanf("%d",&t);
	//printf("%d",checkid(t));
	if(checkid(t)==0)
	{
		printf("\n\n");
		printf("\a                        The Employee Record Already Exists !!!\a");
		getch();
		administration();
		return 0;
	}
	e.id=t;
	printf("        Employee Name : ");
	scanf("%s",e.name);
	printf("        Date Of Birth (dd/mm/yyyy) :");
	scanf("%d/%d/%d",&e.dd,&e.mm,&e.yyyy);
	printf("        Year OF Joining :");
	scanf("%d",&e.YOJ);
	printf("        Place :");
	scanf("%s",e.place);
	printf("        Department :");
	scanf("%s",e.department);
	return 1;
}

void details(void)
{
	char name1[20];
	char name2[20];
	long long int phone;
	char address[40];
	char landmark[30];
	printf("Please Give Your Contact Details \n");
	printf(" First Name : ");
	scanf("%s",name1);
	printf("Last Name : ");
	scanf("%s",name2);
	printf("Phone : ");
	scanf("%lld",&phone);
	printf("Address : ");
	scanf("%s",address);
	printf("Landmark : ");
	scanf("%s",landmark);
	printf("\n\n");
	printf("Your Entered Details Are --->\n");
	FILE *cust;
	cust = fopen("order.txt","a");
	fprintf(cust,"Order Placed By : %s %s\nPhone number : %lld\n\n\n",name1,name2,phone);
	fclose(cust);
	printf("    -->First Name :  %s\n    -->Last Name   :  %s\n    -->Phone     :%lld \n    -->Address  :%s \n    -->Landmark  :%s \n",name1,name2,phone,address,landmark);
	printf("\n\n\n");
	printf("                       *********************************************************************************************\n");
	printf("                                             Your Order Will Be At Your Door In 30 minutes.\n");
	printf("                                                       .....HAPPY ORDERING.....\n");
	printf("                       *********************************************************************************************\n");

	printf("Press Any To The MainMenu.");
	if(getch())
	//customer();
	mainmenu();
}

void Password(void)
{
	system("cls");
	char d[30]="PASSWORD PROTECTED";
	char ch,pass[10];
	int i=0,j;
	for(j=0;j<20;j++)
	{
		//delay(50);
		printf("*");
	}
	for(j=0;j<20;j++)
	{
		//delay(50);
		printf("%c",d[j]);
	}
	for(j=0;j<20;j++)
	{
		//delay(50);
		printf("*");
	}
	printf("\nENTER PASSWORD : ");
	while(ch!=13)
	{
		ch=getch();
		if(ch!=13 && ch!=8)
		{
			putch('*');
			pass[i]=ch;
			i++;
		}
	}
	pass[i]='\0';
	if(strcmp(pass,password)==0)
	{
		printf("PASSWORD MATCHED !!!\n\n");
		//printf("Press Any Key To Continue......\n\n");
		//getch();
		//mainmenu();
        administration();
	}
	else
	{
		printf("WARNING ! INCORRECT PASSWORD....");
		getch();
		Password();
	}
}

void addfood(void)
{
	system("cls");
	//fp=fopen("record.txt","a");
	//printf("%d",getdata());
	if(getmenudata()==1)
	{
	    fp=fopen("menu.txt","a");
		fseek(fp,0,SEEK_END);
		fwrite(&m,sizeof(m),1,fp);
		fclose(fp);
		printf("\n\n");
		printf("The Record Is Successfully Saved ! !\n\n");
		printf("Save any more?(Y / N): ");
		if(getch()=='n')
	    	administration();
		else
	    	system("cls");
	    	addfood();
	}
}

int checkmenuid(int c)  //check whether the record is exist in list or not
{

    int temp=1;
	//rewind(fp);
	//printf("%d",fp);
	fp=fopen("menu.txt","r");
	//printf("outside while\n");
	//printf("%d\n",fread(&e,sizeof(struct employee),1,fp));
	//printf("%d",e.id);
	while(fread(&m,sizeof(struct menu),1,fp)==1)
	{
	    if(m.id==c)
        {
            temp=0;  //returns 0 if employee exits
            break;
        }
	}
	return temp; //return 1 if it not
}
int getmenudata()
{
	//*int t;
	printf("        Food ID :\t");
	scanf("%d",&t);
	//printf("%d",checkid(t));
	if(checkmenuid(t)==0)
	{
		printf("\n\n");
		printf("\a                        The Dish Record Already Exists !!!\a");
		getch();
		addfood();
		return 0;
	}
	m.id=t;
	printf("        Dish Name : ");
	scanf("%s",m.name);
	printf("        Price :");
	//printf("gulullluuuu");
	scanf("%d", &m.price);
	//printf("%d", t);
	return 1;
}

void viewmenu(void)
{
    int choice;
	int again;
	int quantity;
    system("cls");
    printf("                              ********************** Food Menu**********************\n\n");
    printf("                 ID        DISH NAME        PRICE\n\n");

    fp=fopen("MENU.txt","r");
    while(fread(&m,sizeof(m),1,fp)==1)
    {
		printf("                 %d",m.id);
		//printf("        %d",e.id);
		printf("         %s",m.name);
		printf("           %d",m.price);
        printf("\n\n");
	}
	placeorder();
	/*
	printf("\n\nEnter What You Want :");
	printf("\n\n");
	scanf("%d",&choice);
	rewind(fp);
    while(fread(&m,sizeof(m),1,fp)==1)
    {
        if(m.id==choice)
        {
            printf("Quantity :  ");
            scanf("%d",&quantity);
            total=total + m.price*(quantity);
            printf("\n");

            FILE *ttl;
            ttl = fopen("order.txt","a");
            fprintf(ttl,"\n%s\n quantity : %d\n",m.name,quantity);
            fclose(ttl);

            printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
            scanf("%d",&again);
            printf("\n");
            if(again==1)
            {
                printf("\n\n");
                viewmenu();
            }
            else if(again==2)
            {
                printf("Your Total Amount Is :%.2lf\n\n",total);
                int totl = total;
                FILE *ttl;
                ttl = fopen("order.txt","a");
                fprintf(ttl,"\nGrand Total : %d\n",totl);
                fclose(ttl);
                printf("success!!!");
                //administration();

                details();
            }
            else
            {
                printf("Wrong Input! Re-enter THe Correct Option\n\n");
                if(getch())
                viewmenu();
            }

        }

    }
    */


      fclose(fp);
      returnfunc1();
}

void returnfunc1(void)
{
    {
		printf(" Press ENTER to return to main menu");
    }
    e:
    if(getch()==13) //allow only use of enter
    //administration();
    mainmenu();
    else
    goto e;
}
////////////////////////////////////


//441

void deletefood(void)
{
	system("cls");
    int d;
    char another='y';
    while(another=='y')  //infinite loop
    {
	system("cls");
	printf("                Enter The Food ID To Delete :");
	scanf(" %d",&d);
	fp=fopen("menu.txt","r+");
	rewind(fp);
	while(fread(&m,sizeof(m),1,fp)==1)
	{
	    if(m.id==d)
	    {
			printf("\n\n");
			printf("                               .....................The Food Record Is Available....................\n\n");
			printf("               Food Name Is : %s\n\n",m.name);
			printf("               Food Price Is : %d\n\n",m.price);
			findrecord='t';
	    }
	}
	if(findrecord!='t')
	{
	    printf("                                    .........................No record is found modify the search..........................\n\n");
	    if(getch())
	    administration();
	}
	if(findrecord=='t' )
	{
	    printf("Do You Want To Delete THe Record ? (Y/N) ");
	    if(getch()=='y')
	    {
			ft=fopen("test2.txt","w");  //temporary file for delete
			rewind(fp);
			while(fread(&m,sizeof(m),1,fp)==1)
			{
		    	if(m.id!=d)
		    	{
					fseek(ft,0,SEEK_CUR);
					fwrite(&m,sizeof(m),1,ft); //write all in tempory file except that
		    	}                              //we want to delete
			}
			fclose(ft);
			fclose(fp);
			remove("menu.txt");
			rename("test2.txt","menu.txt"); //copy all item from temporary file to fp except that
			fp=fopen("menu.txt","r");    //we want to delete
			if(findrecord=='t')
			{
		    	printf("        THE FOOD RECORD IS SUCCESSFULLY DELETED.\n\n");
		    	printf("        Delete Another Record ? (Y/N) : ");
			}
	    }
		else
		administration();
		fflush(stdin);
		another=getch();
	}
    }
administration();
}

void placeorder(void)
{
    int choice;
	int again;
	int quantity;
	int temp=0;
	fp=fopen("MENU.txt","r");
    printf("\n\nEnter What You Want :");
	printf("\n\n");
	scanf("%d",&choice);
	rewind(fp);
    while(fread(&m,sizeof(m),1,fp)==1)
    {
        if(m.id==choice)
        {
            printf("Quantity :  ");
            scanf("%d",&quantity);
            temp=m.price*(quantity);
			total=add(total,temp);
            //total=total + m.price*(quantity);
            printf("\n");

            FILE *ttl;
            ttl = fopen("order.txt","a");
            fprintf(ttl,"\n%s\n quantity : %d\n",m.name,quantity);
            fclose(ttl);

            printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
            scanf("%d",&again);
            printf("\n");
            if(again==1)
            {
                printf("\n\n");
                viewmenu();
            }
            else if(again==2)
            {
                printf("Your Total Amount Is :%.2lf\n\n",total);
                int totl = total;
                FILE *ttl;
                ttl = fopen("order.txt","a");
                fprintf(ttl,"\nGrand Total : %d\n",totl);
                fclose(ttl);
				total=0;
                //printf("success!!!");
                //administration();

                details();
            }
            else
            {
                printf("Wrong Input! Re-enter THe Correct Option\n\n");
                if(getch())
                viewmenu();
            }

        }

    }
    fclose(fp);
    returnfunc1();
}

void viewmenu1(void)
{
    system("cls");
    printf("                              ********************** Food Menu**********************\n\n");
    printf("                 ID        DISH NAME        PRICE\n\n");

    fp=fopen("MENU.txt","r");
    while(fread(&m,sizeof(m),1,fp)==1)
    {
		printf("                 %d",m.id);
		//printf("        %d",e.id);
		printf("         %s",m.name);
		printf("           %d",m.price);
        printf("\n\n");
	}
    fclose(fp);
    returnfunc();
}

