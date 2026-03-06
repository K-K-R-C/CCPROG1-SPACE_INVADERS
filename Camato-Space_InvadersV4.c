/******************************************************************
This is to certify that this project is my own work, based on my personal efforts
in studying and applying the concepts learned. I have constructed the functions
and their respective algorithms and corresponding code by myself. 
The program was run, tested, and debugged by myown efforts. 
I further certify that I have not copied in part or whole or
otherwise plagiarized the work of other students and/or persons.
Karl Kristoffer R. Camato, DLSU ID# 12411809
******************************************************************/
/*
Description: This program is a simplified version of the game, "Space Invaders", that gives
the player 3 choices, but the gameplay is different where the player has to instead calculate
the amount of shots it takes to kill all aliens on the screen.
Programmed by: Karl Kristoffer R. Camato
Last modified: Nov. 27 2024
Version 4.0
*/

//Include all needed header files
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Define all needed constants
#define FACEHUGGER "//(~O~)\\\\ "
#define CHESTBUSTER "\\\\<^o^>// "
#define XENOMORPH "(((((((O,,,o) "
#define QUEEN ")))O***O((( "

#define PLAYERLIVES 3
#define FLIFE 1
#define CLIFE 2
#define XLIFE 4.2
#define QLIFE 7.3

#define TOTAL_LEVELS 10

#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define RED "\033[0;31m"
#define PURPLE "\033[0;35m"
#define RESET "\033[0m"

//Function prototypes
void displayDivider();

void displayWelcomePage();
void startGame(int* playerID, int* score);
void displayHighScores(int *p1, int *p2, int *p3, int *p4, int *p5, int *p1S, int *p2S, int *p3S, int *p4S, int *p5S);
void sortHighScores(int playerID, int score, int *p1, int *p2, int *p3, int *p4, int *p5, int *p1S, int *p2S, int *p3S, int *p4S, int *p5S);
void displayQuit();

int validPlayerID(int currentPlayerID);
void displayGuide();
void displayLevelHeader(int level, int lives, int score);
void displayAlienComputation(int nFCount, int nCCount, int nXCount, int nQCount);

int randomizeNum();
void numAliens(int level, int *nFCount, int *nCCount, int *nXCount, int *nQCount);
void displayAliens(int nFCount, int nCCount, int nXCount, int nQCount);
void computeAlienLives(int nFCount, int nCCount, int nXCount, int nQCount, float *correctFAnswer, float *correctCAnswer, float *correctxanswer, float *correctQanswer);
void clearScreen();

int main()
{
	//Create ID and score variables for future top 5 players
	int p1 = 10000000, p1S = 0;
	int p2 = 20000000, p2S = 0;
	int p3 = 30000000, p3S = 0;
	int p4 = 40000000, p4S = 0;
	int p5 = 50000000, p5S = 0;

	//Create variables needed for player's gameplay
	int option;
	int playerID;
	int score = 0;

	do
	{
		displayWelcomePage();
		scanf("%d", &option);
		while(getchar() != '\n');

		switch(option)
		{
			case 1:
				startGame(&playerID, &score); //Allows user to start playing the game
				sortHighScores(playerID, score, &p1, &p2, &p3, &p4, &p5, &p1S, &p2S, &p3S, &p4S, &p5S); //Stores and sorts highscores after game
				break;

			case 2:
				displayHighScores(&p1, &p2, &p3, &p4, &p5, &p1S, &p2S, &p3S, &p4S, &p5S);
				break;

			case 3:
				displayQuit();
				break;

			default:
				printf("Please pick from the given choices (1, 2, or 3)\n");
				break;
		}
	} while (option != 3); //Keep asking the user until they choose option 3 (quit)

	return 0;
}

/*
Description: This function prints a Divider
Precondition: None
@param <None>
@return <None>
*/
void displayDivider()
{
	printf("*------------------------------------------------------------------------------*\n");
}


/*
Description: This function prints the welcome page for players
Precondition: None
@param <None>
@return <None>
*/
void displayWelcomePage()
{
	displayDivider();
	printf("\n%47s\n", "SPACE INVADERS");
	printf("\n%44s\n\n", "C Version");
	displayDivider();

	printf("\n%44s\n%50s\n%44s\n\n", "PLAY (Press 1)", "HIGH SCORES(Press 2)", "QUIT (Press 3)");
}


