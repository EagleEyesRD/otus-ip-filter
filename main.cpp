#include "lib.h"
#include "basefuncs.h"

int main()
{
    try
    {
        

        StoreIp ip_pool;

        for (std::string line; std::getline(std::cin, line);)
        {
            IP v = split(line, '.');
            ip_pool.push_back(v);
        }
        
       

        
        auto compFunc = [](const IP& ippart_i1, const IP& ippart_i2) {
            for (int j = 0; j < 4; j++) {
                if ((ippart_i1[j]) != (ippart_i2[j]))
                    return (ippart_i1[j]) > (ippart_i2[j]);
            }
            return true;
        };

        sort(ip_pool.begin(), ip_pool.end(), compFunc);
        show(ip_pool);
        
        auto oneArg = [](const IP& ip) {return (ip[0]) == 1; };
        show(filter(ip_pool, oneArg));
        
        auto twoArgs = [](const IP& ip) {return (ip[0]) == 46 && (ip[1]) == 70; };
        show(filter(ip_pool, twoArgs));
        
        auto anyArgs = [](const IP& ip) {
            for (int j = 0; j < 4; j++) {
                if (ip[j] == 46)
                    return true;
            }
            return false;
        };
        show(filter(ip_pool, anyArgs));
        
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;

}


