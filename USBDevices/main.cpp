#include "XPacket.h"
#include "COMPorts.h"

void printParsedPacket(XPacket parsedPacket);


int main() {
    // Пример использования функции Parse
    //std::vector<uint8_t> packetData = { 0xAF, 0xAA, 0xAF, 0x01, 0x02, 0x03, 0x09,      0x05, 0x00, 0x05, 0x01, 0x08, 0x00, 0x00, 0x08, 0x05,          0xFF, 0x00 };
    //                                  //3 бита протокола /тип /подтип/ id  /длина контента                   /контент                                /закрывающие биты         
    //XPacket parsedPacket = XPacket::Parse(packetData);
    //printParsedPacket(parsedPacket);
    
    
    //readComPorts();
     
    const char* portName = "LCOM7";  // Номер COM-порта
        const char* data = "OK";  // Данные для отправки

    while (true) {
        
        writeToCOMPort(portName, data);
        Sleep(1000);
    }
    


    return 0;
}


void printParsedPacket(XPacket parsedPacket) {
    // Вывод данных распарсенного пакета
    std::cout << "Parsed Packet Type: " << +parsedPacket.PacketType << std::endl;
    std::cout << "Parsed Packet Subtype: " << +parsedPacket.PacketSubtype << std::endl;


    // Вывод данных полей Fields
    for (const auto& field : parsedPacket.Fields) {
        std::cout << "Field ID: " << +field.FieldID << std::endl;
        std::cout << "Field Size: " << +field.FieldSize << std::endl;
        std::cout << "Field Contents:";
        for (const auto& content : field.Contents) {
            std::cout << " " << +content;
        }
        std::cout << std::endl;
    }
}