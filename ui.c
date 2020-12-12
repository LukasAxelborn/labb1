#include "ui.h"
#include "io.h"
#include "analyze.h"

#include <stdbool.h>
#include <stdio.h>

//
// Private
//
static void ui_invalid_input()
{
	printf("info> bad input\n");
}

static void ui_exit()
{
	printf("info> bye\n");
}

static char ui_get_choice()
{
	char buf[3];

	printf("input> ");
	return read_line(buf, 3) ? buf[0] : 0;
}

static void ui_line(char c, int n)
{
	while (n-- > 0)
	{
		putchar(c);
	}
	putchar('\n');
}

static void ui_menu_options(const char *options[], int num_options)
{
	int i;

	for (i = 0; i < num_options; i++)
	{
		printf("    %c) %s\n", 'a' + i, options[i]);
	}
}

static void ui_menu()
{
	const char *options[] = {
		"Menu",
		"Exit\n",
		"Bubble sort best case",
		"Bubble sort worst case",
		"Bubble sort avarage case\n",
		"Insertion sort best case",
		"Insertion sort worst case",
		"Insertion sort avarage case\n",
		"Quick sort best case",
		"Quick sort worst case",
		"Quick sort avarage case\n",
		"Linear search best case",
		"Linear search worst case",
		"Linear search avarage case\n",
		"Binary search best case",
		"Binary search worst case",
		"Binary search avarage case\n",
	};

	ui_line('=', MENU_WIDTH);
	ui_menu_options(options, sizeof(options) / sizeof(char *));
	ui_line('-', MENU_WIDTH);
}

/////////////////////////////////////////////////////
//mina extra funtkrioner för gränsnitet

double _internal_math_divide_log(result_t keeper, int choise)
{
	return !choise ? (keeper.time / log(keeper.size)) : (keeper.time / (keeper.size * log(keeper.size)));
}
double _internal_math_divide_pow(result_t keeper, int power)
{
	return keeper.time / pow(keeper.size, power);
}
char *_internal_get_function_name(int a)
{
	switch (a)
	{
	case 0:
		return "Bubble Sort";
		break;
	case 1:
		return "Insertion Sort";
		break;
	case 2:
		return "Quick Sort";
		break;
	case 3:
		return "Linear Search";
		break;
	case 4:
		return "Binary Search";
		break;

	default:

		printf("choice finns inte");
		return NULL;
		break;
	}
}
char *_internal_get_case_senario(int c)
{
	switch (c)
	{
	case 0:
		return "Best";
		break;
	case 1:
		return "Worst";
		break;
	case 2:
		return "Average";
		break;

	default:

		printf("choice finns inte");
		return NULL;
		break;
	}
}
void _internal_print_top(int a, int c)
{
	ui_line('*', MENU_WIDTH);
	printf("%*s: %s\n", (MENU_WIDTH / 2), _internal_get_function_name(a), _internal_get_case_senario(c));
	ui_line('~', MENU_WIDTH);
}

//////////
//skriver ut för sortering
//skriver ut bästa reultatet
void _internal_print_results_best_sorted(result_t *result, int a, int c)
{
	_internal_print_top(a, c);

	printf("size\t time T(s)\t T/logn\t\t T/n\t\t T/nlogn\n");
	ui_line('~', MENU_WIDTH);

	for (int i = 0; i < RESULT_ROWS; i++)
	{
		printf("%d\t %.8f\t %.8e\t %.8e\t %.8e\n", result[i].size, result[i].time, _internal_math_divide_log(result[i], 0), _internal_math_divide_pow(result[i], 1), _internal_math_divide_log(result[i], 1));
	}
}
//skriver ut värsta reultatet
void _internal_print_results_worst_sorted(result_t *result, int a, int c)
{
	_internal_print_top(a, c);

	printf("size\t time T(s)\t T/nlogn\t T/n^2\t\t T/n^3\n");
	ui_line('~', MENU_WIDTH);

	for (int i = 0; i < RESULT_ROWS; i++)
	{
		printf("%d\t %.8f\t %.8e\t %.8e\t %.8e\n", result[i].size, result[i].time, _internal_math_divide_log(result[i], 1), _internal_math_divide_pow(result[i], 2), _internal_math_divide_pow(result[i], 3));
	}
}
//skriver ut meddelunda reultatet
void _internal_print_results_avarage_sorted(result_t *result, int a, int c)
{
	_internal_print_top(a, c);

	printf("size\t time T(s)\t T/logn\t\t T/n\t\t T/n^2\n");
	ui_line('~', MENU_WIDTH);

	for (int i = 0; i < RESULT_ROWS; i++)
	{
		printf("%d\t %.8f\t %.8e\t %.8e\t %.8e\n", result[i].size, result[i].time, _internal_math_divide_log(result[i], 0), _internal_math_divide_pow(result[i], 1), _internal_math_divide_pow(result[i], 2));
	}
}
//////////

//////////
//skriver ut för sök
void _internal_print_results_best_search(result_t *result, int a, int c)
{
	_internal_print_top(a, c);

	printf("size\t time T(s)\t T/n\t\t T/1\t\t T/nlogn\n");
	ui_line('~', MENU_WIDTH);

	for (int i = 0; i < RESULT_ROWS; i++)
	{
		printf("%d\t %.8f\t %.8e\t %.8e\t %.8e\n", result[i].size, result[i].time, _internal_math_divide_pow(result[i], 1), result[i].time, _internal_math_divide_log(result[i], 1));
	}
}

