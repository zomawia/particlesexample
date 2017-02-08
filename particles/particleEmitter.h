#pragma once
#include "particles.h"
#include "ObjectPool.h"

#define PART_SIZE 51200

//factory
class particleEmitter {
	//data structure to store all particles
	//particle particles[PART_SIZE];
	ObjectPool <particles> parts;
	
	void emit() {

		//for (int i = 0; i < PART_SIZE; ++i)
		//{
		//	if (!particles[i].isActive()) {
		//		particles[i] = _generate();
		//		return;
		//	}
		//}
		parts.push(_generate());
	}

	particles _generate() {
		particles part;
		part.pos = pos;
		part.sprite = sprite;

		part.vel = randDirr(angleLo, angleHi) * lerp(speedLo, speedHi, rand01());

		part.lifespan = lerp(lifeSpanLo, lifeSpanHi, rand01());

		part.sColor = lerp(colLoStart, colHiStart, rand01());
		part.eColor = lerp(colLoEnd, colHiEnd, rand01());

		part.sDim = randRanger(dimLoStart, dimHiStart);
		part.eDim = randRanger(dimLoEnd, dimHiEnd);

		part.lifetime = 0;

		return part;
	}

	float emissionTimer;

public:
	//emissions
	float emitRateLo, emitRateHi;
	
	particleEmitter() : emissionTimer(0), parts(PART_SIZE) {}


	//defaults
	unsigned sprite;
	vec2 pos;
	float angleLo, angleHi;			//direction
	float speedLo, speedHi;			//speed velocity
	vec2 dimLoStart, dimHiStart;	//range of acceptable start dims
	vec2 dimLoEnd, dimHiEnd;		//range of acceptable end dims
	color colLoStart, colHiStart;	//
	color colLoEnd, colHiEnd;		//
	float lifeSpanLo, lifeSpanHi;	

	void update(float dt) {
		//for (int i = 0; i < PART_SIZE; ++i) {
		//	if (particles[i].isActive())
		//		particles[i].refresh(dt);			
		//}

		for (auto it = parts.begin(); it != parts.end();) {
			it->refresh(dt);
			if (it->isActive()) it++;
			else				it.free(); //similar to ++ but will find next active
		}

		emissionTimer -= dt;
		while(emissionTimer < 0){		
			emit();
			emissionTimer = lerp(emitRateLo, emitRateHi, rand01());
			//emit a particle
		}
	}

};