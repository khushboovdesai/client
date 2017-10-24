//#include <gtk/gtk.h>
#include <stdio.h>
#define _USE_BSD 1
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdarg.h>
#include <stdlib.h>
#include <semaphore.h>
#include <errno.h>
#include <time.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define _XOPEN_SOURCE
#include <unistd.h>
#include <crypt.h>

#include<stdlib.h>
#include <termios.h>

#include<mysql/mysql.h>

#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define BUFSIZE 64

#ifndef INADDR_NONE
#define INADDR_NONE 0xffffffff
#endif


#define sendfinal 2000
#define p_name 1000
#define u_name 1000

struct data
{
	const char *TO;
	const char *source;
	const char *destiny;
	const char *date;
	const char *dept_time;
};

struct reg
{
	const char *TO;
	const char *usname;
	const char *pas;
};

int smtpfun(struct data obj);
int smtpfunreg(struct reg obj);

static char *host = "localhost";  // local database server
static char *user = "root";      //username to connect to mysql server
static char  *pass = "nikhil";
static char *dbname = "test_nik";

unsigned int port = 3306;
static char *sql_socket = NULL;
unsigned int flag =0;

extern int errno;
int errexit(const char *format,...);
int connectTCP(const char *service,const char *host);
int connectsock(const char *service,const char *host,const char *transport);





/*------------------------------------------------------------------------------------
 * connectsock-Allocate and connect socket for TCP
 *------------------------------------------------------------------------------------
*/

int connectsock(const char *service,const char *host,const char *transport)
{

/*
Arguments:
*service   - service associated with desired port
*host      - name of the host to which connection is desired
*transport - name of the transport protocol to use

*/ 

struct sockaddr_in sin;                     //an internet endpoint address
int s,type;                                   //socket descriptor and socket type 

memset(&sin,0,sizeof(sin));  
sin.sin_family=AF_INET;                           //family name
  
sin.sin_port=htons(8000);                                        //port number


inet_pton(AF_INET,"127.0.0.1",&(sin.sin_addr));                         //to convert host name into 32-bit IP address
 
/*
 * to determine the type of socket
 */

if(strcmp(transport,"udp")==0)         
type=SOCK_DGRAM;
else
type=SOCK_STREAM;

/* Allocate a socket */

s=socket(AF_INET,type,0);


if(s<0)
errexit("can't create socket : %s\n",strerror(errno));


if((connect(s,(struct sockaddr *) &sin,sizeof(sin)))<0)        //connect the socket 
errexit("can't connect to %s.%s: %s\n",host,service,strerror(errno));


return s;

}

/*
 * errexit- print and error message and exit
 */


int errexit(const char* format,...)
{
va_list args;

va_start(args,format);
vfprintf(stderr,format,args);
va_end(args);
exit(1);
}


/*------------------------------------------------------------------------
 * connectTCP-connect to a specified TCP service on specified host
 -------------------------------------------------------------------------*/

int connectTCP(const char *service,const char *host)
{
/*
 Arguments:
 *service-service associated with desired port
 *host-name of the host to which connection is desired
 */

return connectsock(service,host,"tcp");
}


/*
 main - TCP client for finding square root by modifying echo service
 */ 

