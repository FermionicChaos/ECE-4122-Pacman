#include "ECE_Ghost.h"

#include <random>
#include <chrono>

const math::real3 ECE_Ghost::FColor = math::real3(0.0, 0.0, 1.0);

ECE_Ghost::ECE_Ghost(int ID) {
	this->Map = nullptr;
	this->ModeTimer = 0.0;
	this->ID = ID;
	//this->State = STANDSTILL;
	this->State = SCATTER;
	this->Dir = STALL;
	switch (ID) {
	default:
		this->Color = math::real3(1.0, 1.0, 1.0);
		this->Pos = math::real3(0.0, 0.0, -10.0);
		break;
	case RED:
		this->Color = math::real3(1.0, 0.0, 0.0);
		this->Pos = math::real3(0.0, 1.0, 0.15);
		//this->Pos = math::real3(0.0, 0.0, 0.15);
		break;
	case GREEN:
		this->Color = math::real3(0.0, 1.0, 0.0);
		this->Pos = math::real3(-1.0, 0.0, 0.15);
		//this->Pos = math::real3(0.0, 0.0, 0.15);
		break;
	case ORANGE:
		this->Color = math::real3(1.0, 0.6470f, 0.0039f);
		this->Pos = math::real3(1.0, 0.0, 0.15);
		//this->Pos = math::real3(0.0, 0.0, 0.15);
		break;
	case PINK:
		this->Color = math::real3(1.0, 0.7529f, 0.7960f);
		this->Pos = math::real3(0.0, 0.0, 0.15);
		break;
	}
	this->TargetPos = math::real3(0.0, 0.0, 0.0);
}

