#pragma once

#include "Factory.h"

class GameState {
	Factory factory;
	
public:
	unsigned puff_sprite;

	void init(){
		puff_sprite = sfw::loadTextureMap("../res/particle_sprite.png");
	}

	void play() {
		for (int i = 0; i < 200; ++i)
			factory.spawnMouseAttractor(puff_sprite);
	}

	void update(float dt) {
		sfw::drawCircle(sfw::getMouseX(), sfw::getMouseY(), 12);			

		for (auto e = factory.begin(); e != factory.end();)
		{
			// Rendering System
			if (e->sprt)
			{
				e->sprt->draw(*e->tran);
			}

			// Lifetime management System
			if (e->life)
			{
				if (!(e->life->isAlive()))
				{
					factory.destroy(e);
					continue;
				}
				e->life->age(dt);
			}

			// Rigidbody Physics System
			if (e->rdby && e->tran)
			{
				e->rdby->integrate(*e->tran, dt);
			}

			// controller system
			if (e->cont  && e->rdby && e->tran)
			{
				e->cont->poll(*e->tran, *e->rdby);
			}

			// particle system
			if (e->part && e->life && e->tran && e->sprt)
			{
				e->part->update(*e->life, *e->tran, *e->sprt);
			}

			++e;
		}
	}
};
