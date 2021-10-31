#include "ECE_Pacman.h"

#include <iostream>

ECE_Pacman::ECE_Pacman() {
	this->PowerUpTaken = false;
	this->Map = nullptr;
	//this->Lives = 3;
	this->Points = 0;

	for (int i = 0; i < 4; i++) {
		this->ButtonDir[i] = false;
	}

	this->Dir = STALL;
	this->Pos = math::real3(0.0, -6.0, 0.0);
}

int ECE_Pacman::update(double dt) {
	// NewDir will equal the old value if no input is detected.
	int NewDir = this->Dir;
	if (this->ButtonDir[0]) {
		NewDir = UP;
	}
	else if (this->ButtonDir[1]) {
		NewDir = LEFT;
	}
	else if (this->ButtonDir[2]) {
		NewDir = DOWN;
	}
	else if (this->ButtonDir[3]) {
		NewDir = RIGHT;
	}

	math::real3 Vel = math::real3(0.0, 0.0, 0.0);
	if (this->at_intersection(dt)) {
		math::real3 Node = this->get_inode(dt);
		Node = math::real3(round(Node.x), round(Node.y), 0.0);
		this->Pos = Node;
		bool Traversable[4] = { false, false, false, false }; // {UP, LEFT, DOWN, RIGHT}
		math::real3 Neighbor[4];
		Neighbor[0] = Node + math::real3( 0.0,  1.0, 0.0);
		Neighbor[1] = Node + math::real3(-1.0,  0.0, 0.0);
		Neighbor[2] = Node + math::real3( 0.0, -1.0, 0.0);
		Neighbor[3] = Node + math::real3( 1.0,  0.0, 0.0);
		Node = this->get_inode(dt);
		for (int i = 0; i < 4; i++) {
			switch (Map->get_element(Neighbor[i].x, Neighbor[i].y)) {
			default:
				Traversable[i] = true;
				break;
			case ECE_Map::GENERIC_WALL: case ECE_Map::GHOST_WALL:
				Traversable[i] = false;
				break;
			}
		}

		// At this current pos, get item
		switch (Map->get_element(this->Pos.x, this->Pos.y)) {
		default:
			break;
		case ECE_Map::COIN:
			this->Points += 15;
			Map->set_element(this->Pos.x, this->Pos.y, 0);
			break;
		case ECE_Map::POWER_UP:
			this->PowerUpTaken = true;
			this->Points += 40;
			Map->set_element(this->Pos.x, this->Pos.y, 0);
			break;
		case ECE_Map::TELEPORT:
			this->Pos.x = -this->Pos.x;
			break;
		}

		if ((NewDir != STALL) ? Traversable[NewDir] : false) {
			this->Dir = NewDir;
			Vel = this->get_vel(NewDir);
			this->Pos += Vel * dt;
		}
		else if ((this->Dir != STALL) ? Traversable[this->Dir] : false) {
			Vel = this->get_vel(this->Dir);
			this->Pos += Vel * dt;
		}
		else {
			this->Dir = STALL;
		}
	}
	else {
		switch (this->Dir) {
		default:
			break;
		case UP:
			if (NewDir == DOWN) this->Dir = NewDir;
			break;
		case LEFT:
			if (NewDir == RIGHT) this->Dir = NewDir;
			break;
		case DOWN:
			if (NewDir == UP) this->Dir = NewDir;
			break;
		case RIGHT:
			if (NewDir == LEFT) this->Dir = NewDir;
			break;
		}
		Vel = this->get_vel(this->Dir);
		this->Pos += Vel * dt;
	}

	return 0;
}

int ECE_Pacman::draw(const ECE_Camera Camera) {

	// This generates the perspective matrix.
	math::real4x4 Pers = math::perspective(Camera.FOV, (double)Camera.Width / (double)Camera.Height, 1.0, 100.0);

	// This rotates the vertex to the camera.
	math::real4x4 Rot = math::real4x4(
		Camera.Right.x,		Camera.Right.y,		Camera.Right.z,		0.0,
		Camera.Up.x,		Camera.Up.y,		Camera.Up.z,		0.0,
		Camera.Forward.x,	Camera.Forward.y,	Camera.Forward.z,	0.0,
		0.0,				0.0,				0.0,				1.0
	);

	// This translates the vertex to the camera coordinate space.
	math::real4x4 Trans = math::real4x4(
		1.0, 0.0, 0.0, (this->Pos.x-Camera.Pos.x),
		0.0, 1.0, 0.0, (this->Pos.y-Camera.Pos.y),
		0.0, 0.0, 1.0, (this->Pos.z-Camera.Pos.z),
		0.0, 0.0, 0.0, 1.0
	);
	math::real4x4 T = Pers * Rot * Trans;

	glLoadMatrixf(T.ptr);
	glColor3f(1.0, 1.0, 0.0);
	glutSolidSphere(0.5, 10, 10);

	return 0;
}

math::real3 ECE_Pacman::get_inode(double dt) const {
	math::real3 temp = math::real3(0, 0, 0);
	bool Intersection = this->at_intersection(dt);
	math::real3 Vel = this->get_vel(this->Dir);
	math::real3 NewPos = this->Pos + Vel * dt;
	if (Intersection) {
		switch (this->Dir) {
		default:
			break;
		case STALL:
			temp = this->Pos;
			break;
		case UP:
			temp = math::real3(this->Pos.x, ceil(this->Pos.y), this->Pos.z);
			break;
		case LEFT:
			temp = math::real3(floor(this->Pos.x), this->Pos.y, this->Pos.z);
			break;
		case DOWN:
			temp = math::real3(this->Pos.x, floor(this->Pos.y), this->Pos.z);
			break;
		case RIGHT:
			temp = math::real3(ceil(this->Pos.x), this->Pos.y, this->Pos.z);
			break;
		}
	}

	return temp;
}

bool ECE_Pacman::at_intersection(double dt) const {
	bool Intersection = false;
	math::real3 Vel = this->get_vel(this->Dir);
	math::real3 NewPos = this->Pos + Vel * dt;
	switch (this->Dir) {
	default:
		break;
	case STALL:
		Intersection = true;
		break;
	case UP:
		Intersection = (ceil(this->Pos.y) == floor(NewPos.y));
		break;
	case LEFT:
		Intersection = (floor(this->Pos.x) == ceil(NewPos.x));
		break;
	case DOWN:
		Intersection = (floor(this->Pos.y) == ceil(NewPos.y));
		break;
	case RIGHT:
		Intersection = (ceil(this->Pos.x) == floor(NewPos.x));
		break;
	}
	return Intersection;
}

math::real3 ECE_Pacman::get_vel(int aDir) const {
	math::real Mag = 4.0; // Determines Pacman's speed.
	math::real3 Vel = math::real3(0.0, 0.0, 0.0);
	switch (aDir) {
	default:
		break;
	case UP:
		Vel.y += Mag;// 1.0;
		break;
	case LEFT:
		Vel.x -= Mag;// 1.0;
		break;
	case DOWN:
		Vel.y -= Mag;// 1.0;
		break;
	case RIGHT:
		Vel.x += Mag;// 1.0;
		break;
	}
	return Vel;
}