void _internal_print_results_worst_search(result_t *result, int a, int c)
{
	_internal_print_top(a, c);

	printf("size\t time T(s)\t T/logn\t\t T/n\t\t T/nlogn\n");
	ui_line('~', MENU_WIDTH);

	for (int i = 0; i < RESULT_ROWS; i++)
	{
		printf("%d\t %.8f\t %.8e\t %.8e\t %.8e\n", result[i].size, result[i].time, _internal_math_divide_log(result[i], 0), _internal_math_divide_pow(result[i], 1), _internal_math_divide_log(result[i], 1));
	}
}

void _internal_print_results_avarage_search(result_t *result, int a, int c)
{
	_internal_print_top(a, c);

	printf("size\t time T(s)\t T/logn\t\t T/(n/2)\t T/nlogn\n");
	ui_line('~', MENU_WIDTH);

	for (int i = 0; i < RESULT_ROWS; i++)
	{
		printf("%d\t %.8f\t %.8e\t %.8e\t %.8e\n", result[i].size, result[i].time, _internal_math_divide_log(result[i], 0), result[i].time / (result[i].size / 2), _internal_math_divide_log(result[i], 1));
	}
}
//////////
void _internal_print_results(int a, int c, result_t *result)
{
	if (a < 3)
	{
		switch (c)
		{
		case 0:
			//best
			_internal_print_results_best_sorted(result, a, c);
			break;
		case 1:
			//worst
			_internal_print_results_worst_sorted(result, a, c);
			break;
		case 2:
			//avarage
			_internal_print_results_avarage_sorted(result, a, c);
			break;

		default:
			printf("valet finns inte\n");
			break;
		}
	}
	else
	{
		switch (c)
		{
		case 0:
			//best
			_internal_print_results_best_search(result, a, c);
			break;
		case 1:
			//worst
			_internal_print_results_worst_search(result, a, c);
			break;
		case 2:
			//avarage
			_internal_print_results_avarage_search(result, a, c);
			break;

		default:
			printf("valet finns inte\n");
			break;
		}
	}
}
/////////////////////////////////////////////////////

//
// Public
//
void ui_run()
{
	bool running, show_menu;
	result_t result[RESULT_ROWS];

	show_menu = true;
	running = true;
	while (running)
	{
		if (show_menu)
		{
			show_menu = false;
			ui_menu();
		}
		switch (ui_get_choice())
		{
		// House keeping
		case 'a':
			show_menu = true;
			break;
		case 'b':
			running = false;
			break;
		// Bubble sort
		case 'c':
			benchmark(bubble_sort_t, best_t, result, RESULT_ROWS);
			_internal_print_results(bubble_sort_t, best_t, result);
			break;
		case 'd':
			benchmark(bubble_sort_t, worst_t, result, RESULT_ROWS);
			_internal_print_results(bubble_sort_t, worst_t, result);
			break;
		case 'e':
			benchmark(bubble_sort_t, average_t, result, RESULT_ROWS);
			_internal_print_results(bubble_sort_t, average_t, result);
			break;
		case 'f':
			benchmark(insertion_sort_t, best_t, result, RESULT_ROWS);
			_internal_print_results(insertion_sort_t, best_t, result);
			break;
		case 'g':
			benchmark(insertion_sort_t, worst_t, result, RESULT_ROWS);
			_internal_print_results(insertion_sort_t, worst_t, result);
			break;
		case 'h':
			benchmark(insertion_sort_t, average_t, result, RESULT_ROWS);
			_internal_print_results(insertion_sort_t, average_t, result);
			break;
		case 'i':
			benchmark(quick_sort_t, best_t, result, RESULT_ROWS);
			_internal_print_results(quick_sort_t, best_t, result);
			break;
		case 'j':
			benchmark(quick_sort_t, worst_t, result, RESULT_ROWS);
			_internal_print_results(quick_sort_t, worst_t, result);
			break;
		case 'k':
			benchmark(quick_sort_t, average_t, result, RESULT_ROWS);
			_internal_print_results(quick_sort_t, average_t, result);
			break;
		case 'l':
			benchmark(linear_search_t, best_t, result, RESULT_ROWS);
			_internal_print_results(linear_search_t, best_t, result);
			break;
		case 'm':
			benchmark(linear_search_t, worst_t, result, RESULT_ROWS);
			_internal_print_results(linear_search_t, worst_t, result);
			break;
		case 'n':
			benchmark(linear_search_t, average_t, result, RESULT_ROWS);
			_internal_print_results(linear_search_t, average_t, result);
			break;
		case 'o':
			benchmark(binary_search_t, best_t, result, RESULT_ROWS);
			_internal_print_results(binary_search_t, best_t, result);
			break;
		case 'p':
			benchmark(binary_search_t, worst_t, result, RESULT_ROWS);
			_internal_print_results(binary_search_t, worst_t, result);
			break;
		case 'q':
			benchmark(binary_search_t, average_t, result, RESULT_ROWS);
			_internal_print_results(binary_search_t, average_t, result);
			break;
		// Invalid input
		default:
			show_menu = false;
			ui_invalid_input();
			break;
		}
	}
	ui_exit();
}
