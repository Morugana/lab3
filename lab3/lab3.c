/*	TE2101 Programming Methodology Lab 3	*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//Declare typedef stuct node, no need to repeat struct declaration.
typedef struct
{
	int index;
	char *colour; //always use pointer for char due to unknown string array size
	int memory;
	int degree;
}node;

#define ROWS 20
#define COLUMNS 20

//Declare GLOBAL variables
int globalmatrix[ROWS][COLUMNS] = { 0 };
int globaledge[ROWS] = { 0 };
node globalNodeArray[ROWS] = { 0 };

/*Declare function prototype. Call LOCAL variables within.*/
void random_matrix(int localmatrix[ROWS][COLUMNS]);
void display_matrix(int localmatrix[ROWS][COLUMNS]);
void spacebar(void);
void isolated(int localmatrix[ROWS][COLUMNS]);
void nodeEdge(int localmatrix[ROWS][COLUMNS], node localnodematrix[ROWS]);
void nodeInfo(node localnodematrix[ROWS]);
void onehopNode(int localmatrix[ROWS][COLUMNS], node localnodematrix[ROWS], int k);
void nodeDetail(node localnodematrix[ROWS], int k);
void nodeQuery(int localmatrix[ROWS][COLUMNS], node localnodematrix[ROWS]);
void continue_quit(int localmatrix[ROWS][COLUMNS], node localnodematrix[ROWS]);


/*	Call function with GLOBAL variables in MAIN.
Able to use the function repeatedly with different GLOBAL variables.	*/
int main()
{
	random_matrix(globalmatrix);
	isolated(globalmatrix);
	display_matrix(globalmatrix);
	spacebar();
	nodeInfo(globalNodeArray);
	spacebar();
	nodeEdge(globalmatrix, globalNodeArray);
	spacebar();
	nodeQuery(globalmatrix, globalNodeArray);
	spacebar();
	continue_quit(globalmatrix, globalNodeArray);

	getchar();
	getchar();
	return 0;
}

//Generate random matrix array
void random_matrix(int localmatrix[ROWS][COLUMNS])
{

	int i, j;

	//Initialise matrix array to zero
	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLUMNS; j++)
		{
			localmatrix[i][j] = 0;
		}
	}

	srand((unsigned int)time(NULL));

	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLUMNS; j++)
		{
			/*	Use random (MOD2 + 0) to generate elements with the value zero or one.
			(+0) for lower limit	*/
			localmatrix[i][j] = rand() % 2 + 0;

			//Mirror upper triangular matrix to lower triangular matrix to create symmetry
			if (i > j)
			{
				localmatrix[i][j] = localmatrix[j][i];
			}

			//Make all diagonal entries to zero
			if (i == j)
			{
				localmatrix[i][j] = 0;
			}
		}
	}


}

//Display the generated random matrix
void display_matrix(int localmatrix[ROWS][COLUMNS])
{

	int i, j;

	printf("Welcome to my Graph Processing tool!!!\n\n");
	printf("The adjacency matrix for graph G\n");

	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLUMNS; j++)
		{
			printf("%d ", localmatrix[i][j]);
		}
		printf("\n");
	}
}

//Create space and bar
void spacebar(void)
{
	printf("\n");
	printf("============================================\n");
	printf("\n");
}

//Account for isolated nodes
void isolated(int localmatrix[ROWS][COLUMNS])
{

	int i, j, isolatedCount;
	int randomCount = 0;

	for (i = 0; i < ROWS; i++)
	{
		isolatedCount = 0;

		for (j = 0; j < COLUMNS; j++)
		{
			//Condition to detect isolated node
			if (localmatrix[i][j] == 0)
			{
				isolatedCount++;
			}

		}

		/*	When isolated node is detected, randomCount generates a random node [0,19] to connect to.
		if randomCount equals to itself, randomCount will random and add 1 and modulus to prevent
		array overflow	*/
		if (isolatedCount == ROWS)
		{
			randomCount = rand() % ROWS;
			randomCount = (randomCount == i) ? ((randomCount + 1) % ROWS) : randomCount;
			localmatrix[i][randomCount] = 1;
			localmatrix[randomCount][i] = 1;
		}
	}

}