/*
Description: This function allows the player to play the game
Precondition: option must equal 1 before being called
@Param <*playerID> <will be used to update playerID variable in Main>
@Param <*score> <will be used to update score variable in Main>
@return <None>
*/
void startGame(int *playerID, int *score)
{
	//declare and initialize needed variables for gameplay
	int currentPlayerID;
	int level = 0;
	int lives = PLAYERLIVES;
	int currentScore = 0;

	int nFCount;
	int nCCount;
	int nXCount;
	int nQCount;

	float correctFAnswer, correctCAnswer, correctXAnswer, correctQAnswer;
	float playerFAnswer, playerCAnswer, playerXAnswer, playerQAnswer;

	int menuNum = 0;

	//Keep asking user for ID if it is invalid
	do
	{
		printf("What is your player ID?: ");
		scanf("%d", &currentPlayerID);
		while(getchar() != '\n');
	} while (!validPlayerID(currentPlayerID));

	//Start game
	for (level = 1; level <= TOTAL_LEVELS && lives > 0; level++)
	{
    	nFCount = 0;
    	nCCount = 0;
    	nXCount = 0;
    	nQCount = 0;
    	
        correctFAnswer = 0;
        correctCAnswer = 0;
        correctXAnswer = 0;
        correctQAnswer = 0;
        
        playerFAnswer = 0;
        playerCAnswer = 0;
        playerXAnswer = 0;
        playerQAnswer = 0;
        
		//Display level guide and information that seperates levels
		displayGuide();
		displayLevelHeader(level, lives, currentScore);

		//Create random number of aliens and display them
		numAliens(level, &nFCount, &nCCount, &nXCount, &nQCount);
		displayAliens(nFCount, nCCount, nXCount, nQCount);

		//Ask for player's answer for how many times to shoot all aliens
		printf("Shoot Facehuggers how many times?: ");
		scanf("%f", &playerFAnswer);
		while(getchar() != '\n');

		if (nCCount > 0)
		{
			printf("Shoot Chestbusters how many times?: ");
			scanf("%f", &playerCAnswer);
			while(getchar() != '\n');
		}

		if (nXCount > 0)
		{
			printf("Shoot Xenomorphs how many times?: ");
			scanf("%f", &playerXAnswer);
			while(getchar() != '\n');
		}

		if (nQCount > 0)
		{
			printf("Shoot Queens how many times?: ");
			scanf("%f", &playerQAnswer);
			while(getchar() != '\n');
		}


		//Compute for the correct answers for all alien types
		computeAlienLives(nFCount, nCCount, nXCount, nQCount, &correctFAnswer, &correctCAnswer, &correctXAnswer, &correctQAnswer);

		if (playerFAnswer == correctFAnswer && playerCAnswer == correctCAnswer && playerXAnswer == correctXAnswer && playerQAnswer == correctQAnswer)
		{
			printf("YOU WIN THIS LEVEL\n");
			currentScore++;
		}
		
		if (playerFAnswer != correctFAnswer)
		{
			printf("WRONG ANSWER FOR FACEHUGGERS\n");
			lives--;
		}

		if (playerCAnswer != correctCAnswer)
		{
			printf("WRONG ANSWER FOR CHESTBUSTERS\n");
			lives--;
		}
		
		if (playerXAnswer != correctXAnswer)
		{
			printf("WRONG ANSWER FOR XENOMORPHS\n");
			lives--;
		}

		if (playerQAnswer != correctQAnswer)
		{
			printf("WRONG ANSWER FOR QUEENS\n");
			lives--;
		}
		
		displayAlienComputation(nFCount, nCCount, nXCount, nQCount);
	}

	//End of the game (life == 0 or all levels finished)
	printf("GAME OVER\n SCORE: %d\n", currentScore);

	//Take the value of player ID and currentScore (using pointers)
	*score = currentScore;
	*playerID = currentPlayerID;

	//Ask player to return to the main menu;
	do
	{
		printf("Go back to Main Menu (Press 1)");
		scanf("%d", &menuNum);
		while(getchar() != '\n');
	} while (menuNum != 1);

	clearScreen();
}


/*
Description: This function prints the highscores for top 5 players
Precondition: Option must equal 2 before being called
@Param <*p1> <is the top player ID>
@Param <*p2> <is the second top player ID>
@Param <*p3> <is the third top player ID>
@Param <*p4> <is the fourth top player ID>
@Param <*p5> <is the fifth top player ID>

@Param <*p1S> <is the top player's score>
@Param <*p2S> <is the second top player's score>
@Param <*p3S> <is the third top player's score>
@Param <*p4S> <is the fourth top player's score>
@Param <*p5S> <is the fifth top player's score>
*/
void displayHighScores(int *p1, int *p2, int *p3, int *p4, int *p5, int *p1S, int *p2S, int *p3S, int *p4S, int *p5S)
{
	//Compare and compute for highest score

	//Display the highscores
	displayDivider();

	printf("                                  HIGH SCORES\n\n");
	printf("                       1st: %d                      %d\n", *p1, *p1S);
	printf("                       2nd: %d                      %d\n", *p2, *p2S);
	printf("                       3rd: %d                      %d\n", *p3, *p3S);
	printf("                       4th: %d                      %d\n", *p4, *p4S);
	printf("                       5th: %d                      %d\n", *p5, *p5S);

	displayDivider();
}

