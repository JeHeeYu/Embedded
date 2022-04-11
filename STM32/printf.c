#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int _write(int file, char *p, int len);
void User_Printf(const char *fmt, ...);
void vprint(const char *fmt, va_list argp);

int _write(int file, char *p, int len)
{
	HAL_UART_Transmit(&huart3, p, len, 10);

	return len;
}

void vprint(const char *fmt, va_list argp) {
	char string[200];
	if (0 < vsprintf(string, fmt, argp))
			{
		HAL_UART_Transmit(&huart3, (uint8_t*) string, strlen(string), 0xffffff);
	}
}

void User_Printf(const char *fmt, ...)
{
	va_list argp;
	va_start(argp, fmt);
	vprint(fmt, argp);
	va_end(argp);
}