int main(int argc,char *argv[])
{

char *host;
char sendline[100];
char recvline[1000];
char *number;
double result;


char *service="time";                                               //default service port

int s,n;                                                            //socket descriptor

switch(argc)
{
case 1:
host="localhost";

break;

case 2:
host="localhost";

break;

case 3:
number=argv[2];
host=argv[1];
break;

default:printf("Error in taking arguments\n");
exit(1);

}

	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	
		
	conn = mysql_init(NULL);
	if(!(mysql_real_connect(conn,host,user,pass,dbname,port,sql_socket,flag)))   //reutrn zero on success
	{
		fprintf(stderr,"Error: %s [%d]\n", mysql_error(conn),mysql_errno(conn));
		exit(1);
	
	}
int nfds;

s=connectTCP(service,host);                                       //connect the socket

nfds=getdtablesize();

/*
GtkBuilder  *builder;
GtkWidget   *window;
GError *err = NULL;
gtk_init(&argc,&argv);
builder=gtk_builder_new();
if(0==gtk_builder_add_from_file(builder,"user.glade",&err))
 {
   fprintf(stderr,"Error adding build from file. Error: %s\n",err->message);
 }
window=GTK_WIDGET(gtk_builder_get_object(builder,"window1"));
gtk_builder_connect_signals(builder,NULL);

g_object_unref(G_OBJECT(builder));
gtk_widget_show(window);
gtk_main();
*/

system("clear");
l3:printf("\n\n\t\t\t\t\t\t%sWelcome to Airline Reservation System \n\n%s",KYEL,KWHT);

	
	printf("1.Log In\n");
	printf("2.Sign Up\n");
	printf("\n\nEnter your choice\n");
	int choice;
	scanf("%d",&choice);	


	if(choice == 1)
{
	
l1:	printf("\nEnter Username\n");
	char username[u_name];

	char final[sendfinal];
	
	scanf("%s",username);

	  char *password;
	  //password = getpass("Enter Password:\n");
	password = strdup(crypt(getpass("\nEnter Password\n"),"k7"));
			  

   /*	
    printf("Pass:\n");
    struct termios term, term_orig;
    tcgetattr(STDIN_FILENO, &term);
    term_orig = term;
    term.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
 
    char password[p_name];
    scanf("%s", password);
    //printf("Read: %s\n",password);
 
    /* Remember to set back, or your commands won't echo! */
   // tcsetattr(STDIN_FILENO, TCSANOW, &term_orig);
   	



strcpy(final,"");
strcat(final,username);

strcat(final," ");
strcat(final,password);




int input=0;


send(s,final,sendfinal,0);                                  //write the number(send to server) for which the square root needs to be find


while(1)
{
recv(s,recvline,1000,0);                                           //read the message(square root of number from server) from server
//printf("%s\n",recvline);


if(!(strcmp(recvline,"A")))
{

      char flight_customer[200];
		while(1)
		{
			printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t%sUser: %s\n%s",KGRN,username,KWHT);   
	
			printf("\n\n%sEnter your choice\n\n%s",KYEL,KWHT);
			printf("1.View flight details\n");
			printf("2.Add flight\n");
			printf("3.Reschedule flight\n");
			printf("4.Delete flight\n");
			printf("5.View Customer's Booking Details\n");
			printf("6.Log out\n\n\n");
		
		       
			int n;
			scanf("%d",&n);


		
		       if(n==1)
		       {
			char select[1000];
			sprintf(select,"select * from flights where username ='%s'",username);	
			//puts(select);         	


			//printf("%s",recvline);
			mysql_query(conn,select);

			res = mysql_store_result(conn);

			row = mysql_fetch_row(res);
			if(row>0)
			{
			printf("\n%sFlight Details:\n\n%s",KYEL,KWHT);
			printf("%sFlight Num    Flight Name\tDepart City\tDept date\tDeparture\tArrival City\tArrival Date\tArrival       Seats\tPrice\n%s",KBLU,KWHT);
				//while((row = mysql_fetch_row(res))>0)
				//{	
					printf("\n%s\t      %s\t%s\t\t%s\t%s\t%s\t\t%s\t%s\t%s\t%s\n",row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8],row[9],row[11]);
					printf("\n");
				//}	
	
	
			}

			else 
			{
				printf("\n%sThere are no Flights to be displayed\n\n%s",KRED,KWHT);
				break;
			}
                        
			
				
	
			
				while((row = mysql_fetch_row(res))>0)
				{	
					printf("\n%s\t      %s\t%s\t\t%s\t%s\t%s\t\t%s\t%s\t%s\t%s\n",row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8],row[9],row[11]);
					printf("\n");
				}	
	
	
			
			}
			else if(n==2)
			{
				printf("\n\n%sPlease enter the following details to add a flight\n\n%s",KYEL, KWHT);


				

				printf("\n1.Enter the flight number\n");
				char flight_num[100];
				//fgets(flight_num,sizeof(flight_num),stdin);
				scanf("%s",flight_num);
							
				printf("\n2.Enter the flight name\n");
				char flight_name1[500];
				char flight_name2[500];
				scanf("%s%s",flight_name1,flight_name2);
				strcat(flight_name1," ");				
				strcat(flight_name1,flight_name2);
				

				printf("\n3.Enter the departure city\n");
				char dep_city[500];
				scanf("%s",dep_city);
			
				printf("\n4.Enter the departure date in the format yyyy:mm:dd\n");
				char dep_date[100];
				scanf("%s",dep_date);

				printf("\n5.Enter the departure time in the format hh:mm:ss\n");
				char dep_time[100];
				scanf("%s",dep_time);

				printf("\n6.Enter the arrival city\n");
				char arr_city[500];
				scanf("%s",arr_city);
		
				printf("\n7.Enter the arrival date in the format yyyy:mm:dd\n");
				char arivl_date[100];
				scanf("%s",arivl_date);

				printf("\n8.Enter the arrival time in the format hh:mm::ss\n");
				char arr_time[100];
				scanf("%s",arr_time);

				printf("\n9.Enter the number of seats\n");
				int seats;
				scanf("%d",&seats);
					
				printf("\n10.Enter the fare per seat in $\n");
				int price;
				scanf("%d",&price);
				
				
				char select[1000];
				sprintf(select,"insert into flights(flight_num,flight_name,dep_city,dep_time,arrival_city,arrival_time,seats,username,price$,dep_date,arivl_date) values('%s','%s','%s','%s','%s','%s',%d,'%s',%d,'%s','%s')",flight_num,flight_name1,dep_city,dep_time,arr_city,arr_time,seats,username,price,dep_date,arivl_date);	
				//puts(select);	

                                
				//printf("%s",recvline);
				mysql_query(conn,select);

				res = mysql_store_result(conn);
				printf("\n%sSuccessfully added flight : %s\n\n%s",KGRN,flight_num,KWHT);
				
				
				
			}
			else if(n==3)
			{

				char view[1000];
			sprintf(view,"select * from flights where username ='%s'",username);	
			//puts(view);	


			//printf("%s",recvline);
			mysql_query(conn,view);

			res = mysql_store_result(conn);
	
			printf("\n%sFlight Details:\n\n%s",KYEL,KWHT);
			printf("%sFlight Num    Flight Name\tDepart City\tDept date\tDeparture\tArrival City\tArrival Date\tArrival       Seats\tPrice\n%s",KBLU,KWHT);
				while(row = mysql_fetch_row(res))
				{	
					printf("\n%s\t      %s\t%s\t\t%s\t%s\t%s\t\t%s\t%s\t%s\t%s\n",row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8],row[9],row[11]);
					printf("\n");
				}
	
				printf("\n1.Enter the flight number for rescheduling\n");
				char flight_num[100];
				scanf("%s",flight_num);
				
				printf("\n2.Enter the departure date in the format yyyy:mm:dd for rescheduling\n");
				char dep_date[100];
				scanf("%s",dep_date);				
			
				printf("\n3.Enter the departure time in the format hh:mm::ss for rescheduling\n");
				char dep_time[100];
				scanf("%s",dep_time);

				printf("\n4.Enter the arrival date in the format yyyy:mm:dd for rescheduling\n");
				char arrival_date[100];
				scanf("%s",arrival_date);					

				printf("\n5.Enter the arrival time in the format hh:mm::ss for rescheduling\n");
				char arr_time[100];
				scanf("%s",arr_time);
				char select[1000];
				sprintf(select,"update  flights set dep_time='%s', dep_date ='%s',arivl_date = '%s', arrival_time='%s' where flight_num='%s' and username='%s'",dep_time,dep_date,arrival_date,arr_time,flight_num,username);	
				//puts(select);	


				//printf("%s",recvline);
				mysql_query(conn,select);

				res = mysql_store_result(conn);
				printf("\n\n%sSuccessfully updated flight details: %s\n\n%s",flight_num,KGRN,KWHT);
				
				
			}

			else if(n==4)
			{
				char view[1000];
			sprintf(view,"select * from flights where username ='%s'",username);	
			//puts(view);	


			//printf("%s",recvline);
			mysql_query(conn,view);

			res = mysql_store_result(conn);
	
			printf("\n%sFlight Details:\n\n%s",KYEL,KWHT);
			printf("%sFlight Num    Flight Name\tDepart City\tDept date\tDeparture\tArrival City\tArrival Date\tArrival       Seats\tPrice\n%s",KBLU,KWHT);
				while(row = mysql_fetch_row(res))
				{	
					printf("\n%s\t      %s\t%s\t\t%s\t%s\t%s\t\t%s\t%s\t%s\t%s\n",row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8],row[9],row[11]);
					printf("\n");
				}
			
				printf("\n1.Enter the flight number to be deleted\n");
				char flight_num[100];
				scanf("%s",flight_num);
				char select[1000];
				sprintf(select,"Delete  from flights where flight_num ='%s' and username in ('%s')",flight_num,username);	
				//puts(select);	


				//printf("%s",recvline);
				mysql_query(conn,select);

				res = mysql_store_result(conn);
				printf("\n\n%sSuccessfully deleted flight : %s\n\n%s",flight_num,KRED,KWHT);
				
				
			}
			
			else if(n==5)
			{
			        char cust_details[1000];
			sprintf(cust_details,"select * from customers where flight_name in(select flight_name from flights where username='%s')",username);	
			//puts(cust_details);	


			
			mysql_query(conn,cust_details);

			res = mysql_store_result(conn);
	
			printf("\n%sCustomer Details:\n\n%s",KYEL,KWHT);
			printf("%sUsername   Flight Num\tFlight Name\tDepart City\tDept date   Departure   Arrival City\tArrival Date\tArrival     Booking\tTotal\n%s",KBLU,KWHT);
				while(row = mysql_fetch_row(res))
				{	
					printf("\n%s\t   %s\t%s\t%s\t\t%s   %s\t%s\t\t%s\t%s\t%s\t%s\n",row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8],row[9],row[10],row[11]);
					printf("\n");
				}
			}
			else if(n==6)
			{
				printf("\n\n%sSuccessfully logged out\n\n%s",KBLU,KWHT);
        			exit(0);
			}

			
		}
}

