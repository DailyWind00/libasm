#include <stdio.h>
#include <string.h>

size_t ft_strlen(const char *s);

int main(void)
{
	const char *tests[] = {
		"",
		"a",
		"Hello",
		"Hello, World!",
		"42",
		"Assembly is fun! (no)"
	};

	size_t count = sizeof(tests) / sizeof(tests[0]);

	for (size_t i = 0; i < count; i++)
	{
		size_t expected = strlen(tests[i]);
		size_t result = ft_strlen(tests[i]);

		printf("Test %zu: \"%s\"\n", i + 1, tests[i]);
		printf("  strlen    = %zu\n", expected);
		printf("  ft_strlen = %zu\n", result);

		if (result == expected)
			printf("  OK\n\n");
		else
			printf("  FAIL\n\n");
	}

	return 0;
}