int ECE_Ghost::update(double dt) {
	// this part insures that the ghosts do not go through the walls, despite being ghosts.
	int NewDir = this->Dir;

	math::real3 Vel = math::real3(0.0, 0.0, 0.0);
	if (this->at_intersection(dt)) {
		// Actual code that determines the possibility of choice from previous selection.
		math::real3 Node = this->get_inode(dt);
		Node = math::real3(round(Node.x), round(Node.y), 0.0);
		this->Pos = Node;
		bool Traversable[4] = { false, false, false, false }; // {UP, LEFT, DOWN, RIGHT}
		math::real3 Neighbor[4];
		Neighbor[0] = Node + math::real3(0.0, 1.0, 0.0);
		Neighbor[1] = Node + math::real3(-1.0, 0.0, 0.0);
		Neighbor[2] = Node + math::real3(0.0, -1.0, 0.0);
		Neighbor[3] = Node + math::real3(1.0, 0.0, 0.0);
		Node = this->get_inode(dt);
		for (int i = 0; i < 4; i++) {
			switch (Map->get_element(Neighbor[i].x, Neighbor[i].y)) {
			default:
				Traversable[i] = true;
				break;
			case ECE_Map::GENERIC_WALL: /*case ECE_Map::GHOST_WALL:*/
				Traversable[i] = false;
				break;
			}
		}

		int Seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::default_random_engine RNG1(Seed);
		std::uniform_real_distribution<double> D1(0, 3);
		math::real ShortPath = FLT_MAX;
		switch (this->State) {
		default:
			break;
		case CHASE:
			// Finds nearest neighbor node to pacman. (Greedy Algo)
			// This part determines the appropriate path the ghost will take
			for (int i = 0; i < 4; i++) {
				if ((length(this->TargetPos - Neighbor[i]) < ShortPath) && (Traversable[i])) {
					ShortPath = length(this->TargetPos - Neighbor[i]);
					NewDir = i;
				}
			}
			//NewDir = round(D1(RNG1));
			break;
		case SCATTER:
			// Scatter is random so the ghosts don't merge when they hunt pacman
			NewDir = round(D1(RNG1));
			break;
		case FRIGHTENED:
			NewDir = round(D1(RNG1));
			break;
		}

		//std::cout << "God fucking damn im a stupid fucking ghost" << std::endl;
		//if (this->State == FRIGHTENED) {
		//	switch (NewDir) {
		//	default:
		//		break;
		//	case UP:
		//		NewDir = DOWN;
		//		break;
		//	case LEFT:
		//		NewDir = RIGHT;
		//		break;
		//	case DOWN:
		//		NewDir = UP;
		//		break;
		//	case RIGHT:
		//		NewDir = LEFT;
		//		break;
		//	}
		//}

		if (Map->get_element(this->Pos.x, this->Pos.y) == ECE_Map::TELEPORT) {
			this->Pos.x = -this->Pos.x;
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

	// Changes between CHASE and SCATTER determined by RNG.
	switch (this->State) {
	default:
		break;
	case CHASE:
		if (ModeTimer <= 4.0) {
			ModeTimer += dt;
		}
		else {
			ModeTimer = 0.0;
			if ((rand() % 2) == 1) {
				//std::cout << "Change to scatter" << std::endl;
				this->State = SCATTER;
			}
		}
		break;
	case SCATTER:
		if (ModeTimer <= 4.0) {
			ModeTimer += dt;
		}
		else {
			ModeTimer = 0.0;
			if ((rand() % 2) == 1) {
				//std::cout << "Change to scatter" << std::endl;
				this->State = CHASE;
			}
		}
		break;
	case EATEN:
		if (ModeTimer <= 5.0) {
			ModeTimer += dt;
		}
		else {
			// Resets once timer expires
			ModeTimer = 0.0;
			switch (this->ID) {
			default:
				this->Pos = math::real3(0.0, 0.0, -10.0);
				break;
			case RED:
				this->Pos = math::real3(0.0, 1.0, 0.15);
				break;
			case GREEN:
				this->Pos = math::real3(-1.0, 0.0, 0.15);
				break;
			case ORANGE:
				this->Pos = math::real3(1.0, 0.0, 0.15);
				break;
			case PINK:
				this->Pos = math::real3(0.0, 0.0, 0.15);
				break;
			}
			this->State = SCATTER;
		}
		break;
	case FRIGHTENED:
		if (ModeTimer <= 5.0) {
			ModeTimer += dt;
		}
		else {
			// Resets once 
			ModeTimer = 0.0;
			this->State = SCATTER;
		}
		break;
	}
	return 0;
}

int ECE_Ghost::draw(const ECE_Camera Camera) {

	math::real4x4 RR = math::rotation(math::deg2rad(180), math::real3(1, 0, 0));
	//math::real4x4 T = Pers * Rot * Trans * RR;
	math::real4x4 T = Camera.get_transform(this->Pos) * RR;

	GLUquadricObj* p = NULL;
	glLoadMatrixf(T.ptr);
	switch (this->State) {
	default:
		break;
	/*case STANDSTILL:*/ case CHASE: case SCATTER:
		glColor3f(this->Color.x, this->Color.y, this->Color.z);
		p = gluNewQuadric();
		gluCylinder(p, 0.5, 0.5, 0.5, 10, 10);
		gluQuadricDrawStyle(p, GLU_LINE);
		gluDeleteQuadric(p);

		glLoadMatrixf(T.ptr);
		glColor3f(this->Color.x, this->Color.y, this->Color.z);
		glutSolidSphere(0.5, 10, 10);
		break;
	case FRIGHTENED:
		glColor3f(this->FColor.x, this->FColor.y, this->FColor.z);
		p = gluNewQuadric();
		gluCylinder(p, 0.5, 0.5, 0.5, 10, 10);
		gluQuadricDrawStyle(p, GLU_LINE);
		gluDeleteQuadric(p);

		glLoadMatrixf(T.ptr);
		glColor3f(this->FColor.x, this->FColor.y, this->FColor.z);
		glutSolidSphere(0.5, 10, 10);
		break;
	case EATEN:

		break;
	}

	return 0;
}

int ECE_Ghost::reset() {
	this->Map = nullptr;
	this->ModeTimer = 0.0;
	this->ID = ID;
	//this->State = STANDSTILL;
	this->State = SCATTER;
	this->Dir = STALL;
	switch (ID) {
	default:
		this->Color = math::real3(1.0, 1.0, 1.0);
		this->Pos = math::real3(0.0, 0.0, -10.0);
		break;
	case RED:
		this->Color = math::real3(1.0, 0.0, 0.0);
		this->Pos = math::real3(0.0, 1.0, 0.15);
		//this->Pos = math::real3(0.0, 0.0, 0.15);
		break;
	case GREEN:
		this->Color = math::real3(0.0, 1.0, 0.0);
		this->Pos = math::real3(-1.0, 0.0, 0.15);
		//this->Pos = math::real3(0.0, 0.0, 0.15);
		break;
	case ORANGE:
		this->Color = math::real3(1.0, 0.6470f, 0.0039f);
		this->Pos = math::real3(1.0, 0.0, 0.15);
		//this->Pos = math::real3(0.0, 0.0, 0.15);
		break;
	case PINK:
		this->Color = math::real3(1.0, 0.7529f, 0.7960f);
		this->Pos = math::real3(0.0, 0.0, 0.15);
		break;
	}
	this->TargetPos = math::real3(0.0, 0.0, 0.0);
	return 0;
}

math::real3 ECE_Ghost::get_inode(double dt) const {
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

bool ECE_Ghost::at_intersection(double dt) const {
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

math::real3 ECE_Ghost::get_vel(int aDir) const {
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