else if(!(strcmp(recvline,"C")))
{
      int no_of_seats=0;
	//sem_t mutex;
	//sem_init(&mutex,0,1);
	
		while(1)
		{
			printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t%sUser: %s\n%s",KGRN,username,KWHT); 
	
			printf("\nEnter your choice\n\n");
			printf("1.View Bookings\n");
			printf("2.Book a flight ticket\n");
			printf("3.Delete Bookings\n");
			printf("4.Log out\n\n");
		
		       
			int n;
			scanf("%d",&n);


		
		       if(n==1)
		       {
			char view_details[1000];
			sprintf(view_details,"select * from customers where username ='%s'",username);	
			//puts(view_details);	


			mysql_query(conn,view_details);

			res = mysql_store_result(conn);
			
			row = mysql_fetch_row(res);
				
			if(row>0)
			{
	
			printf("\n%sBooking Details:\n\n%s",KYEL,KWHT);
			printf("%sFlight Num    Flight Name\tDepart City\tDept date\tDeparture\tArrival City\tArrival Date\tArrival       Seats\tPrice\n%s",KBLU,KWHT);
					
					printf("\n%s\t      %s\t%s\t\t%s\t%s\t%s\t\t%s\t%s\t%s\t%s\n",row[2],row[3],row[4],row[5],row[6],row[7],row[8],row[9],row[10],row[11]);
					printf("\n");
					
	
			}
                        else
			{
				printf("\n\n%sYou don't have any bookings\n\n%s",KRED,KWHT);
				break;
			}

			
			while(row = mysql_fetch_row(res))
				{	
					printf("\n%s\t      %s\t%s\t\t%s\t%s\t%s\t\t%s\t%s\t%s\t%s\n",row[2],row[3],row[4],row[5],row[6],row[7],row[8],row[9],row[10],row[11]);
					printf("\n");
				}
			
			}
			else if(n==2)
			{

				//sem_wait(&mutex);
				printf("\n\n%sPlease enter the following details to book a flight ticket\n\n%s",KYEL,KWHT);


				printf("1.Enter your email id\n");
				char mailid[1000];
				//fgets(flight_num,sizeof(flight_num),stdin);
				scanf("%s",mailid);

				printf("\n2.Enter source\n");
				char source[100];
				//fgets(flight_num,sizeof(flight_num),stdin);
				scanf("%s",source);
				
				printf("\n3.Enter the destination\n");
				char destiny[500];
				scanf("%s",destiny);
							
				printf("\n4.Enter From date in the format yyyy:mm:dd \n");
				char from_date[100];
				scanf("%s",from_date);
				
				
				
				char selectb[1000];
				sprintf(selectb,"select * from flights where dep_city ='%s' and arrival_city='%s' and dep_date ='%s'",source,destiny,from_date);	
				//puts(selectb);	
				
				
				
				
				mysql_query(conn,selectb);

				res = mysql_store_result(conn);
	
				//int flag = 0;
				
				row = mysql_fetch_row(res);
								
				if(row > 0)
				{
					printf("\n\nFlight Details:\n\n");
			printf("%sFlight Num    Flight Name\tDepart City\tDept date\tDeparture\tArrival City\tArrival Date\tArrival       Seats\tPrice\n%s",KBLU,KWHT);

					printf("\n%s\t      %s\t%s\t\t%s\t%s\t%s\t\t%s\t%s\t%s\t%s\n",row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8],row[9],row[11]);
					printf("\n");
				

				}

				else
				{
					printf("\n\n%sNo flights available for the entered date\n\n%s",KRED,KWHT);
					break;
				}

				
				while(row = mysql_fetch_row(res))
				{	
					printf("\n%s\t      %s\t%s\t\t%s\t%s\t%s\t\t%s\t%s\t%s\t%s\n",row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8],row[9],row[11]);
					printf("\n");
				}

					
				

				printf("\n5.Enter the flight number to be booked\n");
				char flight_num[100];
				scanf("%s",flight_num);

				

				printf("\n6.Enter number of seats\n");
				int seats_num;
				scanf("%d",&seats_num);
				
				
				
				
				//sem_wait(&mutex);
				char seat_update[1000];
				sprintf(seat_update,"update  flights set seats=seats-%d where flight_num='%s'",seats_num,flight_num);	
				//puts(seat_update);	


				//sem_wait(&mutex);
				mysql_query(conn,seat_update);

				res = mysql_store_result(conn);



				char cust_insert[1000];
				sprintf(cust_insert,"insert into customers(username,flight_num,flight_name,dep_city,dep_time,arivl_city,arrival_time,Bookings,Total,dep_date ,arivl_date)select '%s',flight_num,flight_name,dep_city,dep_time,arrival_city,arrival_time,%d,price$*%d,dep_date,arivl_date from flights where flight_num='%s'",username,seats_num,seats_num,flight_num);	
				//puts(cust_insert);	


				
				mysql_query(conn,cust_insert);

				res = mysql_store_result(conn);
                                
			//sem_post(&mutex);

				char time[1000];
				sprintf(time,"select dep_time from flights where flight_num ='%s'",flight_num);	
				//puts(time);	
				
				
				
				
				mysql_query(conn,time);

				res = mysql_store_result(conn);
	
				//int flag = 0;
				
				row = mysql_fetch_row(res);
								
				char t[100];
				strcpy(t,row[0]);
			
				char mail[1000];
				sprintf(mail,"<%s>",mailid); 
				int x;
				struct data obj;
				
				obj.TO = mail;
				obj.source = source;
				obj.destiny = destiny;
				obj.date = from_date;
				obj.dept_time =  t;
	
	
	
	x = smtpfun(obj);
			printf("\n\n%sTicket booked successfully!.\nBooking confirmation has been sent to your mail.\n\n%s",KGRN,KWHT);	
			}
			else if(n==3)
			{


				char view_details[1000];
			sprintf(view_details,"select * from customers where username ='%s'",username);	
			//puts(view_details);	


			mysql_query(conn,view_details);

			res = mysql_store_result(conn);
			
			row = mysql_fetch_row(res);

			if(row>0)
			{
				printf("\n\n%sBooking Details:\n\n%s",KYEL,KWHT);
			printf("%sFlight Num    Flight Name\tDepart City\tDept date\tDeparture\tArrival City\tArrival Date\tArrival       Seats\tPrice\n%s",KBLU,KWHT);
					
					printf("\n%s\t      %s\t%s\t\t%s\t%s\t%s\t\t%s\t%s\t%s\t%s\n",row[2],row[3],row[4],row[5],row[6],row[7],row[8],row[9],row[10],row[11]);
					printf("\n");
					
				}
			else
			{
				printf("\n\n%sYou don't have any bookings\n%s",KRED,KWHT);
				break;
			}	
	                  
			
				while(row = mysql_fetch_row(res))
				{	
					printf("\n%s\t      %s\t%s\t\t%s\t%s\t%s\t\t%s\t%s\t%s\t%s\n",row[2],row[3],row[4],row[5],row[6],row[7],row[8],row[9],row[10],row[11]);
					printf("\n");
				}	



     printf("\n\n%sPlease enter the flight number and number of tickets to be cancelled\n%s",KYEL,KWHT);

     printf("\n1.Enter the flight number\n");
     char flight_num[100];
     scanf("%s",flight_num);

     printf("\n2.Enter the number of tickets to be cancelled\n");
     int no_tickets;
     scanf("%d",&no_tickets);



				char booking_delete[1000];
				sprintf(booking_delete,"update customers set Total=Total-%d*(Total/Bookings) where flight_num='%s'",no_tickets,flight_num);
				//puts(booking_delete);	


				
				mysql_query(conn,booking_delete);

				res = mysql_store_result(conn);


				char booking_delete1[1000];
				sprintf(booking_delete1,"update customers set Bookings=Bookings-%d where flight_num='%s'",no_tickets,flight_num);
				//puts(booking_delete);	


				
				mysql_query(conn,booking_delete1);

				res = mysql_store_result(conn);


				char delete_update[1000];
				sprintf(delete_update,"update flights set seats=seats+%d where flight_num='%s'",no_tickets,flight_num);
				//puts(delete_update);	


				
				mysql_query(conn,delete_update);

				res = mysql_store_result(conn);
				

				char zero_delete[1000];
				sprintf(zero_delete,"delete from customers where flight_num='%s' and Bookings=0",flight_num);
				//puts(zero_delete);	


				
				mysql_query(conn,zero_delete);

				res = mysql_store_result(conn);

				printf("\n%sTicket booking cancelled successfully\n%s",KYEL,KWHT);
				
			}

			
			else if(n==4)
			{
				printf("\n\n%sSuccessfully logged out\n\n%s",KBLU,KWHT);
        			exit(0);
			}

			
		}
}

