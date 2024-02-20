#include <cstddef>
#include <cstdint>
#include <list>

class XPacketField {
public:
    uint8_t FiledID;
    uint8_t FieldSize;
    uint8_t Contents;

}

class packet {
public:
    uint8_t PacketSubtype;
    uint8_t PacketType;
    list<XPacketField> Fields

}