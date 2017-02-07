#include <iostream>
#include "sfwdraw.h"
#include "maths.h"
#include "particles.h"

void main() {
	sfw::initContext();

	unsigned sprite = sfw::loadTextureMap("../res/particle_sprite.png");

	particle part;
	part.sprite = sprite;
	part.pos = vec2{ 400,0 };
	part.vel = vec2{ 0,20 };
	part.sDim = vec2{ 8,8 };
	part.eDim = vec2{ 256, 256 };
	part.sColor.ui_color = GREEN;
	part.eColor.ui_color = BLUE;
	part.lifespan = 12.f;
	part.lifetime = 0;

	while (sfw::stepContext()) {
		float dt = sfw::getDeltaTime();
		
		part.refresh(dt);


	}

	sfw::termContext();


}