else if(!(strcmp(recvline,"S")))
{

      char flight_customer[200];
		while(1)
		{
			printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t%sUser: %s\n%s",KGRN,username,KWHT); 
	
			printf("\nEnter your choice\n\n");
			printf("1.Add an Airline Representative\n");
			printf("2.Display all Airline Representatives\n");
			printf("3.Delete an Airline Representative\n");
			printf("4.View all Airline Representative's Flight Details\n");
			printf("5.View all Customer's Booking Details\n");	
			printf("6.Log out\n\n");
		
		       
			int n;
			scanf("%d",&n);
			
		       if(n==1)
		       {
			char uname[100];
			
			printf("\n1.Enter Airline's Username\n");
			scanf("%s",uname);
                       

			 char *pass;
			    pass = strdup(crypt(getpass("\n2.Enter Airline's Password\n"),"k7"));

			char add_airrep[1000];

			
			sprintf(add_airrep,"insert into air_users values ('%s','%s','A');",uname,pass);	
			//printf("\nQuery: ");			
			//puts(add_airrep);	



			mysql_query(conn,add_airrep);

			res = mysql_store_result(conn);

			printf("\n\n%sAirline Representative successfully added\n%s",KBLU,KWHT);
			}

		       else if(n==2)
		       {
			
			
			//printf("\nAirline Representatives\n");
			


			char disp_airrep[1000];
			sprintf(disp_airrep,"select username , password from air_users where flag = 'A'");	
			//puts(sys_cust);	


			
			mysql_query(conn,disp_airrep);

			res = mysql_store_result(conn);
	
			printf("\n\n\n\t%sAirline Representatives\n%s",KYEL,KWHT);
			printf("\n\t%sUsername\tPassword\n%s",KBLU,KWHT);
				while(row = mysql_fetch_row(res))
				{	
					printf("\n\t%s\t\t%s\n",row[0],row[1]);
					printf("\n");
				}

			
			}
			
		       else if(n==3)
		       {
			char disp_airrep[1000];
			sprintf(disp_airrep,"select username , password from air_users where flag = 'A'");	
			//puts(sys_cust);	


			
			mysql_query(conn,disp_airrep);

			res = mysql_store_result(conn);
	
			printf("\n\n\n\t%sAirline Representatives\n%s",KYEL,KWHT);
			printf("\n\t%sUsername\tPassword\n%s",KBLU,KWHT);
				while(row = mysql_fetch_row(res))
				{	
					printf("\n\t%s\t\t%s\n",row[0],row[1]);
					printf("\n");
				}
                       		
			
			char uname[100];


			printf("\n\n%sEnter Airline Representative's Username to be deleted\n%s",KYEL,KWHT);
			scanf("%s",uname);
			
			char del_airrep[1000];

			
			sprintf(del_airrep,"delete from air_users where username = '%s'",uname);	
			//puts(del_airrep);	



			mysql_query(conn,del_airrep);

			res = mysql_store_result(conn);




			char cust_dele[1000];
			sprintf(cust_dele,"delete from customers where flight_name in(select flight_name from flights where username='%s')",uname);	
			//puts(cust_dele);	


			//printf("%s",recvline);
			mysql_query(conn,cust_dele);

			res = mysql_store_result(conn);
			
				
			
			char air_dele[1000];
			sprintf(air_dele,"delete from flights  where username='%s'",uname);	
			//puts(air_dele);	


			//printf("%s",recvline);
			mysql_query(conn,air_dele);

			res = mysql_store_result(conn);

			printf("\n%sAirline Representative successfully deleted\n%s", KRED, KWHT);
			}
		
		       else if(n==4)
		       {

			char sys_flight[1000];
			sprintf(sys_flight,"select * from flights");	
			puts(sys_flight);	


			//printf("%s",recvline);
			mysql_query(conn,sys_flight);

			res = mysql_store_result(conn);
	
			printf("\n%sFlight Details:\n\n%s",KYEL,KWHT);
			printf("%sFlight Num      Flight Name     Depart City\tDept date\tDeparture\tArrival City\tArrival Date\tArrival       Seats\tPrice\n%s",KBLU,KWHT);
				while(row = mysql_fetch_row(res))
				{	
					printf("\n%s\t\t%s\t%s\t\t%s\t%s\t%s\t\t%s\t%s\t%s\t%s\n",row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8],row[9],row[11]);
					printf("\n");
				}	
		       }

		       else if(n==5)
		       {

			     char sys_cust[1000];
			sprintf(sys_cust,"select * from customers");	
			//puts(sys_cust);	


			
			mysql_query(conn,sys_cust);

			res = mysql_store_result(conn);
	
			printf("\n\n%sCustomer Details:\n\n%s",KYEL,KWHT);
			printf("%sUsername   Flight Num\tFlight Name\tDepart City\tDept date   Departure   Arrival City\tArrival Date\tArrival     Booking\tTotal\n%s",KBLU,KWHT);
				while(row = mysql_fetch_row(res))
				{	
					printf("\n%s\t   %s\t%s\t%s\t\t%s   %s\t%s\t\t%s\t%s\t%s\t%s\n",row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8],row[9],row[10],row[11]);
					printf("\n");
				}

		       }	

			else if(n==6)
			{
				printf("\n%sSuccessfully logged out\n\n%s",KBLU,KWHT);
        			exit(0);
			}
			
	
	
		}
			
			
			
}

