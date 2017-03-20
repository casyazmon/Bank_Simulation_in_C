#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include <time.h>

#define N 200
pthread_mutex_t lock;

int a[100], i, max;
int balance, amount;
	char temp[512] = "                           ";
	char Newamount[512],Oldamount[512];
int j=0;
char table[N][512] = {"                                  "};
void *Deposit(void *pointer);
void *Withdrawal(void *pointer);


char *replace_str(char *str, char *orig, char *rep)
{
    static char buffer[4096];
    char *p;
     
    if(!(p = strstr(str, orig)))
    return str;
     
    strncpy(buffer, str, p-str);
    buffer[p-str] = '\0';
     
    sprintf(buffer+(p-str), "%s%s", rep, p+strlen(orig));
     
    return buffer;
}
 
int main()
{
	char c[1000];
	pthread_t thread1, thread2;
	int thred1, thred2;
	char *msg1="Deposit";
	char *msg2="Withdraw";
	char *account;
	int choice;
	int line_num = 1;
	
	int find_result = 0;

	char str[]="                               ";
	const char s[1] = ":";
   	char *token,*client;
	
	int k=0;

	for (k=0; k<i; k++)
	{
		//table[k] = malloc(200);
	}

	FILE*f=fopen("clients.txt","r");

	if (f == NULL) {
	  fprintf(stderr, "Can't open file clients!\n");
	  exit(1);
	}
	
	i=0;
	while(fscanf(f, "%s", table[i]) != -1) {
		//table[i] = temp;
		//strcpy(table[i], temp);
		printf("v1=\tv2=%s\n",table[i]);
		i+=1;	
	}
	
	fscanf(f,"%[^\n]", c);
	fclose(f);
	f=fopen("clients.txt","a+");

    	printf("Data from the file:\n%s", c);

	printf("What transaction do you want?\n");
	printf("1.Deposit\n");
	printf("2.Withdraw\n");
	printf("reply 1 for deposit and 2 for withdrawal\n");

	scanf("%d",&choice);
//////////////////////////////////////////////////////////////////////////
    	printf("Enter account\n");
	scanf("%s",str);

	while(fgets(temp, 512, f) != NULL) {
		if((strstr(temp, str)) != NULL) {
			printf("A match found on line: %d\n", line_num);
			printf("\n%s\n", temp);
			find_result++;
			j=line_num;
			break;
		}
		line_num++;
		
	}

		max=i;
		
	
			printf("\n%s\n", temp);
			//str=temp; 
	if(find_result == 0) {
		printf("\nSorry, account does not exist.\n");
		exit(0);
	}

	/* get the first token */
  
	token = strtok(temp, s);
   	client =token;
   	/* walk through other tokens */
        while( token != NULL ) 
  	 {
     		 printf( "token %s\n", token );
    		balance = atoi(token);
      		token = strtok(NULL, s);
	
   	}
	printf("%s your balance is %d\n",client,balance);
  
//////////////////////////////////////////////////////////////////////
	if (choice==1)
	{
		thred1 = pthread_create(&thread1, NULL, Deposit, NULL);
		pthread_join(thread1, NULL);
	}
	if (choice==2)
	{	
		thred2 = pthread_create(&thread2, NULL, Withdrawal, NULL);
		pthread_join(thread2, NULL);
	}
	fclose(f);
	return 0;
}
void *Deposit(void *pointer)
{
			FILE*f=fopen("clients.txt","w");

		if (f == NULL) {
		 	 fprintf(stderr, "Can't open file clients!\n");
		 	 exit(1);
		}
		pthread_mutex_lock(&lock);
		printf("Enter amount to deposit\n");
		scanf("%d",&amount);  
		//printf("Transaction number %d\n",i);
		printf("deposit of %d\n",amount);
		sprintf(Oldamount,"%d",balance);
		balance= balance+amount;
		sprintf(Newamount,"%d",balance);
		printf("account status before %s\n",temp);
		sprintf(temp,"%s:%d",temp,balance);
		//table[j]=temp;
		strcpy(table[j-1],temp);
		printf("New Balance is %d\n",balance);
		printf("account status %s\n",temp);
		//sleep(10000);
		 for (i=0; i<max; i++)
		{
			fprintf(f,"%s\n",table[i]);
		}
		fclose(f);
		pthread_mutex_unlock(&lock);
	
}
void *Withdrawal(void *pointer)
{
		FILE*f=fopen("clients.txt","w");
		if (f == NULL) {
		 	 fprintf(stderr, "Can't open file clients!\n");
		 	 exit(1);
		}
	char *msg=(char *)pointer;
	printf("msg : %s\n", msg);
		pthread_mutex_lock(&lock);
		printf("Enter amount to withdraw\n");
		scanf("%d",&amount);  
		//printf("Transaction number %d\n",i);
		printf("withdrawal of %d\n",amount);
		sprintf(Oldamount,"%d",balance);
		balance= balance-amount;
		sprintf(Newamount,"%d",balance);
		printf("account status before %s",temp);
		sprintf(temp,"%s:%d",temp,balance);
		//table[j]=temp;
		strcpy(table[j-1],temp);
		printf("New Balance is %d\n",balance);
		printf("account status %s\n",table[j]);
		//sleep(10000);
		 for (i=0; i<max; i++)
		{
			fprintf(f,"%s\n",table[i]);
		}
		fclose(f);
		pthread_mutex_unlock(&lock);


}
