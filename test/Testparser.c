#include "unity.h"
#include "lexor.h"
#include <stdarg.h>

t_tools test_tools;
t_lexor *test_lexor;
t_simple_cmds *test_simple_cmds;

void setUp(void)
{
    // set stuff up here
}

void tearDown(void)
{
    // clean stuff up here
}

void init_test(char *line)
{
    test_tools.args = line;
    token_reader(&test_tools);
	// test_simple_cmds = parser(test_lexor, &test_tools);
}

void assert_parser(char **expected, char *builtin, int num_directions, t_lexor *expected_redirection)
{
	int i;

	i = 0;
	while (expected[i])
	{
   		TEST_ASSERT_EQUAL_STRING(expected[i], test_simple_cmds->str[i]);
		i++;
	}
	if (builtin)
		TEST_ASSERT_NOT_NULL(test_simple_cmds->builtin);
	else
		TEST_ASSERT_NULL(test_simple_cmds->builtin);
	TEST_ASSERT_EQUAL_INT(num_directions, test_simple_cmds->num_redirections);
	TEST_ASSERT_EQUAL_STRING(expected_redirection->str, test_simple_cmds->redirections->str);
	TEST_ASSERT_EQUAL_INT(expected_redirection->token, test_simple_cmds->redirections->token);
	TEST_ASSERT_EQUAL_INT(expected_redirection->i, test_simple_cmds->redirections->i);
    test_simple_cmds = test_simple_cmds->next;
}

t_lexor *make_expected_redirection(char *str, int token, int i)
{
	t_lexor *redirection;

	redirection = malloc(sizeof(t_lexor));
	redirection->str = str;
	redirection->token = token;
	redirection->i = i;
	return (redirection);
}

char **make_array(char *str, ...)
{
	va_list arg;
	char **arr = NULL;
	char *test = "test";
	int i;

	i = 0;
	va_start(arg, str);
	while (test)
	{
		test = va_arg(arg, char*);
		arr[i] = test;
		i++;
	}
	va_end(arg);
	return (arr);
}

void test_lexer_1(void)
{
	init_test("test test");
	assert_parser(make_array("test", "test"), NULL, 0, make_expected_redirection(NULL, 0, 0));
}

void test_lexer_2(void)
{
	init_test("test test | test");

	assert_parser(make_array("test", "test"), NULL, 0, make_expected_redirection(NULL, 0, 0));
	assert_parser(NULL, NULL, 0, make_expected_redirection(NULL, 0, 0));
	assert_parser(make_array("test"), NULL, 0, make_expected_redirection(NULL, 0, 0));
}

int main(void)
{
    UNITY_BEGIN();
	RUN_TEST(test_lexer_1);
    return UNITY_END();
}