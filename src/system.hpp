#ifndef ECS_SYSTEM_HPP
#define ECS_SYSTEM_HPP

#include "registry.hpp"

namespace ecs
{
    class System
    {
    
	public:
		virtual ~System() {}

		virtual void configure(Registry* registry)
		{
		}

		virtual void unconfigure(Registry* registry)
		{
		}

		virtual void update(Registry* registry, float delta_time)
		{
		}
    };
} // ecs


#endif