/*
* Author:
* Class: ECE4122
* Last Date Modified: 12/01/2020
* Description:
* This is the early design for the pacman game
* final project for the class ECE 4122. Default controls
* are press 'R' for clockwise rotation. The math library was
* also written by me as a utility. I never much liked the other
* math libraries available such as glm, so I wrote my own so I could
* define the notation that was more to my own liking. DEBUG_MODE
* can be enabled for free camera movement mode.
* DEBUG_MODE was used for the modelling of the maze.
* 
* ----------------------------------------------------------------------
* 
* Controls to move the camera are as follows.
* WASD are the keys for camera motion.
* W: Moves the camera forward.
* A: Moves the camera left.
* S: Moves the camera backwars.
* D: Moves the camera right
* 
* Up Key: Rotates the camera up.
* Left Key: Rotates the camera left.
* Down Key: Rotates the camera down.
* Right Key: Rotates the camera right.
*/

//#define DEBUG_MODE

/*
Bugs (Binny)
	-Sometimes ghost go through ghost house walls.
	-Sometimes ghosts and pacman can escape the teleporter
	-The ghosts in frightened mode
*/

#include <math.h>
#include <time.h>
#include <iostream>


#ifdef _WIN32
#include <Windows.h>
#endif // __WIN32

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h> // Fucking garbage API, go back to 2001.

#include "src/math/mathematics.h"

#include "src/objects/ECE_Camera.h"
#include "src/objects/ECE_Map.h"
#include "src/objects/ECE_Ghost.h"
#include "src/objects/ECE_Pacman.h"

/*
* Cols = 19
* Rows = 22
* GridElement[][]
* 0 - Empty Space
* 1 - Coin
* 2 - Power Up
* 3 - Player Start
* 4 - Ghost Wall
* 5 - Generic Wall
*/
//int GridElement[22][19] = {
//	{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
//	{5, 1, 1, 1, 1, 1, 1, 1, 1, 5, 1, 1, 1, 1, 1, 1, 1, 1, 5},
//	{5, 2, 5, 5, 1, 5, 5, 5, 1, 5, 1, 5, 5, 5, 1, 5, 5, 2, 5},
//	{5, 1, 5, 5, 1, 5, 5, 5, 1, 5, 1, 5, 5, 5, 1, 5, 5, 1, 5},
//	{5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5},
//	{5, 1, 5, 5, 1, 5, 1, 5, 5, 5, 5, 5, 1, 5, 1, 5, 5, 1, 5},
//	{5, 1, 1, 1, 1, 5, 1, 1, 1, 5, 1, 1, 1, 5, 1, 1, 1, 1, 5},
//	{5, 5, 5, 5, 1, 5, 5, 5, 0, 5, 0, 5, 5, 5, 1, 5, 5, 5, 5},
//	{0, 0, 0, 5, 1, 5, 0, 0, 0, 0, 0, 0, 0, 5, 1, 5, 0, 0, 0},
//	{5, 5, 5, 5, 1, 5, 0, 5, 5, 4, 5, 5, 0, 5, 1, 5, 5, 5, 5},
//	{0, 0, 0, 0, 1, 0, 0, 5, 0, 0, 0, 5, 0, 0, 1, 0, 0, 0, 0},
//	{5, 5, 5, 5, 1, 5, 0, 5, 5, 5, 5, 5, 0, 5, 1, 5, 5, 5, 5},
//	{0, 0, 0, 5, 1, 5, 0, 0, 0, 0, 0, 0, 0, 5, 1, 5, 0, 0, 0},
//	{5, 5, 5, 5, 1, 5, 0, 5, 5, 5, 5, 5, 0, 5, 1, 5, 5, 5, 5},
//	{5, 1, 1, 1, 1, 1, 1, 1, 1, 5, 1, 1, 1, 1, 1, 1, 1, 1, 5},
//	{5, 1, 5, 5, 1, 5, 5, 5, 1, 5, 1, 5, 5, 5, 1, 5, 5, 1, 5},
//	{5, 2, 1, 5, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 5, 1, 2, 5},
//	{5, 5, 1, 5, 1, 5, 1, 5, 5, 5, 5, 5, 1, 5, 1, 5, 1, 5, 5},
//	{5, 1, 1, 1, 1, 5, 1, 1, 1, 5, 1, 1, 1, 5, 1, 1, 1, 1, 5},
//	{5, 1, 5, 5, 5, 5, 5, 5, 1, 5, 1, 5, 5, 5, 5, 5, 5, 1, 5},
//	{5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5},
//	{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}
//};

// Set Framerate
double FPS = 60.0;
// Window Size
int Width = 640;
int Height = 480;

//double Angle = -math::constant::pi / 2.0; // In Radians
double Angle = -math::constant::pi/3.0; // In Radians

// Main Camera
ECE_Camera Camera(math::real3(0.0, 0.0, 22.0), math::constant::pi, math::constant::pi / 2.0);

