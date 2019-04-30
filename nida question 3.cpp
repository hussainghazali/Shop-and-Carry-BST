void QUESTION_3()
{
/*
Problem 3- Simulation of Queuing Systems
The Shop-n-Carry (SC) is a big chain of departmental stores. The SC would like to improve its
customer services. There has been a complained for some period that the waiting time to avail
Point-of-Sale terminal services is unbearable for some areas in stores. SC is planning to improve
the services by means of installing more POS terminals to those stores, which are in heavy use,
and customers have to wait for making payments. You have been hired, as a consultant by the SC
president to determine whether this idea is feasible or not. The management has decided that if the
average waiting time of a user at a POS is greater than 3 minutes to get their services. They will
install one more POS terminal machine. It is provided that the arrival rate of POS customer is
anytime within the opening hours and the average service time is between 3 to 8 minutes. The POS
is operational 18 X 7. Your job is to run a simulation program for SC POS for 18 hours, and
calculate the average waiting time for customers on hourly basis. Identify the busy hours. Use the
least count of the clock as discrete unit of minutes. Put the entire statistic in the output file which
is as follows:
? Number of customers
? Average waiting time (for each hour – in a separate line)
? Average Customers (for each hour – in a separate line)
? POS utilization time (Average Service Time) 
*/
}


#include<iostream>
#include <time.h>   
#include <stdlib.h> 
#include <conio.h>

using namespace std;   

#define MAXIMUM_INTERVAL8
#define MAXIMUM_CUSTOMER 10001

class  Shop_n_Carry
{
	public:
	int Waiting_Time; 
     Shop_n_Carry *prev; 
	 Shop_n_Carry *next; 
}; 

class tnode
{
	public:
	int Customer_Number; 
	tnode *left; 
	tnode *right; 
}; 

Shop_n_Carry *head, *tail; 
int Data_Count; 
int Maximum_Number = 0; 
int Maximum_Time; 
int Maximum_Waiting_Time = 0; 
tnode *base; 
bool Customer_Number[10001];
int Current_Customer_Number; 


void InitQueue()
{
	head = ( Shop_n_Carry *)malloc(sizeof( Shop_n_Carry)); 
	tail = ( Shop_n_Carry *)malloc(sizeof( Shop_n_Carry)); 
	head->prev = head; 
	head->next = tail; 
	tail->prev = head; 
	tail->next = tail; 

	Data_Count = 0; 
}

int Enqueue(int value)
{
	 Shop_n_Carry *newNode;

	if((newNode = ( Shop_n_Carry *)malloc(sizeof( Shop_n_Carry))) == NULL) 
	{
		cout<<"\nOut of memory."; 
		return -1;
	}

	newNode->Waiting_Time = value; 
	tail->prev->next = newNode;
	newNode->prev = tail->prev; 
	tail->prev = newNode; 
	newNode->next = tail; 

	Data_Count++; 

	return value;
}

int Dequeue() 
{
	 Shop_n_Carry *delNode; 
	delNode = head->next; 

	if(delNode == tail) 
	{
		cout<<"\n No Customers ";
		return -1;
	}

	int i = delNode->Waiting_Time;
	head->next = delNode->next; 
	delNode->next->prev = head; 
	free(delNode); 

	Data_Count--; 

}

void Clear_Queue() 
{
	 Shop_n_Carry *node1; 
	 Shop_n_Carry *node2; 
	node1 = head->next; 

	while(node1 != tail)
	{  
		node2 = node1;
		node1 = node1->next;
		free(node2); 
	}

	head->next = tail; 
	tail->prev = head;
}

void Add_Waiting_Time_To_Queue()
{
	 Shop_n_Carry *curNode; 
	curNode = head->next; 

	while(curNode != tail) 
	{
		curNode->Waiting_Time++; 
		curNode = curNode->next; 
	}
}

void Init_Tree(int initValue)
{
	base = (tnode *)malloc(sizeof( Shop_n_Carry));
	base->Customer_Number = initValue; 
	base->left = NULL; 
	base->right = NULL; 
}

