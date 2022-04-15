/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libassert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:34:09 by susami            #+#    #+#             */
/*   Updated: 2022/04/15 15:30:46 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
static size_t	counter = 0;
static void	start_test(void)
{
	printf("%zu.", ++counter);
	fflush(stdout);
}

static void	print_ok(void)
{
	printf(ANSI_COLOR_GREEN "OK " ANSI_COLOR_RESET);
	fflush(stdout);
}

static void	print_ko(void)
{
	printf(ANSI_COLOR_RED "KO " ANSI_COLOR_RESET);
	fflush(stdout);
}

static void print_error(char *fmt, ...)
{
	va_list	args;
	va_start(args, fmt);
	//fprintf(stderr, ANSI_COLOR_RED);
	vfprintf(stderr, fmt, args);
	//fprintf(stderr, ANSI_COLOR_RESET);
	va_end(args);
}

void	ASSERT_TRUE(bool actual,
	char *caller_file, const char *caller_func, int caller_line)
{
	start_test();
	if (actual == false)
	{
		print_ko();
		print_error("[test %zu] %s failed: ", __func__);
		print_error("func %s at file %s, line %d\n",
			caller_func, caller_file, caller_line);
		return ;
	}
	else
		print_ok();
}

void	ASSERT_EQ_I(int actual, int expected,
	char *caller_file, const char *caller_func, int caller_line)
{
	start_test();
	if (actual != expected)
	{
		print_ko();
		print_error("[test %zu] %s failed: (\"%i\") is not equal to expected (\"%i\"). ",
			counter, __func__, actual, expected);
		print_error("func %s at file %s, line %d\n",
			caller_func, caller_file, caller_line);
		return ;
	}
	else
		print_ok();
}

void	ASSERT_EQ_UI(unsigned int actual, unsigned int expected,
	char *caller_file, const char *caller_func, int caller_line)
{
	if (actual != expected)
	{
		print_error("[test %zu] %s failed: (\"%u\") is not equal to expected (\"%u\"). ",
			__func__, actual, expected);
		print_error("func %s at file %s, line %d\n",
			caller_func, caller_file, caller_line);
	}
}

void	ASSERT_EQ_L(long actual, long expected,
	char *caller_file, const char *caller_func, int caller_line)
{
	if (actual != expected)
	{
		print_error("[test %zu] %s failed: (\"%li\") is not equal to expected (\"%li\"). ",
			counter, __func__, actual, expected);
		print_error("func %s at file %s, line %d\n",
			caller_func, caller_file, caller_line);
	}
}

void	ASSERT_EQ_UL(unsigned long actual, unsigned long expected,
	char *caller_file, const char *caller_func, int caller_line)
{
	if (actual != expected)
	{
		print_error("[test %zu] %s failed: (\"%lu\") is not equal to expected (\"%lu\"). ",
			counter, __func__, actual, expected);
		print_error("func %s at file %s, line %d\n",
			caller_func, caller_file, caller_line);
	}
}

void	ASSERT_EQ_LL(long long actual, long long expected,
	char *caller_file, const char *caller_func, int caller_line)
{
	if (actual != expected)
	{
		print_error("[test %zu] %s failed: (\"%lli\") is not equal to expected (\"%lli\"). ",
			counter, __func__, actual, expected);
		print_error("func %s at file %s, line %d\n",
			caller_func, caller_file, caller_line);
	}
}

void	ASSERT_EQ_ULL(unsigned long long actual, unsigned long long expected,
	char *caller_file, const char *caller_func, int caller_line)
{
	if (actual != expected)
	{
		print_error("[test %zu] %s failed: (\"%llu\") is not equal to expected (\"%llu\"). ",
			counter, __func__, actual, expected);
		print_error("func %s at file %s, line %d\n",
			caller_func, caller_file, caller_line);
	}
}

void	ASSERT_EQ_SIZE(size_t actual, size_t expected,
	char *caller_file, const char *caller_func, int caller_line)
{
	if (actual != expected)
	{
		print_error("[test %zu] %s failed: (\"%zu\") is not equal to expected (\"%zu\"). ",
			counter, __func__, actual, expected);
		print_error("func %s at file %s, line %d\n",
			caller_func, caller_file, caller_line);
	}
}

void	ASSERT_EQ_STR(char *actual, char *expected, size_t size,
	char *caller_file, const char *caller_func, int caller_line)
{
	if (strncmp(actual, expected, size) != 0)
	{
		print_error("[test %zu] %s failed: (\"%s\") is not equal to expected (\"%s\"). ",
			counter, __func__, actual, expected);
		print_error("func %s at file %s, line %d\n",
			caller_func, caller_file, caller_line);
	}
}

static const char	*g_base16 = "0123456789abcdef";

static void	hexdump(void *p, size_t size)
{
	unsigned char	*ptr;
	size_t			i;
	char			c;

	ptr = (unsigned char *)p;
	i = 0;
	while (i < size)
	{
		c = *(ptr + i);
		print_error("%c%c", g_base16[(c >> 4) & 0x0f], g_base16[c & 0x0f]);
		i++;
	}
}

#include <malloc/malloc.h>
void	ASSERT_EQ_MEM(void *actual, void *expected, size_t size,
	char *caller_file, const char *caller_func, int caller_line)
{
	start_test();
	if (expected == NULL || actual == NULL)
	{
		if (expected != actual)
		{
			print_ko();
			print_error("[test %zu] %s failed: \"%p\" is not equal to expected \"%p\"", counter, __func__, actual, expected);
		}
		else
			print_ok();
		return ;
	}
		
	if (malloc_size(actual) != malloc_size(expected))
	{
		print_ko();
		print_error("[test %zu] %s failed: malloc_size \"%i\" is not equal to expected \"%i\"", counter, __func__, malloc_size(actual), malloc_size(expected));
		return ;
	}
	if (memcmp(actual, expected, size) != 0)
	{
		print_ko();
		print_error("[test %zu] %s failed: hexdump (\"", counter, __func__);
		hexdump(actual, size);
		print_error("\") is not equal to expected (\"");
		hexdump(expected, size);
		print_error("\"). ");
		print_error("func %s at file %s, line %d\n",
			caller_func, caller_file, caller_line);
	}
	else
		print_ok();
}