ECE_Map Map;

// Ghosts
ECE_Ghost Ghost[4] = {
	ECE_Ghost(ECE_Ghost::Color_Type::RED),
	ECE_Ghost(ECE_Ghost::Color_Type::GREEN),
	ECE_Ghost(ECE_Ghost::Color_Type::ORANGE),
	ECE_Ghost(ECE_Ghost::Color_Type::PINK)
};

// Actually pacman
int Lives = 3;
bool StartGame = false;
ECE_Pacman Pacman;

clock_t Start, End;
math::real t, dt;

void init_game();
void reset_game();
int interact(ECE_Pacman P, ECE_Ghost G);

void update();
void display();
void reshape(int WindowWidth, int WindowHeight);

// Keyboard input
void literal_key_press(unsigned char Key, int x, int y);
void literal_key_release(unsigned char Key, int x, int y);
void special_key_press(int Key, int x, int y);
void special_key_release(int Key, int x, int y);
// Mouse input

void mouse_move(int x, int y);
void mouse_button(int Button, int State, int x, int y);


int main(int argc, char* argv[]) {

	t = 0.0;
	dt = 0.0;
	End = clock();

	Camera.FOV = math::deg2rad(75);
	Camera.Width = Width;
	Camera.Height = Height;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(Width, Height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Pac Bois™️");

	// Update and Draw
	//glutTimerFunc(10u, update, 10);
	glutIdleFunc(update);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	// Input Output Gathering
	glutKeyboardFunc(literal_key_press);
	glutKeyboardUpFunc(literal_key_release);
	glutSpecialFunc(special_key_press);
	glutSpecialUpFunc(special_key_release);
	glutPassiveMotionFunc(mouse_move);
	glutMouseFunc(mouse_button);

	init_game();

	glutMainLoop();

	return 0;
}

void init_game() {
	//Pacman.Pos = math::real3(0, -6, 0);
	//Ghost[0].Pos = math::real3(0.0, 2.0, 0.15);
	//Ghost[1].Pos = math::real3(-1.0, 0.0, 0.15);
	//Ghost[2].Pos = math::real3(1.0, 0.0, 0.15);
	//Ghost[3].Pos = math::real3(0.0, 0.0, 0.15);

	Pacman.Map = &Map;
	for (int i = 0; i < 4; i++) {
		Ghost[i].Map = &Map;
	}
}

void reset_game() {
	Pacman = ECE_Pacman();
	Ghost[0] = ECE_Ghost(ECE_Ghost::RED);
	Ghost[1] = ECE_Ghost(ECE_Ghost::GREEN);
	Ghost[2] = ECE_Ghost(ECE_Ghost::ORANGE);
	Ghost[3] = ECE_Ghost(ECE_Ghost::PINK);
	
	Map.reset();

	Pacman.Map = &Map;
	for (int i = 0; i < 4; i++) {
		Ghost[i].Map = &Map;
	}
}

//int interact(ECE_Pacman P, ECE_Ghost G) {
//	if (math::length(P.Pos - G.Pos) < 1.0) {
//		// Within bounds of eachother, check for death or game over.
//		switch (G.State) {
//		default:
//			return 0;
//		case ECE_Ghost::CHASE:
//			// Game over.
//			return -1;
//		case ECE_Ghost::FRIGHTENED:
//			// Ghost eaten
//			P.Points += 100;
//			G.State = ECE_Ghost::EATEN;
//			return 0;
//		}
//	}
//}

void update() {
	// Main loop for updates.
	dt = 0.0;
	do {
		// <time.h>
		Start = End;
		End = clock();
		math::real temp = ((double)End - (double)Start) / (double)CLOCKS_PER_SEC;

		dt += temp;

		// If enough time has passed, release from loop.
		if (dt > (math::real)(1.0 / FPS)) break;
	} while (true);
	t += dt;
	//std::cout << dt << std::endl;

	srand((unsigned int)t);

	if (StartGame) {


		Camera.update(dt);

		Map.update(dt);

		for (int i = 0; i < 4; i++) {
			Ghost[i].update(dt);
		}
		Pacman.update(dt);

		for (int i = 0; i < 4; i++) {
			Ghost[i].TargetPos = Pacman.Pos;
		}

		// Updates ghosts to frightened mode if power up is taken.
		if (Pacman.PowerUpTaken) {
			for (int i = 0; i < 4; i++) {
				if ((Ghost[i].State == ECE_Ghost::CHASE) || (Ghost[i].State == ECE_Ghost::SCATTER)) {
					Ghost[i].ModeTimer = 0.0;
					Ghost[i].State = ECE_Ghost::FRIGHTENED;
				}
			}
			Pacman.PowerUpTaken = false;
		}

		// Checks for ghost pacman interaction.
		for (int i = 0; i < 4; i++) {
			if (math::length(Pacman.Pos - Ghost[i].Pos) < 0.6) {
				// Within bounds of eachother, check for death or game over.
				switch (Ghost[i].State) {
				default:
					break;
				case ECE_Ghost::CHASE: case ECE_Ghost::SCATTER:
					//std::cout << "ded" << std::endl;
					// Game over.
					Lives -= 1;
					reset_game();
					break;
				case ECE_Ghost::FRIGHTENED:
					// Ghost eaten
					Pacman.Points += 100;
					Ghost[i].State = ECE_Ghost::EATEN;
					break;
				}
			}
		}

	}

#ifndef DEBUG_MODE
	Camera.Pos = 20.0 * math::real3(cos(Angle), sin(Angle), 1);
	Camera.Forward = math::normalize(math::real3(-cos(Angle), -sin(Angle), -1.0));
	Camera.Right = math::normalize(math::real3(-sin(Angle), cos(Angle), 0.0));
	Camera.Up = math::normalize(math::real3(-cos(Angle), -sin(Angle), 1.0));
#endif // !DEBUG_MODE


	// Clears frame buffer.
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);


	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glDepthRange(1.0, -1.0);

	GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat light_position[] = { 0.0, 10.0, 0.5, 0.0 };

	glLoadIdentity();
	//glLoadMatrixf(Final.ptr);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	Pacman.draw(Camera);
	for (int i = 0; i < 4; i++) {
		Ghost[i].draw(Camera);
	}

	Map.draw(Camera);

	// Swap Framebuffers
	glutSwapBuffers();

	if ((Lives == 0) || Map.check()) exit(0);
}

