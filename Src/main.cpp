//
//  main.cpp

 /*-------------------------------------------------------------------------+
 |	No idea what this is doing.  Ask Chris.									|
 +-------------------------------------------------------------------------*/

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <pthread.h>
#include <unistd.h>
#include <thread>
#include <iostream>
#include <mutex>
//
#include "gl_frontEnd.h"
std::mutex ghostLock, pacLock;

//==================================================================================
//	Custom data types
//==================================================================================


//==================================================================================
//	Function prototypes
//==================================================================================
void displayGridPane(void);
void displayStatePane(void);
void initializeApplication(void);
void* pacmanLoop(void* v);
void* ghostLoop(void* v);


//==================================================================================
//	Application-level global variables
//==================================================================================

//	Don't touch
extern int	GRID_PANE, STATE_PANE;
extern int	gMainWindow, gSubwindow[2];

//	The state grid and its dimensions
GameWorld gameWorld;

//	pacman game stats
int numLiveThreads = 0;
int score = 0;
int dots_collected = 0;
int pacman_lives = 3;

//==================================================================================
//	These are the functions that tie the simulation with the rendering.
//	Some parts are "don't touch."  Other parts need your intervention
//	to make sure that access to critical section is properly synchronized
//==================================================================================


void displayGridPane(void)
{
	//	This is OpenGL/glut magic.  Don't touch
	glutSetWindow(gSubwindow[GRID_PANE]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//---------------------------------------------------------
	//	This is the call that makes OpenGL render the grid.
	//
	//	You *must* synchronize this call.
	//
	//---------------------------------------------------------
	{
		std::unique_lock myGhost(ghostLock);
		std::unique_lock myPac(pacLock);
		drawGameWorld(&gameWorld);
	}
	
	//	This is OpenGL/glut magic.  Don't touch
	glutSwapBuffers();
	
	glutSetWindow(gMainWindow);
}

void displayStatePane(void)
{
	//	This is OpenGL/glut magic.  Don't touch
	glutSetWindow(gSubwindow[STATE_PANE]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//---------------------------------------------------------
	//	This is the call that makes OpenGL render information
	//	about the state of the simulation.
	//
	//	You *must* synchronize this call.
	//
	//---------------------------------------------------------
	{
		std::unique_lock myGhost(ghostLock);
		std::unique_lock myPac(pacLock);
		drawState(numLiveThreads, gameWorld.score, gameWorld.dots_collected, gameWorld.numLives);
	}
	
	
	//	This is OpenGL/glut magic.  Don't touch
	glutSwapBuffers();
	
	glutSetWindow(gMainWindow);
}

//------------------------------------------------------------------------
//	You shouldn't have to change anything in the main function
//------------------------------------------------------------------------
int main(int argc, char** argv)
{
    srand(static_cast<unsigned int>(time(NULL)));

	initializeFrontEnd(argc, argv, displayGridPane, displayStatePane);
	
	//	Now we can do application-level
	initializeApplication();

	//	Now we enter the main loop of the program and to a large extend
	//	"lose control" over its execution.  The callback functions that 
	//	we set up earlier will be called when the corresponding event
	//	occurs
	glutMainLoop();

		
	//	This will never be executed (the exit point will be in one of the
	//	call back functions).
	return 0;
}


//==================================================================================
//
//	This is a part that you have to edit and add to.
//
//==================================================================================

void threadFunc(int index)
{
	numLiveThreads++;
	while(!gameWorld.gameOver)
	{
		{
		std::unique_lock myGhost(ghostLock);
		gameWorld.ghost_array[index].ghostAI(gameWorld);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(15));
	}
}

void initializeApplication(void)
{
    //Allocate the grid and all objects
    initializeGameWorldFile(gameWorld, "Levels/level_01.txt");

	//	Probably here would be a good place to create the threads
	for(unsigned int k=0; k < gameWorld.ghost_count; k++)
	{
		gameWorld.ghostThreads.push_back(std::thread(threadFunc, k));
	}
}

//-------------------------------------------------------------------
//	This is the main work that needs to be done by multiple threads:
//		One thread for Pacman, and one for each ghost
//-------------------------------------------------------------------
void updatePacAndGhosts(void)
{
	//update pacman
	{
		std::unique_lock myGhost(ghostLock);
		std::unique_lock myPac(pacLock);
		if (gameWorld.pacman != nullptr)
			gameWorld.pacman->update(gameWorld);
	}
}
