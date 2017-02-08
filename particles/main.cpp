#include <iostream>
#include "sfwdraw.h"
#include "maths.h"
#include "particleEmitter.h"
#include <time.h>
#include "GameState.h"

void main() {

	sfw::initContext();
	GameState gs;
	gs.init();
	gs.play();

	while (sfw::stepContext()) {
		float dt = sfw::getDeltaTime();
		gs.update(dt);
	}

	sfw::termContext();
}

//void main2() {
//	sfw::initContext();
//
//	unsigned sprite = sfw::loadTextureMap("../res/particle_sprite.png");
//
//	particleEmitter pe, pe2;
//
//	pe.emitRateLo = .001f;
//	pe.emitRateHi = .003f;
//
//	pe.sprite = sprite;
//
//	pe.pos = vec2{ 400,5 };
//	pe.angleLo = 45;
//	pe.angleHi = 135;
//	pe.speedLo = 120;
//	pe.speedHi = 320;
//	pe.dimLoStart = vec2{ 8,8 };
//	pe.dimHiStart = vec2{ 32,32 };
//	pe.dimLoEnd = vec2{ 256,256 };
//	pe.dimHiEnd = vec2{ 512, 512 };
//
//	pe.colLoStart.ui_color = WHITE;
//	pe.colHiStart.ui_color = RED;
//	pe.colLoEnd.ui_color = NONE;
//	pe.colHiEnd.ui_color = NONE;
//
//	pe.lifeSpanLo = 6.9f;
//	pe.lifeSpanHi = 12.5f;	
//
//	while (sfw::stepContext()) {
//		float dt = sfw::getDeltaTime();
//		pe.update(dt);
//	}
//
//	sfw::termContext();
//
//
//}