/*
Description: This function prints the highscores for top 5 players
Precondition: Parameters must be non-negative
@Param <playerID> <is the player's ID>
@Param <score> <is the player's score>

@Param <*p1> <is the top player ID>
@Param <*p2> <is the second top player ID>
@Param <*p3> <is the third top player ID>
@Param <*p4> <is the fourth top player ID>
@Param <*p5> <is the fifth top player ID>

@Param <*p1S> <is the top player's score>
@Param <*p2S> <is the second top player's score>
@Param <*p3S> <is the third top player's score>
@Param <*p4S> <is the fourth top player's score>
@Param <*p5S> <is the fifth top player's score>

@return <None>
*/
void sortHighScores(int playerID, int score, int *p1, int *p2, int *p3, int *p4, int *p5, int *p1S, int *p2S, int *p3S, int *p4S, int *p5S)
{
	if ((score > *p1S && score > *p2S && score > *p3S && score > *p4S && score > *p5S) && playerID != *p1 && playerID != *p2 && playerID != *p3 && playerID != *p4 && playerID != *p5)
	{
		*p5 = *p4;
		*p5S = *p4S;

		*p4 = *p3;
		*p4S = *p3S;

		*p3 = *p2;
		*p3S = *p2S;

		*p2 = *p1;
		*p2S = *p1S;

		*p1 = playerID;
		*p1S = score;
	}
	else if ((score > *p2S && score > *p3S && score > *p4S && score > *p5S) && playerID != *p1 && playerID != *p2 && playerID != *p3 && playerID != *p4 && playerID != *p5)
	{
		*p5 = *p4;
		*p5S = *p4S;

		*p4 = *p3;
		*p4S = *p3S;

		*p3 = *p2;
		*p3S = *p2S;

		*p2 = playerID;
		*p2S = score;
	}
	else if ((score > *p3S && score > *p4S && score > *p5S) && playerID != *p1 && playerID != *p2 && playerID != *p3 && playerID != *p4 && playerID != *p5)
	{
		*p5 = *p4;
		*p5S = *p4S;

		*p4 = *p3;
		*p4S = *p3S;

		*p3 = playerID;
		*p3S = score;
	}
	else if ((score > *p4S && score > *p5S) && playerID != *p1 && playerID != *p2 && playerID != *p3 && playerID != *p4 && playerID != *p5)
	{
		*p5 = *p4;
		*p5S = *p4S;

		*p4 = playerID;
		*p4S = score;
	}
	else if ((score > *p5S) && playerID != *p1 && playerID != *p2 && playerID != *p3 && playerID != *p4 && playerID != *p5)
	{
		*p5 = playerID;
		*p5S = score;
	}
}

/*
Description: This function prints the quit page for players
Precondition: Option must equal 3 before being called
@Param <None>
@return <None>
*/
void displayQuit()
{
	displayDivider();
	printf("\n\n\n\n\n\n\n\n\n\n");
	printf("                                 >*<GAME OVER>*<");
	printf("\n\n\n\n\n\n\n\n\n\n");
	displayDivider();
}


/*
Description: This function displays the alien guide for players
Precondition: None
@Param <None>
@return <None>
*/
void displayGuide()
{
	displayDivider();

	printf("Alien types guide: \n");
	printf("Facehugger: %s (Lives to shoot: %d)\n", FACEHUGGER, FLIFE);
	printf("Chestbuster: %s (Lives to shoot: %d)\n", CHESTBUSTER, CLIFE);
	printf("Xenomorph: %s (Lives to shoot: %.1f)\n", XENOMORPH, XLIFE);
	printf("Queen: %s (Lives to shoot: %.1f)\n", QUEEN, QLIFE);
}


/*
Description: This function displays the header for the level
Precondition: Parameters are non-negative
@param <level> <is the current level of the player>
@param <lives> <is the current lives of the player>
@param <score> <is the current score of the player>
@return <None>
*/
void displayLevelHeader(int level, int lives, int score)
{
	displayDivider();

	printf("Level: %d | Lives: %d | Score: %d\n", level, lives, score);
}