//List of node information
void nodeInfo(node localnodematrix[ROWS])
{
	int i, j = 0;
	int randomColour = 0;
	int randomMemory[3] = { 20, 60, 100 };
	int randomMemoryCount = 0;

	printf("Node Structure Information");
	printf("\n\n");
	printf("Index  Colour  Memory(Gb)");
	printf("\n");

	srand((unsigned int)time(NULL));

	for (i = 0; i < ROWS; i++) 
	{
		//assign index using j count
		localnodematrix[i].index = j++;

		//formatting to the right, padded blank spaces by x values: %-x
		printf("%-6d ", localnodematrix[i].index);

		//assign random colour of node using MOD3 
		randomColour = rand() % 3 + 0;

		if (randomColour == 0)
		{
			localnodematrix[i].colour = "Red";
		}
		else if (randomColour == 1)
		{
			localnodematrix[i].colour = "Blue";
		}
		else 
		{
			localnodematrix[i].colour = "Green";
		}
		//formatting to the right, padded blank spaces by x values: %-x
		printf("%-7s ", localnodematrix[i].colour);

		//assign random memory using randomMemory array declared using MOD3 
		randomMemoryCount = rand() % 3 + 0;
		localnodematrix[i].memory = randomMemory[randomMemoryCount];
		printf("%d ", localnodematrix[i].memory);
		printf("\n");

	}
}

//List of Node Edges using one-hop matrix function
void nodeEdge(int localmatrix[ROWS][COLUMNS], node localnodematrix[ROWS])
{
	int i, j;
	int edgeCount = 0;

	printf("Number of Edges for each node\n");

	for (i = 0; i < ROWS; i++)
	{
		//Print the index of all nodes
		printf("Node %d: ", i);

		for (j = 0; j < COLUMNS; j++)
		{
			//Condition to detect one-hop and print the one-hop neighbours
			if (localmatrix[i][j] == 1)
			{
				edgeCount++;
			}
		}
		localnodematrix[i].degree = edgeCount;
		edgeCount = 0;
		printf("%d ", localnodematrix[i].degree);
		printf("\n");
	}
}

//List of one-hop nodes
void onehopNode(int localmatrix[ROWS][COLUMNS], node localnodematrix[ROWS], int k)
{
	int j;
	int totalmemory = localnodematrix[k].memory;

	printf("List of one hop neighbours for Node %d:\n", k);

	printf("Index  Colour  \n");
	for (j = 0; j < ROWS; j++)
	{
		//Condition to detect one-hop with user input k
		if (globalmatrix[k][j] == 1)
		{
			//formatting to the right, padded blank spaces by x values: %-x
			printf("%-6d ", j);
			printf("%s ", localnodematrix[j].colour);
			printf("\n");

			//totalmemory = totalmemory + [onehop nodes memory (increment by j)]
			totalmemory = totalmemory + localnodematrix[j].memory;
		}
	}

	printf("\n");
	printf("Total available memory(Gb): %d", totalmemory);
}

//Print out complete details for Node K 
void nodeDetail (node localnodematrix[ROWS], int k)
{
	//formatting to the right, padded blank spaces by x values: %-x
	printf("Index  Colour  Memory(Gb)  Degree\n");
	printf("%-6d ", localnodematrix[k].index); 
	printf("%-7s ", localnodematrix[k].colour);
	printf("%-11d ", localnodematrix[k].memory);
	printf("%d ", localnodematrix[k].degree);
	printf("\n\n");
}

//User input to query Node K
void nodeQuery(int localmatrix[ROWS][COLUMNS], node localnodematrix[ROWS])
{
	int k = 0; 

	printf("Enter Node K: <0 to %d>\n", ROWS - 1);
	scanf_s("%d", &k);

	//allows user input between [0,19] for int k.
	if (k >= 0 && k < ROWS) 
	{
		printf("\n");
		spacebar();
		nodeDetail(localnodematrix, k);
		spacebar();
		onehopNode(localmatrix, localnodematrix, k);
		printf("\n");
	}
	else
	{	
		printf("\n");
		printf("Invalid entry!");
		printf("\n\n");
		nodeQuery(globalmatrix, globalNodeArray);
	}
}

//Continue or Quit the program
void continue_quit(int localmatrix[ROWS][COLUMNS], node localnodematrix[ROWS])
{
	char retry;

	printf("Do you wish to try again? <Type Y to continue or Q to quit>");
	printf("\n");

	/*	"blank" in the format string tells scanf to skip leading whitespace,
	"1" read single character	*/
	scanf_s(" %c", &retry, 1);
	printf("\n");

	//OR logic allows the user to input both upper and lower case of the letter. 
	if (retry == 'y' || retry == 'Y')
	{
		nodeQuery(globalmatrix, globalNodeArray);
		spacebar();
		continue_quit(globalmatrix, globalNodeArray);
	}
	else if (retry == 'q' || retry == 'Q')
	{
		printf("Thanks and Good Bye.");
	}
	else
	{
		continue_quit(globalmatrix, globalNodeArray);
	}
}