#include "XPacket.h"

int main() {
    // ������ ������������� ������� Parse
    std::vector<uint8_t> packetData = { 0xAF, 0xAA, 0xAF, 0x01, 0x02, 0x03, 0x0C, 0x07, 0x07, 0x07, 0x07,0x07,0x07,0x07,0x07,0x07,0x07, 0xFF, 0x00 };
                                      //3 ���� ��������� /��� /������/ id  /����� /�������                                            /����������� ����         
    XPacket parsedPacket = XPacket::Parse(packetData);

    // ����� ������ ������������� ������
    std::cout << "Parsed Packet Type: " << +parsedPacket.PacketType << std::endl;
    std::cout << "Parsed Packet Subtype: " << +parsedPacket.PacketSubtype << std::endl;

    // ����� ������ ����� Fields
    for (const auto& field : parsedPacket.Fields) {
        std::cout << "Field ID: " << +field.FieldID << std::endl;
        std::cout << "Field Size: " << +field.FieldSize << std::endl;
        std::cout << "Field Contents:";
        for (const auto& content : field.Contents) {
            std::cout << " " << +content;
        }
        std::cout << std::endl;
    }

    return 0;
}