#ifndef ENTCOSY_CONFIG_HPP
#define ENTCOSY_CONFIG_HPP

#include<cstdint>

namespace entcosy
{
    typedef enum 
    {
        ENTCOSY_DEBUG = 0x00000001
    } ENTCOSY_CONFIG;

    class Config
    {
    public:
        static Config &get()
        {
            static Config config;
            return config;
        }

        void set(uint32_t configs)
        {
            m_configs = configs;
        }

        bool isEnabled(const ENTCOSY_CONFIG &config)
        {
            if((m_configs & config) == config)
                return true;
            return false;
        }

    private:
        uint32_t m_configs;
    };
} // entcosy


#endif