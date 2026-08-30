#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define OK "\033[1;32m[OK]\033[0m"
#define FAIL "\033[1;31m[FAIL]\033[0m"

size_t	ft_strlen(const char *s);
char	*ft_strcpy(char *dest, const char *src);
int		ft_strcmp(const char *s1, const char *s2);
ssize_t ft_write(int fd, const void *buf, size_t count);
ssize_t ft_read(int fd, void *buf, size_t count);

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

		printf("\"%s\" -> expected: %zu, got: %zu %s\n",
			tests[i],
			expected,
			result,
			result == expected ? OK : FAIL);
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
		printf("  content:      %s\n", content_ok ? OK : FAIL);
		printf("  return ptr:   %s\n", pointer_ok ? OK : FAIL);
		printf("  null byte:    %s\n", null_terminated ? OK : FAIL);

		if (content_ok && pointer_ok && null_terminated)
			printf("  RESULT:       " OK "\n");
		else
			printf("  RESULT:       " FAIL "\n");
	}
}

static void test_strcmp(void)
{
	const char *tests[][2] = {
		{"", ""},
		{"", "a"},
		{"a", ""},
		{"a", "a"},
		{"a", "b"},
		{"b", "a"},
		{"abc", "abc"},
		{"abc", "abd"},
		{"abd", "abc"},
		{"abc", "abcd"},
		{"abcd", "abc"},
		{"Hello", "Hello"},
		{"Hello", "hello"},
		{"hello", "Hello"},
		{"42", "43"},
		{"Assembly", "Assembly is fun!"}
	};

	size_t count = sizeof(tests) / sizeof(tests[0]);

	printf("\n========== ft_strcmp ==========\n");

	for (size_t i = 0; i < count; i++)
	{
		int expected = strcmp(tests[i][0], tests[i][1]);
		int result = ft_strcmp(tests[i][0], tests[i][1]);

		int expected_sign = (expected > 0) - (expected < 0);
		int result_sign = (result > 0) - (result < 0);

		printf("\"%s\" vs \"%s\"\n",
			tests[i][0],
			tests[i][1]);

		printf("  libc strcmp: %d\n", expected);
		printf("  ft_strcmp:   %d\n", result);

		if (expected_sign == result_sign)
			printf("  RESULT:      " OK "\n");
		else
			printf("  RESULT:      " FAIL "\n");
	}
}

static void test_strcmp_unsigned(void)
{
	const char s1[] = { (char)0xFF, '\0' };
	const char s2[] = { (char)0x01, '\0' };

	int expected = strcmp(s1, s2);
	int result = ft_strcmp(s1, s2);

	printf("\n========== unsigned char test ==========\n");
	printf("libc strcmp: %d\n", expected);
	printf("ft_strcmp:   %d\n", result);
	printf("RESULT:      %s\n",
		((expected > 0) == (result > 0)) ? OK : FAIL);
}

static void test_write(void)
{
	const char *str = "Hello from ft_write!\n";
	size_t len = strlen(str);

	printf("\n========== ft_write ==========\n");

	printf("libc write:\n");
	errno = 0;
	ssize_t expected = write(STDOUT_FILENO, str, len);
	int expected_errno = errno;

	printf("ft_write:\n");
	errno = 0;
	ssize_t result = ft_write(STDOUT_FILENO, str, len);
	int result_errno = errno;

	printf("\nExpected return: %zd\n", expected);
	printf("ft_write return: %zd\n", result);

	printf("Expected errno: %d\n", expected_errno);
	printf("ft_write errno: %d\n", result_errno);

	if (result == expected)
		printf("Return value: " OK "\n");
	else
		printf("Return value: " FAIL "\n");

	if (result >= 0)
		printf("SUCCESS TEST: %s\n",
			result == (ssize_t)len ? OK : FAIL);
	else
		printf("SUCCESS TEST: " FAIL "\n");
}

static void test_write_error(void)
{
	const char *str = "This should fail\n";

	printf("\n========== ft_write error ==========\n");

	errno = 0;
	ssize_t expected = write(-1, str, strlen(str));
	int expected_errno = errno;

	errno = 0;
	ssize_t result = ft_write(-1, str, strlen(str));
	int result_errno = errno;

	printf("libc:      return = %zd, errno = %d (%s)\n",
		expected, expected_errno, strerror(expected_errno));

	printf("ft_write:  return = %zd, errno = %d (%s)\n",
		result, result_errno, strerror(result_errno));

	if (result == expected && result_errno == expected_errno)
		printf("ERROR TEST: " OK "\n");
	else
		printf("ERROR TEST: " FAIL "\n");
}


static void test_read(void)
{
	int pipefd[2];
	char expected[64];
	char result[64];
	const char *message = "Hello from ft_read!";

	printf("\n========== ft_read ==========\n");

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return;
	}

	/* Write data into the pipe */
	write(pipefd[1], message, strlen(message));
	close(pipefd[1]);

	/* Test ft_read */
	errno = 0;
	ssize_t result_size = ft_read(pipefd[0], result, sizeof(result) - 1);

	/* Test libc read with the same data */
	int pipefd2[2];
	if (pipe(pipefd2) == -1)
	{
		perror("pipe");
		close(pipefd[0]);
		return;
	}

	write(pipefd2[1], message, strlen(message));
	close(pipefd2[1]);

	errno = 0;
	ssize_t expected_size = read(pipefd2[0], expected, sizeof(expected) - 1);

	close(pipefd[0]);
	close(pipefd2[0]);

	if (result_size >= 0)
		result[result_size] = '\0';
	else
		result[0] = '\0';

	if (expected_size >= 0)
		expected[expected_size] = '\0';
	else
		expected[0] = '\0';

	printf("Expected: \"%s\" (%zd bytes)\n", expected, expected_size);
	printf("Got:      \"%s\" (%zd bytes)\n", result, result_size);

	if (result_size == expected_size &&
		strcmp(result, expected) == 0)
		printf("SUCCESS TEST: " OK "\n");
	else
		printf("SUCCESS TEST: " FAIL "\n");
}

static void test_read_error(void)
{
	char buffer[16];

	printf("\n========== ft_read error ==========\n");

	errno = 0;
	ssize_t expected = read(-1, buffer, sizeof(buffer));
	int expected_errno = errno;

	errno = 0;
	ssize_t result = ft_read(-1, buffer, sizeof(buffer));
	int result_errno = errno;

	printf("libc:     return = %zd, errno = %d (%s)\n",
		expected, expected_errno, strerror(expected_errno));

	printf("ft_read:  return = %zd, errno = %d (%s)\n",
		result, result_errno, strerror(result_errno));

	if (result == expected && result_errno == expected_errno)
		printf("ERROR TEST: " OK "\n");
	else
		printf("ERROR TEST: " FAIL" \n");
}

int main(void)
{
	test_strlen();

	test_strcpy();

	test_strcmp();
	test_strcmp_unsigned();

	test_write();
	test_write_error();

	test_read();
	test_read_error();

	return 0;
}