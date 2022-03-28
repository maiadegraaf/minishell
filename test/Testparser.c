#include "unity.h"
#include "lexor.h"
#include <stdarg.h>

t_tools test_tools;
t_lexor *test_lexor;
t_simple_cmds *test_simple_cmds;

void	setUp(void)
{
	// set stuff up here
}

void	tearDown(void)
{
	// clean stuff up here
}

void	init_test(char *line)
{
	test_tools.args = line;
	token_reader(&test_tools);
	parser(&test_tools);
}

void	assert_parser(char **expected, char *builtin, int num_directions, t_lexor *expected_redirection)
{
	int	i;

	i = 0;
	while (expected[i])
	{
		TEST_ASSERT_EQUAL_STRING_MESSAGE(expected[i], test_tools.simple_cmds->str[i], "STR CHECK\t");
		i++;
	}
	if (builtin)
		TEST_ASSERT_NOT_NULL_MESSAGE(test_tools.simple_cmds->builtin, "BUILTIN CHECK\t");
	else
		TEST_ASSERT_NULL(test_tools.simple_cmds->builtin);
	TEST_ASSERT_EQUAL_INT_MESSAGE(num_directions, test_tools.simple_cmds->num_redirections, "NUM REDIRECTIONS CHECK\t");
	// if (expected_redirection)
	// {
	// 	printf("%s\n", test_tools.simple_cmds->redirections->str);
	// 	// TEST_ASSERT_EQUAL_STRING(expected_redirection->str, test_tools.simple_cmds->redirections->str);
	// 	// TEST_ASSERT_EQUAL_INT(expected_redirection->token, test_tools.simple_cmds->redirections->token);
	// }	
	test_tools.simple_cmds = test_tools.simple_cmds->next;
}

void	test_parser_1(void)
{
	init_test("test test");
	assert_parser(ft_split("test test", ' '), NULL, 0, NULL);
	ft_simple_cmdsclear(&test_tools.simple_cmds);
}

void	test_parser_2(void)
{
	init_test("test test | test");
	assert_parser(ft_split("test test", ' '), NULL, 0, NULL);
	assert_parser(ft_split("test", ' '), NULL, 0, NULL);
	ft_simple_cmdsclear(&test_tools.simple_cmds);
}

void	test_parser_3(void)
{
	init_test("test test | test      | 'test'");
	assert_parser(ft_split("test test", ' '), NULL, 0, NULL);
	assert_parser(ft_split("test", ' '), NULL, 0, NULL);
	assert_parser(ft_split("'test'", ' '), NULL, 0, NULL);
	ft_simple_cmdsclear(&test_tools.simple_cmds);
}

void	test_parser_4(void)
{
	init_test("< redirection");
	assert_parser(NULL, NULL, 1, ft_lexornew("redirection", LESS));
	ft_simple_cmdsclear(&test_tools.simple_cmds);
}

void	test_parser_5(void)
{
	init_test("test > redirection");
	assert_parser(ft_split("test", ' '), NULL, 1, ft_lexornew("redirection", GREAT));
	ft_simple_cmdsclear(&test_tools.simple_cmds);
}

int	main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_parser_1);
	RUN_TEST(test_parser_2);
	RUN_TEST(test_parser_3);
	// RUN_TEST(test_parser_4);
	// RUN_TEST(test_parser_5);
	return UNITY_END();
}