void display() {
	// Draw sh...
	// I mean stuff.
}

void reshape(int WindowWidth, int WindowHeight) {
	Width = WindowWidth;
	Height = WindowHeight;
	Camera.Width = Width;
	Camera.Height = Height;
	glViewport(0, 0, WindowWidth, WindowHeight);
}

// Keyboard input
void literal_key_press(unsigned char Key, int x, int y) {
	//std::cout << Key << ": Pressed" << std::endl;
	StartGame = true;
	switch (Key) {
	default:
		break;
	case 'w':
		//Camera.Pos += Camera.Forward * dt * 1000.0;
		Camera.KeyActive[0] = true;
		break;
	case 'a':
		Camera.KeyActive[1] = true;
		break;
	case 's':
		Camera.KeyActive[2] = true;
		break;
	case 'd':
		Camera.KeyActive[3] = true;
		break;
	case 'r':
		Angle += math::deg2rad(5);
		break;
	}
}

void literal_key_release(unsigned char Key, int x, int y) {
	//std::cout << Key << ": Released" << std::endl;
	switch (Key) {
	default:
		break;
	case 'w':
		Camera.KeyActive[0] = false;
		break;
	case 'a':
		Camera.KeyActive[1] = false;
		break;
	case 's':
		Camera.KeyActive[2] = false;
		break;
	case 'd':
		Camera.KeyActive[3] = false;
		break;
	}
}

void special_key_press(int Key, int x, int y) {
	// Special Key Press
	switch (Key) {
	default:
	case GLUT_KEY_UP:
		//Camera.KeyActive[4] = true;
		Pacman.ButtonDir[0] = true;
		break;
	case GLUT_KEY_LEFT:
		//Camera.KeyActive[5] = true;
		Pacman.ButtonDir[1] = true;
		break;
	case GLUT_KEY_DOWN:
		//Camera.KeyActive[6] = true;
		Pacman.ButtonDir[2] = true;
		break;
	case GLUT_KEY_RIGHT:
		//Camera.KeyActive[7] = true;
		Pacman.ButtonDir[3] = true;
		break;
	}
}

void special_key_release(int Key, int x, int y) {
	// Special Key Release
	switch (Key) {
	default:
	case GLUT_KEY_UP:
		//Camera.KeyActive[4] = false;
		Pacman.ButtonDir[0] = false;
		break;
	case GLUT_KEY_LEFT:
		//Camera.KeyActive[5] = false;
		Pacman.ButtonDir[1] = false;
		break;
	case GLUT_KEY_DOWN:
		//Camera.KeyActive[6] = false;
		Pacman.ButtonDir[2] = false;
		break;
	case GLUT_KEY_RIGHT:
		//Camera.KeyActive[7] = false;
		Pacman.ButtonDir[3] = false;
		break;
	}
}

// Mouse input
void mouse_move(int xw, int yw) {
	static math::real2 p0 = math::real2(0.0, 0.0);
	math::real2 p = math::real2(2.0 * ((double)xw / (double)Width) - 1.0, -2.0 * ((double)yw / (double)Height) + 1.0);
	math::real2 v = (p - p0) / dt;
	//std::cout << p.x << " " << p.y << std::endl;
}

void mouse_button(int Button, int State, int x, int y) {

}

