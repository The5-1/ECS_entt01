#pragma once

#include <entt/entt.hpp>

#include <cstdint>
#include <iostream>

#include "utility_profiling.h"

namespace entt_test01 {


	struct Position {
		float x;
		float y;
	};

	struct Velocity {
		float dx;
		float dy;
	};

	void update(entt::DefaultRegistry &registry) {
		auto view = registry.view<Position, Velocity>();

		for (auto entity : view) {
			// gets only the components that are going to be used ...

			auto &velocity = view.get<Velocity>(entity);

			velocity.dx = 0.;
			velocity.dy = 0.;

			// ...
		}
	}

	void update(std::uint64_t dt, entt::DefaultRegistry &registry) {
		registry.view<Position, Velocity>().each([dt](auto entity, auto &position, auto &velocity) {
			// gets all the components of the view at once ...

			position.x += velocity.dx * dt;
			position.y += velocity.dy * dt;

			// ...
		});
	}

	int test() {
		entt::DefaultRegistry registry;
		std::uint64_t dt = 16;

		{
			SCOPETIMER();
			
			auto num = 1000000;
			printf("Creating %i entities...", num);
			for (auto i = 0; i < num; ++i) {
				auto entity = registry.create();
				registry.assign<Position>(entity, i * 1.f, i * 1.f);
				if (i % 2 == 0) {
					registry.assign<Velocity>(entity, i * .1f, i * .1f);
				}
			}
			printf("done!\n");
			// takes about 90ms in Release build
		}

		{
			SCOPETIMERAVG(1000);
			for (auto i = 0; i < 1000; i++)
			{

				update(dt, registry);
			}
			//takes about 3ms to update all entities
		}

		update(registry);


		return 0;
	}
}