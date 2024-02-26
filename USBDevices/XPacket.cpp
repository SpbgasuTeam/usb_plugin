#include "XPacket.h"

static bool comp(const XPacketField& a, const XPacketField& b) {
    return a.FieldID < b.FieldID;
}



XPacket XPacket::Create(uint8_t type, uint8_t subtype) {
    XPacket packet;
    packet.PacketType = type;
    packet.PacketSubtype = subtype;
    return packet;
}

vector<uint8_t> XPacket::ToPacket() {
    std::vector<uint8_t> packet;

    // Создание пакета
    packet.insert(packet.end(), { 0xAF, 0xAA, 0xAF, PacketType, PacketSubtype });

     
   // Сортировка полей по FieldID
   // sort(Fields.begin(), Fields.end(), comp);

    // Добавление полей в пакет
    for (const auto& field : Fields) {
        packet.insert(packet.end(), { static_cast<uint8_t>(field.FieldID), static_cast<uint8_t>(field.FieldSize) });
        packet.insert(packet.end(), field.Contents.begin(), field.Contents.end());


    }

    // Завершающий байт
    packet.insert(packet.end(), { 0xFF, 0x00 });

    return packet;
}

XPacket XPacket::Parse(std::vector<uint8_t> packet) {
    //Если длина пакета меньше 7 или заголовок не соответствует нужному
    if (packet.size() < 7 || packet[0] != 0xAF || packet[1] != 0xAA || packet[2] != 0xAF) {
        return XPacket(); // Возвращаем пустой объект
    }
    //Если пакет не заканчивается нужными символами
    size_t mIndex = packet.size() - 1;
    if (packet[mIndex - 1] != 0xFF || packet[mIndex] != 0x00) {
        return XPacket(); // Возвращаем пустой объект
    }

    uint8_t type = packet[3];
    uint8_t subtype = packet[4];
    XPacket xpacket = XPacket::Create(type, subtype);

    std::vector<uint8_t> fields(packet.begin() + 5, packet.end());

    while (true) {
        if (fields.size() < 2) {
            break;
        }

        uint8_t id = fields[0];
        uint8_t size = fields[1];
        std::vector<uint8_t> contents;
        if (size != 0 && fields.size() >= size + 2) {
            contents.assign(fields.begin() + 2, fields.begin() + 2 + size);
        }

        xpacket.Fields.push_back(XPacketField{ id, size, contents });

        size_t offset = 2 + size;
        if (fields.size() < offset) {
            break;
        }

        fields.erase(fields.begin(), fields.begin() + offset);
    }

    return xpacket;
}

