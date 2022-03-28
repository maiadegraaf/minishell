#include "unity.h"
#include "lexor.h"
#include <stdarg.h>

t_tools test_tools;

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
	if (expected)
	{
		while (expected[i])
		{
			TEST_ASSERT_EQUAL_STRING_MESSAGE(expected[i], test_tools.simple_cmds->str[i], "Incorrect: STR");
			i++;
		}
	}
	if (builtin)
		TEST_ASSERT_NOT_NULL_MESSAGE(test_tools.simple_cmds->builtin, "Incorrect: BUILTIN");
	else
		TEST_ASSERT_NULL(test_tools.simple_cmds->builtin);
	// printf("num redirections = >%d<\t|\t", num_directions);
	// printf(">%d<\n", test_tools.simple_cmds->num_redirections);
	TEST_ASSERT_EQUAL_INT_MESSAGE(num_directions, test_tools.simple_cmds->num_redirections, "Incorrect: NUM REDIRECTIONS");
	if (expected_redirection)
	{
		t_lexor *start = expected_redirection;
		while (expected_redirection)
		{
			// printf("%s\t", expected_redirection->str);
			// if (expected_redirection->token == GREAT)
			// 	printf("GREAT\n");
			// else if (expected_redirection->token == GREAT_GREAT)
			// 	printf("GREAT_GREAT\n");
			// else if (expected_redirection->token == LESS)
			// 	printf("LESS\n");
			// else if (expected_redirection->token == LESS_LESS)
			// 	printf("LESS_LESS\n");
			TEST_ASSERT_EQUAL_STRING(expected_redirection->str, test_tools.simple_cmds->redirections->str);
			TEST_ASSERT_EQUAL_INT(expected_redirection->token, test_tools.simple_cmds->redirections->token);
			test_tools.simple_cmds->redirections = test_tools.simple_cmds->redirections->next;
			expected_redirection = expected_redirection->next;
		}
		// printf("%s\n", start->str);
		// ft_lexorclear(&start);
	}
	test_tools.simple_cmds = test_tools.simple_cmds->next;
}

void	test_parser_1(void)
{
	TEST_MESSAGE("1: {test test}");
	init_test("test test");
	assert_parser(ft_split("test test", ' '), NULL, 0, NULL);
	ft_simple_cmdsclear(&test_tools.simple_cmds);
}

void	test_parser_2(void)
{
	TEST_MESSAGE("2: {test test | test}");
	init_test("test test | test");
	assert_parser(ft_split("test test", ' '), NULL, 0, NULL);
	assert_parser(ft_split("test", ' '), NULL, 0, NULL);
	ft_simple_cmdsclear(&test_tools.simple_cmds);
}

void	test_parser_3(void)
{
	TEST_MESSAGE("3: {test test | test      | \'test\'}");
	init_test("test test | test      | \'test\'");
	assert_parser(ft_split("test test", ' '), NULL, 0, NULL);
	assert_parser(ft_split("test", ' '), NULL, 0, NULL);
	assert_parser(ft_split("\'test\'", ' '), NULL, 0, NULL);
	ft_simple_cmdsclear(&test_tools.simple_cmds);
}

void	test_parser_4(void)
{
	TEST_MESSAGE("4: {< redirection}");
	init_test("< redirection");
	assert_parser(NULL, NULL, 1, ft_lexornew("redirection", LESS));
	ft_simple_cmdsclear(&test_tools.simple_cmds);
}

void	test_parser_5(void)
{
	TEST_MESSAGE("5: {test > redirection}");
	init_test("test > redirection");
	assert_parser(ft_split("test", ' '), NULL, 1, ft_lexornew("redirection", GREAT));
	ft_simple_cmdsclear(&test_tools.simple_cmds);
}

