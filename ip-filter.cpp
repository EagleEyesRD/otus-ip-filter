#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
using StoreIp = std::vector<std::vector<std::string>>;
using IpStr = std::vector<std::string>;

IpStr split(const std::string& str, char d)
{
    IpStr r;
    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while (stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

void show(const StoreIp& s) {
    for (StoreIp::const_iterator ip = s.cbegin(); ip != s.cend(); ++ip)
    {
        for (IpStr::const_iterator ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
        {
            if (ip_part != ip->cbegin())
            {
                std::cout << ".";

            }
            std::cout << *ip_part;
        }
        std::cout << std::endl;
    }
}

template<typename T>
StoreIp filter(const StoreIp& ipPool, T compareFunc) {
    StoreIp ipFilt;
    for (auto&& ip : ipPool)
        if (compareFunc(ip))
            ipFilt.emplace_back(ip);
    return ipFilt;
}


int main()
{
    try
    {
        StoreIp ip_pool;
        
        for (std::string line; std::getline(std::cin, line);)
        {
            IpStr v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }
        
        auto compFunc = [](const IpStr& ippart_i1, const IpStr& ippart_i2) {
            for (int j = 0; j < 4; j++) {
                if (stoi(ippart_i1[j]) != stoi(ippart_i2[j]))
                    return stoi(ippart_i1[j]) > stoi(ippart_i2[j]);
            }
        };

        sort(ip_pool.begin(), ip_pool.end(), compFunc);
        show(ip_pool);

        auto oneArg = [](const IpStr& ip) {return stoi(ip[0]) == 1; };
        show(filter(ip_pool, oneArg));
        
        auto twoArgs = [](const IpStr& ip) {return stoi(ip[0]) == 46 && stoi(ip[1]) == 70; };
        show(filter(ip_pool, twoArgs));
        
        auto anyArgs = [](const IpStr& ip) {
            for (int j = 0; j < 4; j++) {
                if (stoi(ip[j]) == 46)
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


