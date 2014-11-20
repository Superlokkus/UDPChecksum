//
//  main.cpp
//  udp_checksum
//
//  Created by Markus Klemm on 12.11.14.
//  Copyright (c) 2014 net.markusklemm. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <cinttypes>
#include <cassert>

uint16_t udp_checksum (std::vector<uint8_t> packet)
{
    uint16_t checksum = 0;
    
    uint32_t temp_checksum = 0;
    
    if (packet.size() % 2)  //Padding
        packet.push_back(0);
    
    
    for (auto i = packet.cbegin(); i != packet.end(); i += 2)
    {
        temp_checksum +=  (uint16_t(*i) << 8) | *(i+1);
        temp_checksum = (temp_checksum & 0xffff) + (temp_checksum >> 16);
        temp_checksum = temp_checksum & 0xffff;
    }
    
    checksum = ~temp_checksum;
    
    if (checksum == 0) checksum = 0xffff;
    
    return checksum;
}

int main(int argc, const char * argv[]) {
    assert(udp_checksum({0xff,0xff,0xff,0xff}) == 0xffff);

    std::vector<uint8_t> packet;
    std::string input;

    std::cout << "Enter packet: " << std::endl;
    
    std::cin >> input;

    for( std::string::size_type i = 0; i != input.length(); i += 2 )
    {
        char t[3] = { input[i], input[i+1], '\0' };
        packet.push_back(std::strtoul(t, nullptr, 16));
    }
    
    std::cout << "Packet data was: \"";
    
    for (const auto &c : packet)
    {
        std::cout << std::hex <<c;
    }
    
    std::cout << "\"" << std::endl;
    
    std::cout << std::hex <<udp_checksum(packet) << std::endl;
    
    
    
    
    
    return 0;
}