else
{
	printf("\n%s%s\n\n",KRED,recvline);
        exit(0);
}

}

}

else if(choice == 2)
{
	               char uname[100];
			char sys_cust[1000];
			
			l2:
			printf("\nEnter Username\n");
			scanf("%s",uname);
			//printf("Enter Password:");
			
					char reuser[1000];
		sprintf(reuser,"select * from air_users where username='%s'",uname);	
			//puts(reuser);	


			
			mysql_query(conn,reuser);

			res = mysql_store_result(conn);
			row=mysql_fetch_row(res);
			
			
	
			
			if(row>0)	
			{
			   printf("\n\n");	
			   printf("%sUsername already existing.\n%s",KRED,KWHT);
		           printf("\n\n");
		 	   //printf("%s\n\n",KWHT);	
			   printf("\n%sPlease select among the options\n\n%s",KYEL,KWHT);
			   printf("1.Try with different username\n");
			   printf("2.Go to home page\n\n");
			   int opt;
			   scanf("%d",&opt);
			   if(opt==1)
				goto l2;
			   else if(opt==2)
                                goto l3;
				
			}	   
			else if(row==0)
			{ 
			   // printf("\nnum of rows: %d\n",x);
			    char *pass;
			    pass = strdup(crypt(getpass("\nEnter Password\n"),"k7"));
			    //printf("\n");	
			 
			    printf("\nEnter your email id\n");
			    char mailidd[1000];
			    scanf("%s",mailidd);
			    

			char add_cust[1000];

			
			sprintf(add_cust,"insert into air_users values ('%s','%s','C');",uname,pass);	
			//puts(add_cust);	



			mysql_query(conn,add_cust);

			res = mysql_store_result(conn);

			char mail[1000];
			sprintf(mail,"<%s>",mailidd);
			int y;
			struct reg obj1;
				
			obj1.TO = mail;
			obj1.usname = uname;
			obj1.pas = pass;

			printf("\n%sSuccessfully Registered!\n%s",KGRN,KWHT);
			printf("\n%sConfirmation mail has been sent to the %s with user credentials\n%s",KGRN,mailidd,KWHT);

			y = smtpfunreg(obj1);

			printf("\n%sPlease re-enter your credentials\n%s",KYEL,KWHT);
			goto l1;
		
			
        		}
			
}

exit(0);
}
