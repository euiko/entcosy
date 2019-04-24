#include <iostream>
#include <vector>
#include <deque>
#include <ctime>
#include <fstream>
#include "entcosy/registry.hpp"

struct PlayerTag
{
    ENTCOSY_DECLARE_TYPE;
};

struct EnemyTag
{
    ENTCOSY_DECLARE_TYPE;
};

struct PositionComponent
{
    ENTCOSY_DECLARE_TYPE;
    int x, y;
};

struct VelocityComponent
{
    ENTCOSY_DECLARE_TYPE;
    int x, y;
};

ENTCOSY_INITIALIZATION;
ENTCOSY_DEFINE_TYPE(PlayerTag);
ENTCOSY_DEFINE_TYPE(EnemyTag);
ENTCOSY_DEFINE_TYPE(PositionComponent);
ENTCOSY_DEFINE_TYPE(VelocityComponent);


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
    entcosy::Registry registry;
    Timer timer;
    std::ofstream os("out.cereal", std::ios::binary);
    // cereal::BinaryOutputArchive archive( os );
    // archive( registry );
    for(int i = 0; i < 999; i++)
    {
        std::shared_ptr<entcosy::Entity> entity = registry.create();
        entity->assign<PositionComponent>(1, 1);
        entity->assign<VelocityComponent>(1, 1);
    }



    timer.elapsed();
    std::unordered_map<int, std::vector<int>> map;
    int last = 0;
    for(size_t key = 0; key < 10; key++)
    {
        std::vector<int> v;
        for(int val = last; val < last+5; val++)
        {
            v.push_back(val);
        }
        map.insert({key, v});
        last++;
    }

    for(auto& kv : map)
    {
        std::cout << "Key " << kv.first << " : ";
        for(auto& value: kv.second)
        {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << std::endl;
    
    std::cout << "Remove..." << std::endl;
    for(auto& kv : map)
    {
        std::cout << "Key " << kv.first << " : ";
        auto begin = std::remove(kv.second.begin(), kv.second.end(), 5);
        auto end = kv.second.end();
        for(auto i = begin; i != end; i++)
        {
            std::cout << *i << " ";
        }
        std::cout << std::endl;
        // end--;
        // end--;
        kv.second.erase(end, end);
        std::cout << "\tProcessing..." << std::endl;
        std::cout << "\t";
        for(auto& v : kv.second)
        {
            std::cout << v << " ";
        }
        std::cout << "\n";
    }

    return 0;
}