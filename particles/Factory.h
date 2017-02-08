#pragma once
#include "components.h"
#include "ObjectPool.h"

struct Entity {
	class Factory *factory;

	ObjectPool<transform>::iterator	tran;
	ObjectPool<rigidbody>::iterator	rdby;
	ObjectPool<controller>::iterator	cont;
	ObjectPool<sprite>::iterator		sprt;
	ObjectPool<lifetime>::iterator	life;
	ObjectPool<particle>::iterator	part;

	void onFree() {
		if (tran)tran.free();
		if (rdby)rdby.free();
		if (cont)cont.free();
		if (sprt)sprt.free();
		if (life)life.free();
		if (part)part.free();
	}
};

class Factory {
	ObjectPool<Entity>		entities;
	ObjectPool<transform>	transforms;
	ObjectPool<rigidbody>	rigidbodies;
	ObjectPool<controller>	controllers;
	ObjectPool<sprite>		sprites;
	ObjectPool<lifetime>	lifetimes;
	ObjectPool<particle>	particles;
public:
	Factory() : entities(512), transforms(512), rigidbodies(512), controllers(512),
		sprites(512), lifetimes(512), particles(512) 
	{ }

	ObjectPool<Entity>::iterator destroy(ObjectPool<Entity>::iterator &eit) { eit->onFree(); return eit.free(); }
	
	ObjectPool<Entity>::iterator begin() { return entities.begin(); }
	ObjectPool<Entity>::iterator end() { return entities.end(); }

	//transform, sprite, lifetime
	ObjectPool<Entity>::iterator spawnStaticImage(unsigned sprite_id, float x, float y, float w, float h, float time = -1) {
		ObjectPool<Entity>::iterator retval = entities.push();
		if (!retval) return retval;

		retval->factory = this;

		retval->tran = transforms.push();
		retval->sprt = sprites.push();

		retval->tran->position = vec2{ x,y };
		retval->tran->scale = vec2{ w,h };
		retval->sprt->sprite_id = sprite_id;

		if (time > 0) {
			retval->life = lifetimes.push();
			retval->life->time = time;
		}
		return retval;
	}

	ObjectPool<Entity>::iterator spawnMouseAttractor(unsigned sprite_id) {
		ObjectPool<Entity>::iterator retval = entities.push();
		if (!retval) return retval;
		retval->factory = this;

		retval->tran = transforms.push();
		retval->sprt = sprites.push();
		retval->cont = controllers.push();
		retval->rdby = rigidbodies.push();

		retval->tran->position = vec2{ rand01() * 800,rand01() * 600 };
		retval->tran->scale = vec2{ 32,32 };

		retval->sprt->sprite_id = sprite_id;
		retval->sprt->tint.ui_color = 0xffffff88;

		retval->cont->speed = rand01() * 60 + 20;

		return retval;
	}
};