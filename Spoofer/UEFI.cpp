#include "UEFI.h"

bool UEFI::Setup() {
	GetOldInfo();

	return true;
}

void UEFI::GetOldInfo() {
	SMBIOSHeader* header = (SMBIOSHeader*)0xF0000;

    if (header->anchorString[0] == '_' && header->anchorString[1] == 'S' && header->anchorString[2] == 'M' && header->anchorString[3] == '_') {
        std::cout << "SMBIOS version: " << static_cast<int>(header->majorVersion) << "." << static_cast<int>(header->minorVersion) << std::endl;
        std::cout << "Number of SMBIOS structures: " << header->numOfStructures << std::endl;

        // Read and parse SMBIOS structures from the tableAddress
    }
    else {
        std::cerr << "SMBIOS table not found." << std::endl;
    }

}