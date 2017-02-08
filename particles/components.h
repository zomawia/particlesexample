#pragma once

#include "maths.h"
#include "sfwdraw.h"
#include "ObjectPool.h"

struct transform {
	vec2 position, scale;
	float angle;
};

struct rigidbody {
	vec2 velocity, accel;
	
	void integrate(transform &T, float dt) {
		velocity = velocity + accel * dt;
		T.position = velocity * dt;		
	}
};

struct lifetime {
	float time = 0, lifespan;

	void age(float dt) { time += dt; }
	bool isAlive() const { return time < lifespan; }
	float pctAlive() const { return time / lifespan; }
	
};

struct sprite {
	size_t sprite_id;
	color tint = { WHITE };
	void draw(const transform &T) {
		sfw::drawTexture(sprite_id, T.position.x, T.position.y,
			T.scale.x, T.scale.y, T.angle, true, 0, tint.ui_color);
	}
};

struct controller {
	float speed;
	void poll(transform &T, rigidbody &RB) {
		vec2 mouse = vec2{ sfw::getMouseX(), sfw::getMouseY() };

		RB.accel = normal(T.position - mouse) * speed;
	}
};

struct particle {
	vec2 sDim, eDim;
	color sColor, eColor;
	void update(const lifetime &life, transform &trans, sprite &sprt){
		trans.scale = lerp(sDim, eDim, life.pctAlive());
		sprt.tint = lerp(sColor, eColor, life.pctAlive());
	}
};

//templated alias or templated typedef
template<typename T> using obpool = ObjectPool<T>::iterator;
struct Entity {
	obpool<transform>	tran;
	obpool<rigidbody>	rdby;
	obpool<controller>	cont;
	obpool<sprite>		sprt;
	obpool<lifetime>	life;
	obpool<particle>	part;

	void onFree() {
		if(tran)tran.free();
		if(rdby)rdby.free();
		if(cont)cont.free();
		if(sprt)sprt.free();
		if(life)life.free();
		if(part)part.free();
	}
};