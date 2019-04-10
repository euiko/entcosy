#ifndef ENTCOSY_SYSTEM_HPP
#define ENTCOSY_SYSTEM_HPP

#include "registry.hpp"

namespace entcosy
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