tnode* Insert_To_Tree(int value)
{
	tnode *node1, *node2; 
	node1 = base;
	node2 = base->left; 

	while(node2 != NULL) 
	{
		node1 = node2; 

		if(value < node2->Customer_Number) 
			node2 = node2->left; 
		else
			node2 = node2->right; 
	} 

	if((node2 = (tnode *)malloc(sizeof(tnode))) == NULL) 
		return NULL;

	node2->Customer_Number = value; 
	node2->left = NULL; 
	node2->right = NULL;

	if(value < node1->Customer_Number || node1 == base) 
		node1->left = node2; 
	else
		node1->right = node2; 

	return node2; 
	
}

int Get_New_Customer_Number()
{
	int number;
   while(1) 
	{
		 number = rand() % MAXIMUM_CUSTOMER; 

		if(Customer_Number[number] == true) 
		{
			Customer_Number[number] = false; 
			break; 
		}
	}

	return number; 
}

void Display_Tree(tnode *node, int totalSpace, int depth)
{
	if(depth >= 5) 
		return;

	if(node == NULL && depth < 5) 
		cout<<"\n"; 

	if(node != NULL) 
	{
		Display_Tree(node->right, totalSpace+5, depth + 1); 

		for(int i = 0; i < totalSpace; i++) 
			cout<<"  ";

		printf("%5d\n", node->Customer_Number);

		Display_Tree(node->left, totalSpace+5, depth + 1); 
	}
}
int main(int argc, char **argv) 
{
	int intervalMaxArrive = 8;
	int intervalMaxService = 8; 
	int simulatePeriod = 1080; 

	if (argc == 8)
	{
		intervalMaxArrive = atoi(argv[1]);
		intervalMaxService = atoi(argv[2]);
		simulatePeriod = atoi(argv[3]);
	}

	time_t t; 
	srand(time(&t)); 
	int count = 0; 
    int Waiting_Time;
	int arrivalTime; 
	int serviceTime; 
	
	InitQueue();
	Init_Tree(0); 
	for(int i = 0; i < MAXIMUM_CUSTOMER; i++)
		Customer_Number[i] = true;

	arrivalTime = rand() % intervalMaxArrive + 1;
	count += arrivalTime; 

	Current_Customer_Number = Get_New_Customer_Number(); 

	Insert_To_Tree(Current_Customer_Number); 
	Customer_Number[Current_Customer_Number] = false; 

	serviceTime = rand() % intervalMaxService + 1; 
	arrivalTime = rand() % intervalMaxArrive + 1; 
	
	while(count < simulatePeriod) 
	{
		if(Maximum_Number < Data_Count)
		{
			Maximum_Number = Data_Count; 
			Maximum_Time = count; 
		}

		arrivalTime--;

		if(arrivalTime == 0) 
		{
			cout<<"\n new customer comes in \n"; 
			Enqueue(0); 
			Insert_To_Tree(Get_New_Customer_Number()); 
			arrivalTime = rand() % intervalMaxArrive + 1; 
		}

		serviceTime--; 

		if(serviceTime == 0) 
		{
			cout<<"\n old customer comes out \n";
			Waiting_Time = Dequeue(); 
			serviceTime = rand() % intervalMaxService + 1;

			if(Maximum_Waiting_Time < Waiting_Time) 
			{
				Maximum_Waiting_Time = Waiting_Time; 
			}
		}

		Add_Waiting_Time_To_Queue(); 

		count++; 

		cout<<" \n Number of Customers in the line : "<< Data_Count << " \n Current Time : " << count << " minutes "<<endl; 
	}

	cout<<" \n\nMaximum Number : "<< Maximum_Number << " customers at " <<Maximum_Time<<" minute "<<endl; 
	cout<<" \n\nMaximum Waiting Time : "<< Maximum_Waiting_Time << " minuts "<<endl; 
	cout<<"\n\n";

	Display_Tree(base->left, 0, 0); 

	Clear_Queue(); 
	
 cout<<"\n\n*********************************************************************"<<endl;
 cout<<"\n\nHUSSAIN GHAZALI \n17K-3900 \nSECTION-(A)";
 }
