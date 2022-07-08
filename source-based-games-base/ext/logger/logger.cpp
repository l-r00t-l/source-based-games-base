#include "../../pch.h"
#include "logger.h"

void c_logger::set_title(const char* title)
{
	if (title != nullptr)
		SetConsoleTitle(title);
}

void c_logger::set_color(const uint8_t color /*= FOREGROUND_WHITE*/)
{
	SetConsoleTextAttribute(m_console, color);
}

void c_logger::print_colored(const char* text, const uint8_t color /*= FOREGROUND_WHITE*/)
{
	set_color(color);
	::printf(text);
	set_color();
}

void c_logger::init(const char* title /*= nullptr*/, log_t log_level /*= log_t::none*/) noexcept
{
	AllocConsole();
	set_title(title);
	m_console = GetStdHandle(STD_OUTPUT_HANDLE);
	freopen_s(&m_stdin_dummy, "CONIN$", "r", stdin);
	freopen_s(&m_stdout_dummy, "CONOUT$", "w", stdout);
	std::cout.clear();
	std::cin.clear();
}

void c_logger::destroy() noexcept
{
	if (m_stdin_dummy)
		fclose(m_stdin_dummy);

	if (m_stdout_dummy)
		fclose(m_stdout_dummy);
	
	FreeConsole();
}

void c_logger::greeting()
{
	::printf("Welcome back, "); print_colored("r00t", FOREGROUND_INTENSE_BLUE | FOREGROUND_INTENSE_GREEN); ::printf("!\n");
	printf(log_t::info, "Build date: %s %s", __DATE__, __TIME__);
}

void c_logger::printf(const log_t level, const char* _format, ...)
{
	set_color();
	switch (level)
	{
	case log_t::none:
		break;
	case log_t::debug:
		print_colored("[*] ", FOREGROUND_MAGENTA);
		break;
	case log_t::info:
		print_colored("[+] ", FOREGROUND_INTENSE_GREEN);
		break;
	case log_t::warning:
		print_colored("[!] ", FOREGROUND_RED | FOREGROUND_YELLOW);
		break;
	case log_t::error:
		print_colored("[-] ", FOREGROUND_RED);
		break;
	case log_t::critical:
		print_colored("[x] ", FOREGROUND_INTENSE_RED);
		break;
	case log_t::always:
		break;
	default:
		break;
	}

	va_list argptr;
	va_start(argptr, _format);
	vprintf(_format, argptr); // Printing
	va_end(argptr);
	::printf("\n");
}