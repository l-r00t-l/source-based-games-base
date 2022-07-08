#pragma once
#include "../singleton/singleton.h"

#pragma region colors
#define FOREGROUND_WHITE		    (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN)
#define FOREGROUND_YELLOW       	(FOREGROUND_RED | FOREGROUND_GREEN)
#define FOREGROUND_CYAN		        (FOREGROUND_BLUE | FOREGROUND_GREEN)
#define FOREGROUND_MAGENTA	        (FOREGROUND_RED | FOREGROUND_BLUE)
#define FOREGROUND_BLACK		    0
#define FOREGROUND_GREY				8

#define FOREGROUND_INTENSE_RED		(FOREGROUND_RED | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_GREEN	(FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_BLUE		(FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_WHITE	(FOREGROUND_WHITE | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_YELLOW	(FOREGROUND_YELLOW | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_CYAN		(FOREGROUND_CYAN | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_MAGENTA	(FOREGROUND_MAGENTA | FOREGROUND_INTENSITY)
#pragma endregion

enum class log_t {
	none = 0,
	debug,
	info,
	warning,
	error,
	critical,
	always
};

class c_logger : public c_singleton<c_logger>
{
	FILE*	m_stdin_dummy = nullptr;
	FILE*	m_stdout_dummy = nullptr;
	HANDLE	m_console;
	log_t	m_max_log_level = log_t::none;
private:
	void set_title(const char* title);
	void set_color(const uint8_t color = FOREGROUND_WHITE);
	void print_colored(const char* text, const uint8_t color = FOREGROUND_WHITE);
public:
	void init(const char* title = nullptr, log_t log_level = log_t::none) noexcept;
	void destroy() noexcept;

	void greeting();
	void printf(const log_t level, const char* _format, ...);
};