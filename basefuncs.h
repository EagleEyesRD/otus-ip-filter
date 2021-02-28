#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <array>
using namespace std;
using IP = std::array<uint8_t, 4>;
using StoreIp = std::vector<IP>;

IP split(const std::string& str, char d)
{
    IP r = { 0,0,0,0 };
    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    int index_arr = 0;
    while (stop != std::string::npos)
    {
        r.at(index_arr) = stoi(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
        index_arr++;
    }

    r.at(index_arr) = stoi(str.substr(start));

    return r;
}

ostream& operator<<(ostream& os, const IP& ip)
{
    os << to_string(ip.at(0)) << '.' << to_string(ip.at(1)) << '.' << to_string(ip.at(2)) << '.' << to_string(ip.at(3));
    return os;
}

void show(const StoreIp& s) {
    for (StoreIp::const_iterator ip = s.cbegin(); ip != s.cend(); ++ip)
    {
        std::cout << *ip << std::endl;
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

