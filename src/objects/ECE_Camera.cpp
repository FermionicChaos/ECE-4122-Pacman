#include "ECE_Camera.h"

//tex:
//$$ x = r \sin{\theta} \cos{\phi} $$
//$$ y = r \sin{\theta} \sin{\phi} $$
//$$ z = r \cos{\theta} $$

ECE_Camera::ECE_Camera() {
	this->Pos = math::real3(0, 0, 0);
	this->Vel = math::real3(0, 0, 0);
	this->Theta = math::constant::pi;
	this->Phi = 0.0;
	for (int i = 0; i < 8; i++) {
		this->KeyActive[i] = false;
	}

	this->Right		= math::real3(0.0, 0.0, 0.0);
	this->Up		= math::real3(0.0, 0.0, 0.0);
	this->Forward	= math::real3(0.0, 0.0, 0.0);

	this->FOV = 0.0;
	this->Width = 0;
	this->Height = 0;
}

ECE_Camera::ECE_Camera(math::real3 aPos, math::real aTheta, math::real aPhi) {
	this->Pos = aPos;
	this->Vel = math::real3(0, 0, 0);
	this->Theta = aTheta;
	this->Phi = aPhi;
	for (int i = 0; i < 8; i++) {
		this->KeyActive[i] = false;
	}

	this->Right		= math::real3( sin(Phi),			-cos(Phi),				0.0 		);
	this->Up		= math::real3(-cos(Phi)*cos(Theta),	-sin(Phi)*cos(Theta),	sin(Theta)	);
	this->Forward	= math::real3( cos(Phi)*sin(Theta),	 sin(Phi)*sin(Theta),	cos(Theta)	);

}

int ECE_Camera::update(double dt) {
	math::real3 TVel = math::real3(0, 0, 0);
	if (KeyActive[0]) {
		TVel += this->Forward;
	}
	if (KeyActive[1]) {
		TVel -= this->Right;
	}
	if (KeyActive[2]) {
		TVel -= this->Forward;
	}
	if (KeyActive[3]) {
		TVel += this->Right;
	}

	math::real dTheta = 0.0;
	math::real dPhi = 0.0;

	if (KeyActive[4]) {
		dTheta -= 0.05;
	}
	if (KeyActive[5]) {
		dPhi += 0.05;
	}
	if (KeyActive[6]) {
		dTheta += 0.05;
	}
	if (KeyActive[7]) {
		dPhi -= 0.05;
	}

	this->Vel = TVel;
	this->Theta += dTheta;
	this->Phi += dPhi;

	this->Pos += 10.0 * this->Vel * dt;
	this->Right		= math::real3( sin(Phi),			-cos(Phi),				0.0 		);
	this->Up		= math::real3(-cos(Phi)*cos(Theta),	-sin(Phi)*cos(Theta),	sin(Theta)	);
	this->Forward	= math::real3( cos(Phi)*sin(Theta),	 sin(Phi)*sin(Theta),	cos(Theta)	);

	return 0;
}

math::real4x4 ECE_Camera::get_transform(math::real3 ObjPos) const {
	// Generates the transfomation matrix using the poisition of the object,
	// and the camera parameters.

    // This generates the perspective matrix.
	math::real4x4 Perspective = math::perspective(this->FOV, (double)this->Width / (double)this->Height, 1.0, 100.0);

	// This rotates the vertex to the camera.
	math::real4x4 Rotate = math::real4x4(
		this->Right.x,		this->Right.y,		this->Right.z,		0.0,
		this->Up.x,			this->Up.y,			this->Up.z,			0.0,
		this->Forward.x,	this->Forward.y,	this->Forward.z,	0.0,
		0.0,				0.0,				0.0,				1.0
	);

	// This translates the vertex to the camera coordinate space.
	math::real4x4 Translate = math::real4x4(
		1.0, 0.0, 0.0, (ObjPos.x - this->Pos.x),
		0.0, 1.0, 0.0, (ObjPos.y - this->Pos.y),
		0.0, 0.0, 1.0, (ObjPos.z - this->Pos.z),
		0.0, 0.0, 0.0, 1.0
	);

    return (Perspective * Rotate * Translate);
}
