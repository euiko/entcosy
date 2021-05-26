#include <iostream>
#include <vector>
#include <deque>
#include <ctime>
#include <rttr/type>
#include <fstream>
#include <entcosy/registry.hpp>

struct PlayerTag
{
    ENTCOSY_DECLARE_TYPE;

    template<class Archive>
    void serialize(Archive &ar)
    {
    }
};

struct EnemyTag
{
    ENTCOSY_DECLARE_TYPE;

    template<class Archive>
    void serialize(Archive &ar)
    {
    }
};

struct PositionComponent
{
    ENTCOSY_DECLARE_TYPE;
    int x, y;

    PositionComponent() : x(0), y(0) { }

    PositionComponent(const int &x, const int &y) : x(x), y(y) { }

    template<class Archive>
    void serialize(Archive &ar)
    {
        ar(x, y);
    }
};

struct VelocityComponent
{
    ENTCOSY_DECLARE_TYPE;
    int speed;

    template<class Archive>
    void serialize(Archive &ar)
    {
        ar(speed);
    }
};

ENTCOSY_INITIALIZATION;
RTTR_REGISTRATION {
    ENTCOSY_BEGIN_DEFINE;
    //template<> entcosy::core::TypeRegistry entcosy::events::OnComponentAssigned<VelocityComponent>::__ENTCOSY_type_reg;
    ENTCOSY_DEFINE_TYPE(PlayerTag);
    ENTCOSY_DEFINE_TYPE(EnemyTag);
    ENTCOSY_DEFINE_TYPE(PositionComponent);
    ENTCOSY_DEFINE_TYPE(VelocityComponent);

    rttr::registration::class_<PositionComponent>("PositionComponent")
        .constructor<const int&, const int&>()
        .property("x", &PositionComponent::x)
        .property("y", &PositionComponent::y);
}

ENTCOSY_SERIALIZATION_REGISTER(PlayerTag);
ENTCOSY_SERIALIZATION_REGISTER(EnemyTag);
ENTCOSY_SERIALIZATION_REGISTER(PositionComponent);
ENTCOSY_SERIALIZATION_REGISTER(VelocityComponent);

struct Timer final {
    Timer(): start{std::chrono::system_clock::now()} {}

    void elapsed() {
        auto now = std::chrono::system_clock::now();
        std::cout << std::chrono::duration<double>(now - start).count() << " seconds" << std::endl;
    }

private:
    std::chrono::time_point<std::chrono::system_clock> start;
};


int main()
{
    std::shared_ptr<entcosy::Registry> registry = std::make_shared<entcosy::Registry>();
    Timer timer;
    {
        std::ofstream os("out.cereal", std::ios::binary);
        cereal::BinaryOutputArchive archive( os );
        for(int i = 0; i < 99; i++)
        {
            std::shared_ptr<entcosy::Entity> entity = registry->create();
            entity->assign<PositionComponent>(rand(), rand());
            entity->assign<VelocityComponent>(i);
        }
        archive( registry );
        os.close();
    }
    {
        std::ifstream is("out.cereal", std::ios::binary);
        cereal::BinaryInputArchive archive( is );
        std::shared_ptr<entcosy::Registry> registry;
        archive(registry);

        registry->each<PositionComponent, VelocityComponent>([&](std::shared_ptr<entcosy::Entity> ent, PositionComponent *pc,
            VelocityComponent *vc
        )
        {
            ent->all([&](rttr::type componentType, rttr::variant value)
            {
                std::cout << componentType.get_name() << "\n";
                for(auto &property: componentType.get_properties())
                {
                    rttr::variant m = property.get_value(value);
                    std::cout << property.get_name() << " = " << m.to_int() << "\n";
                }
                std::cout << "\n";
            });

            // std::cout << "Entity " << ent->getEntityId() << ": Position("<<pc->x<<","<<pc->y<<")"
            //     << " and Velocity("<< vc->speed <<")\n";
        });
    }
    timer.elapsed();
    return 0;
}
