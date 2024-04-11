#include "console.h"
#include "UEFI.h"

bool shouldStop = false;

int main() {

	try
	{
		if (!Console::Attach("Seismic Spoofer"))
			return 0;

		Console::Print("Seismic", "Attached");

		if (!UEFI::Setup())
			Console::Print("UEFI", "Failed to setup UEFI");
	}
	catch (const std::exception& e)
	{
		return 0;
	}

	return 0;
}