void	test_parser_6(void)
{
	TEST_MESSAGE("6: {test > redirection < redirection >> redirection}");
	init_test("test > redirection < redirection >> redirection");
	t_lexor *lst= ft_lexornew("redirection", GREAT);
	ft_lexoradd_back(&lst, ft_lexornew("redirection", LESS));
	ft_lexoradd_back(&lst, ft_lexornew("redirection", GREAT_GREAT));
	assert_parser(ft_split("test", ' '), NULL, 3, lst);
	ft_simple_cmdsclear(&test_tools.simple_cmds);
}

void	test_parser_7(void)
{
	TEST_MESSAGE("7: {test > redirection < redirection | heredoc << EOF}");
	init_test("test > redirection < redirection | heredoc << EOF");
	t_lexor *lst = ft_lexornew("redirection", GREAT);
	ft_lexoradd_back(&lst, ft_lexornew("redirection", LESS));
	assert_parser(ft_split("test", ' '), NULL, 2, lst);
	assert_parser(NULL, NULL, 1, ft_lexornew("heredoc|EOF", LESS_LESS));
	ft_simple_cmdsclear(&test_tools.simple_cmds);
}

void	test_parser_8(void)
{
	TEST_MESSAGE("8: {test > redirection < redirection | heredoc < redirection >> redirection << EOF}");
	init_test("test > redirection < redirection | heredoc < redirection >> redirection << EOF");
	t_lexor *lst = ft_lexornew("redirection", GREAT);
	ft_lexoradd_back(&lst, ft_lexornew("redirection", LESS));
	assert_parser(ft_split("test", ' '), NULL, 2, lst);
	t_lexor *lst2 = ft_lexornew("redirection", LESS);
	ft_lexoradd_back(&lst2, ft_lexornew("redirection", GREAT_GREAT));
	ft_lexoradd_back(&lst2, ft_lexornew("heredoc|EOF", LESS_LESS));
	assert_parser(NULL, NULL, 3, lst2);
	ft_simple_cmdsclear(&test_tools.simple_cmds);
}

void	test_parser_9(void)
{
	TEST_MESSAGE("9: {cat test | test < redirection | echo test}");
	init_test("cat test | test < redirection | echo test");
	assert_parser(ft_split("cat test", ' '), NULL, 0, NULL);
	assert_parser(ft_split("test", ' '), NULL, 1, ft_lexornew("redirection", LESS));
	assert_parser(ft_split("echo test", ' '), "YES", 0, NULL);
	ft_simple_cmdsclear(&test_tools.simple_cmds);
}

void	test_parser_10(void)
{
	TEST_MESSAGE("10: {cd test | env < redirection | exit test}");
	init_test("cd test | env < redirection | exit test");
	assert_parser(ft_split("cd test", ' '), "YES", 0, NULL);
	assert_parser(ft_split("env", ' '), "YES", 1, ft_lexornew("redirection", LESS));
	assert_parser(ft_split("exit test", ' '), "YES", 0, NULL);
	ft_simple_cmdsclear(&test_tools.simple_cmds);
}

void	test_parser_11(void)
{
	TEST_MESSAGE("11: {export test | pwd < redirection | unset test}");
	init_test("export test | pwd < redirection | unset test");
	assert_parser(ft_split("export test", ' '), "YES", 0, NULL);
	assert_parser(ft_split("pwd", ' '), "YES", 1, ft_lexornew("redirection", LESS));
	assert_parser(ft_split("unset test", ' '), "YES", 0, NULL);
	ft_simple_cmdsclear(&test_tools.simple_cmds);
}

int	main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_parser_1);
	RUN_TEST(test_parser_2);
	RUN_TEST(test_parser_3);
	RUN_TEST(test_parser_4);
	RUN_TEST(test_parser_5);
	RUN_TEST(test_parser_6);
	RUN_TEST(test_parser_7);
	RUN_TEST(test_parser_8);
	RUN_TEST(test_parser_9);
	RUN_TEST(test_parser_10);
	RUN_TEST(test_parser_11);
	return UNITY_END();
}
