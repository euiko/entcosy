#ifndef ENTCOSY_SYSTEM_HPP
#define ENTCOSY_SYSTEM_HPP

#include "registry.hpp"


namespace entcosy
{
    class System
    {

	public:
		virtual ~System() {}

		virtual void configure(std::shared_ptr<Registry> registry)
		{
		}

		virtual void unconfigure(std::shared_ptr<Registry> registry)
		{
		}

		virtual void update(std::shared_ptr<Registry> registry, float delta_time)
		{
		}
    };
} // ecs


#endif
