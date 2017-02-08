#include <iostream>
#include "sfwdraw.h"
#include "maths.h"
#include "particles.h"
#include "particleEmitter.h"
#include <time.h>
#include "ObjectPool.h"

void main() {
	sfw::initContext();

	ObjectPool pool(20);

	auto it = pool.push();

	if ((bool)it == true) {

	}
	
	for (int i = 0; i < 10; ++i) pool.push();

	for each(auto part in pool) part.isActive();

	unsigned sprite = sfw::loadTextureMap("../res/particle_sprite.png");

	particleEmitter pe, pe2;

	pe.emitRateLo = .000001f;
	pe.emitRateHi = .000003f;

	pe.sprite = sprite;

	pe.pos = vec2{ 400,300 };
	pe.angleLo = 0;
	pe.angleHi = 360;
	pe.speedLo = 60;
	pe.speedHi = 100;
	pe.dimLoStart = vec2{ 8,8 };
	pe.dimHiStart = vec2{ 32,32 };
	pe.dimLoEnd = vec2{ 256,256 };
	pe.dimHiEnd = vec2{ 512, 512 };

	pe.colLoStart.ui_color = WHITE;
	pe.colHiStart.ui_color = RED;
	pe.colLoEnd.ui_color = NONE;
	pe.colHiEnd.ui_color = NONE;

	pe.lifeSpanLo = 6.9f;
	pe.lifeSpanHi = 12.5f;	

	while (sfw::stepContext()) {
		float dt = sfw::getDeltaTime();
		pe.update(dt);
	}

	sfw::termContext();


}