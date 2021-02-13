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
        
        sort(ip_pool.begin(), ip_pool.end(), [](const IpStr& ippart_i1, const IpStr& ippart_i2) {
            for (int j = 0; j < 4; j++) {
                if (stoi(ippart_i1[j]) != stoi(ippart_i2[j]))
                    return stoi(ippart_i1[j]) > stoi(ippart_i2[j]);
            }
        });
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

        
        
        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;

}


