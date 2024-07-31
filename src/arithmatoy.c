#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

int VERBOSE = 0;

const char *get_all_digits() { return "0123456789abcdefghijklmnopqrstuvwxyz"; }
const size_t ALL_DIGIT_COUNT = 36;

void arithmatoy_free(char *number) { free(number); }

char *arithmatoy_add(unsigned int base, const char *lhs, const char *rhs)
{
	if (VERBOSE)
		fprintf(stderr, "add: entering function\n");
	size_t max_len = strlen(rhs);

	if (strlen(lhs) > strlen(rhs))
		max_len = strlen(lhs);

	char *result = (char *)malloc(max_len + 2);
	size_t nb = 0;

	for (size_t index = 0; index < max_len; index++)
	{
		size_t lhs_nb = 0, rhs_nb = 0;
		if (strlen(lhs) > index)
			lhs_nb = get_digit_value(lhs[strlen(lhs) - index - 1]);
		if (strlen(rhs) > index)
			rhs_nb = get_digit_value(rhs[strlen(rhs) - index - 1]);
		size_t sum = lhs_nb + rhs_nb + nb;
		nb = sum / base;
		result[max_len - index] = to_digit(sum % base);
	}
	if (nb > 0)
		result[0] = to_digit(nb);
	else
		result = result + 1;
	return drop_leading_zeros(result);
}

// Fonction utilitaire pour sub et mul
char *init_result(size_t len)
{
	char *result = (char *)malloc((len + 1) * sizeof(char));
	for (size_t index = 0; index < len; index++)
		result[index] = '0';
	result[len] = '\0';
	return result;
}

char *arithmatoy_sub(unsigned int base, const char *lhs, const char *rhs)
{
	if (VERBOSE)
		fprintf(stderr, "sub: entering function\n");

	lhs = drop_leading_zeros(lhs);
	rhs = drop_leading_zeros(rhs);
	if(strlen(lhs) < strlen(rhs))
		return NULL;
	char *result = init_result(strlen(lhs));
	size_t nb = 0;

	for (size_t i = 0; i < strlen(lhs); i++)
	{
		size_t lhs_nb = get_digit_value(lhs[strlen(lhs) - i - 1]);
		size_t rhs_nb = 0;
		if (i < strlen(rhs))
			rhs_nb = get_digit_value(rhs[strlen(rhs) - i - 1]);
		int sub = lhs_nb - rhs_nb - nb;
		if(sub < 0)
		{
			nb = 1;
			sub += base;
		}
		else
			nb = 0;
		result[strlen(lhs) - i -1] = to_digit(sub);
	}
	if (nb != 0)
	{
		free(result);
		return NULL;
	}
	char *final_result = init_result(strlen(result));
	strcpy(final_result, (char *) drop_leading_zeros(result));
	return final_result;
}

char *arithmatoy_mul(unsigned int base, const char *lhs, const char *rhs)
{
	if (VERBOSE)
		fprintf(stderr, "mul: entering function\n");

	size_t total_len = strlen(lhs) + strlen(rhs);
	char *result = init_result(total_len);

	for (size_t index = 0; index < strlen(lhs); ++index)
	{
		size_t lhs_nb = get_digit_value(lhs[strlen(lhs) - index - 1]);
		size_t nb = 0;
		for (size_t index_2 = 0; index_2 < strlen(rhs); ++index_2)
		{
			size_t rhs_nb = get_digit_value(rhs[strlen(rhs) - index_2 - 1]);
			size_t mul = lhs_nb * rhs_nb + nb + get_digit_value(result[total_len - index - index_2 - 1]);
			nb = mul / base;
			size_t digit = mul % base;
			result[total_len - index - index_2 - 1] = to_digit(digit);
		}
		if (nb > 0)
			result[total_len - index - strlen(rhs) - 1] = to_digit(nb);
	}

	char *final_result = init_result(strlen(drop_leading_zeros(result)));
	strcpy(final_result, drop_leading_zeros(result));
	return final_result;
}



// Here are some utility functions that might be helpful to implement add, sub
// and mul:

unsigned int get_digit_value(char digit) {
  // Convert a digit from get_all_digits() to its integer value
	if (digit >= '0' && digit <= '9') {
		return digit - '0';
	}
	if (digit >= 'a' && digit <= 'z') {
		return 10 + (digit - 'a');
	}
	return -1;
}

char to_digit(unsigned int value) {
	// Convert an integer value to a digit from get_all_digits()
	if (value >= ALL_DIGIT_COUNT) {
		debug_abort("Invalid value for to_digit()");
		return 0;
	}
	return get_all_digits()[value];
}

char *reverse(char *str) {
	// Reverse a string in place, return the pointer for convenience
	// Might be helpful if you fill your char* buffer from left to right
	const size_t length = strlen(str);
	const size_t bound = length / 2;
	for (size_t i = 0; i < bound; ++i) {
		char tmp = str[i];
		const size_t mirror = length - i - 1;
		str[i] = str[mirror];
		str[mirror] = tmp;
	}
	return str;
}

const char *drop_leading_zeros(const char *number) {
	// If the number has leading zeros, return a pointer past these zeros
	// Might be helpful to avoid computing a result with leading zeros
	if (*number == '\0') {
		return number;
	}
	while (*number == '0') {
		++number;
	}
	if (*number == '\0') {
		--number;
	}
	return number;
}

void debug_abort(const char *debug_msg) {
	// Print a message and exit
	fprintf(stderr, debug_msg);
	exit(EXIT_FAILURE);
}
