#pragma once

#include <Windows.h>
#include <format>
#include <fstream>
#include <iostream>
#include <chrono>

#pragma region ConsoleLogColors
#define FOREGROUND_WHITE		    (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN)
#define FOREGROUND_YELLOW       	(FOREGROUND_RED | FOREGROUND_GREEN)
#define FOREGROUND_CYAN		        (FOREGROUND_BLUE | FOREGROUND_GREEN)
#define FOREGROUND_MAGENTA	        (FOREGROUND_RED | FOREGROUND_BLUE)
#define FOREGROUND_BLACK		    0

#define FOREGROUND_INTENSE_RED		(FOREGROUND_RED | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_GREEN	(FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_BLUE		(FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_WHITE	(FOREGROUND_WHITE | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_YELLOW	(FOREGROUND_YELLOW | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_CYAN		(FOREGROUND_CYAN | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_MAGENTA	(FOREGROUND_MAGENTA | FOREGROUND_INTENSITY)
#pragma endregion

#pragma region ConsoleLogErrorHandling
#ifdef _DEBUG
#define SEH_CATCH _RPT0(_CRT_ERROR, ex.what());
#else
#define SEH_CATCH std::abort();
#endif

#define SEH_START try {
#define SEH_END } catch (const std::exception& ex) {		\
	Console::PushConsoleColor(FOREGROUND_INTENSE_RED);			\
	Console::Print("Console Error", std::format("{}", ex.what()));	\
	Console::PopConsoleColor();									\
	SEH_CATCH }
#pragma endregion

namespace Console {
	inline FILE* pStream;
	inline std::uint16_t wConsoleColor = FOREGROUND_WHITE;
	inline std::ofstream ofsFile;

	bool Attach(const char* szConsoleTitle);

	void Detach();

	template <typename ... Args_t>
	void Print(const std::string Attribute, const std::string_view szText, const Args_t& ... argList) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSE_GREEN);
		std::cout << "[" + Attribute + "] ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wConsoleColor);
		if constexpr (sizeof...(argList) > 0)
			std::cout << std::vformat(szText, std::make_format_args(argList...)) << std::endl;
		else
			std::cout << szText << std::endl;
	}

	inline void PushConsoleColor(const std::uint16_t wColor) {
		wConsoleColor = wColor;
	}

	inline void PopConsoleColor() {
		wConsoleColor = FOREGROUND_WHITE;
	}
}