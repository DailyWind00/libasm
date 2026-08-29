#include <stdio.h>
#include <string.h>

size_t	ft_strlen(const char *s);
char	*ft_strcpy(char *dest, const char *src);

static void test_strlen(void)
{
	const char *tests[] = {
		"",
		"a",
		"Hello",
		"Hello, World!",
		"42",
		"Assembly is fun!"
	};

	size_t count = sizeof(tests) / sizeof(tests[0]);

	printf("========== ft_strlen ==========\n");

	for (size_t i = 0; i < count; i++)
	{
		size_t expected = strlen(tests[i]);
		size_t result = ft_strlen(tests[i]);

		printf("\"%s\" -> expected: %zu, got: %zu [%s]\n",
			tests[i],
			expected,
			result,
			result == expected ? "OK" : "FAIL");
	}
}

static void test_strcpy(void)
{
	const char *tests[] = {
		"",
		"a",
		"Hello",
		"Hello, World!",
		"42",
		"Assembly is fun!",
		"This is a longer string used to test ft_strcpy."
	};

	size_t count = sizeof(tests) / sizeof(tests[0]);

	printf("\n========== ft_strcpy ==========\n");

	for (size_t i = 0; i < count; i++)
	{
		char expected[256];
		char result[256];

		char *expected_ptr = strcpy(expected, tests[i]);
		char *result_ptr = ft_strcpy(result, tests[i]);

		(void)expected_ptr;

		int content_ok = strcmp(expected, result) == 0;
		int pointer_ok = result_ptr == result;
		int null_terminated = result[strlen(tests[i])] == '\0';

		printf("\"%s\"\n", tests[i]);
		printf("  content:      [%s]\n", content_ok ? "OK" : "FAIL");
		printf("  return ptr:   [%s]\n", pointer_ok ? "OK" : "FAIL");
		printf("  null byte:    [%s]\n", null_terminated ? "OK" : "FAIL");

		if (content_ok && pointer_ok && null_terminated)
			printf("  RESULT:       [OK]\n");
		else
			printf("  RESULT:       [FAIL]\n");
	}
}

int main(void)
{
	test_strlen();
	test_strcpy();

	return 0;
}