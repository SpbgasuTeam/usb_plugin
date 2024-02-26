#pragma once
#include <cstddef>
#include <cstdint>
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


//Описание поля пакета
class XPacketField {
public:
    uint8_t FieldID;
    uint8_t FieldSize;
    vector<uint8_t> Contents;


};

//Свойства пакета
class XPacket {

public:
    uint8_t PacketSubtype;
    uint8_t PacketType;
    list<XPacketField> Fields;

    static XPacket Create(uint8_t type, uint8_t subtype);

    vector<uint8_t> ToPacket();
        
    static XPacket Parse(std::vector<uint8_t> packet);
       
   
private:
    XPacket() {};



};


