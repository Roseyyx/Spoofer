#pragma once

#include <iostream>

struct SMBIOSHeader {
    char anchorString[4];
    uint8_t checksum;
    uint8_t length;
    uint8_t majorVersion;
    uint8_t minorVersion;
    uint16_t tableLength;
    uint32_t tableAddress;
    uint16_t numOfStructures;
    uint8_t bcdRevision;
    uint8_t padding[5]; // Add padding to align struct members
};

namespace UEFI {
	bool Setup();

	void GetOldInfo();
};