/*
Description: This function displays the computations for each alien type for the level
Precondition: parameters are non-negative
@param <nFCount> <is the amount of Facehuggers to be calculated>
@param <nCCount> <is the amount of Chestbusters to be calculated>
@param <nXCount> <is the amount of Xenomorphs to be calculated>
@param <nQCount> <is the amount of Queens to be calculated>
@return <None>
*/
void displayAlienComputation(int nFCount, int nCCount, int nXCount, int nQCount)
{
	displayDivider();

	printf("Alien computation: \n");
	printf("Facehuggers: %d * %d = %d\n", nFCount, FLIFE, nFCount * FLIFE);

	if (nCCount > 0)
	{
		printf("Chestbusters: %d * %d = %d\n", nCCount, CLIFE, nCCount * CLIFE);
	}

	if (nXCount > 0)
	{
		printf("Xenomorphs: %d * %.1f = %.1f\n", nXCount, XLIFE, nXCount * XLIFE);
	}

	if (nQCount > 0)
	{
		printf("Queens: %d * %.1f = %.1f\n", nQCount, QLIFE, nQCount * QLIFE);
	}
}


/*
Description: This function checks if playerID is valid or not
Precondition: playerID must be an integer
@Param <playerID> <is the player's ID>
@return <1 or 0 (if player's ID is valid or not)>
*/
int validPlayerID(int currentPlayerID)
{
    int isValid = 0;
    
    //Checks if player id is 8 digits
	if (currentPlayerID >= 10000000 && currentPlayerID <= 99999999)
	{
	    isValid++;
	}

	return isValid;
}


/*
Description: This function produces a random number from 1-5
to be used for iterating aliens
Precondition: None
@param <None> 
@return <random number from 1-5>
*/
int randomizeNum()
{
	int random = 0;
	srand(time(NULL));

	random = rand() % (5 - 1 + 1) + 1; //Formula: rand % (max - min + 1) + min

	return random;
}


/*
Description: This function creates the amount of aliens to be displayed
Precondition: Parameters are non-negative
@param <level> <is the current level number of the player>
@param <*nFCount> <is the amount of Facehuggers to be displayed>
@param <*nCCount> <is the amount of Chestbusters to be displayed>
@param <*nXCount> <is the amount of Xenomorphs to be displayed>
@param <*nQCount> <is the amount of Queens to be displayed>
@return <None>
*/
void numAliens(int level, int *nFCount, int *nCCount, int *nXCount, int *nQCount)
{
	*nFCount = randomizeNum();

	if (level != 2 && level != 5)
	{
		*nCCount = randomizeNum();
	}

	if (level % 2 == 0)
	{
		*nXCount = randomizeNum();
	}

	if (level == 10)
	{
		*nQCount = randomizeNum();	
	}
}


/*
Description: This function displays the aliens for the level
Precondition: parameters are non-negative
@param <nFCount> <is the amount of Facehuggers to be displayed>
@param <nCCount> <is the amount of Chestbusters to be displayed>
@param <nXCount> <is the amount of Xenomorphs to be displayed>
@param <nQCount> <is the amount of Queens to be displayed>
@return <None>
*/
void displayAliens(int nFCount, int nCCount, int nXCount, int nQCount)
{
	int i;

	displayDivider();

	for (i = 0; i < nFCount; i++)
	{
		printf(GREEN FACEHUGGER RESET);
	}

	for (i = 0; i < nCCount; i++)
	{
		printf(YELLOW CHESTBUSTER RESET);
	}

	for (i = 0; i < nXCount; i++)
	{
		printf(RED XENOMORPH RESET);
	}

	for (i = 0; i < nQCount; i++)
	{
		printf(PURPLE QUEEN RESET);
	}

	printf("\n");

	displayDivider();
}


/*
Description: This function computes for the total lives of each alien type
Precondition: parameters are non-negative
@param <nFCount> <is the amount of facehuggers on screen>
@param <nCCount> <is the amount of chestbusters on screen>
@param <nXCount> <is the amount of xenomorphs on screen>
@param <nQCount> <is the amount of queens on screen>

@param <*correctFAnswer> <is the correct amount of facehugger lives to shoot>
@param <*correctCAnswer> <is the correct amount of chestbuster lives to shoot>
@param <*correctXAnswer> <is the correct amount of xenomorph lives to shoot>
@param <*correctQAnswer> <is the correct amount of queen lives to shoot>

@return <None>
*/
void computeAlienLives(int nFCount, int nCCount, int nXCount, int nQCount, float *correctFAnswer, float *correctCAnswer, float *correctXAnswer, float *correctQAnswer)
{
	//Calculate for overall lives of all alien types on screen
	*correctFAnswer = nFCount * FLIFE;
	*correctCAnswer = nCCount * CLIFE;
	*correctXAnswer = nXCount * XLIFE;
	*correctQAnswer = nQCount * QLIFE;
}

/*
Description: This function clears the entire screen
Precondition: Must only be called when player loses all lives, or completes all levels
@param <None>
@return None
*/
void clearScreen()
{
	//Clears screen
	system("cls"); //for mac, or system("cls"); for windows
}