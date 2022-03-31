#include "unity.h"
#include "minishell.h"
#include "parser.h"
#include <stdarg.h>

t_tools test_tools;
t_simple_cmds test_simple_cmd;

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
	parse_envp(&test_tools);
	implement_tools(&test_tools);
	test_simple_cmd.str = ft_split(line, ' ');
	test_simple_cmd.builtin = builtin_arr(test_simple_cmd.str[0]);
	test_simple_cmd.num_redirections = 0;
	test_simple_cmd.redirections = NULL;
}

void	assert_mini_echo(void)
{
	TEST_ASSERT_NOT_NULL_MESSAGE(test_simple_cmd.builtin, "Builtin function not connected.");
}

void	assert_mini_cd(char *expected_new_path, char *expected_old_path)
{
	TEST_ASSERT_NOT_NULL_MESSAGE(test_simple_cmd.builtin, "Builtin function not connected.");
	TEST_ASSERT_EQUAL_STRING_MESSAGE(expected_new_path, test_tools.pwd, "New path incorrectly assigned");
	TEST_ASSERT_EQUAL_STRING_MESSAGE(expected_old_path, test_tools.old_pwd, "Old path incorectly assigned");
}

void	assert_mini_env(void)
{
	TEST_ASSERT_NOT_NULL_MESSAGE(test_simple_cmd.builtin, "Builtin function not connected.");
}

void	assert_mini_exit(void)
{
	TEST_ASSERT_NOT_NULL_MESSAGE(test_simple_cmd.builtin, "Builtin function not connected.");
}

void	assert_mini_export(void)
{
	TEST_ASSERT_NOT_NULL_MESSAGE(test_simple_cmd.builtin, "Builtin function not connected.");
}

void	assert_mini_pwd(void)
{
	TEST_ASSERT_NOT_NULL_MESSAGE(test_simple_cmd.builtin, "Builtin function not connected.");
}

void	assert_mini_unset(void)
{
	TEST_ASSERT_NOT_NULL_MESSAGE(test_simple_cmd.builtin, "Builtin function not connected.");
}

void test_builtin_1(void)
{
	init_test("echo hello");
	assert_mini_echo();
}

void test_builtin_2(void)
{
	init_test("echo hello");
	assert_mini_echo();
}

int	main(int argc, char **argv, char **envp)
{
	UNITY_BEGIN();
	test_tools.envp = ft_arrdup(envp);
	RUN_TEST(test_builtin_1);
	TEST_MESSAGE("1: {echo hello}");
	// RUN_TEST(test_builtin_2);
	// TEST_MESSAGE("2: {test test | test}");
	// RUN_TEST(test_builtin_3);
	// TEST_MESSAGE("3: {test test | test      | \'test\'}");
	// RUN_TEST(test_builtin_4);
	// TEST_MESSAGE("4: {< redirection}");
	// RUN_TEST(test_builtin_5);
	// TEST_MESSAGE("5: {test > redirection}");
	// RUN_TEST(test_builtin_6);
	// TEST_MESSAGE("6: {test > redirection < redirection >> redirection}");
	// RUN_TEST(test_builtin_7);
	// TEST_MESSAGE("7: {test > redirection < redirection | heredoc << EOF}");
	// RUN_TEST(test_builtin_8);
	// TEST_MESSAGE("8: {test > redirection < redirection | heredoc < redirection >> redirection << EOF}");
	// RUN_TEST(test_builtin_9);
	// TEST_MESSAGE("9: {cat test | test < redirection | echo test}");
	// RUN_TEST(test_builtin_10);
	// TEST_MESSAGE("10: {cd test | env < redirection | exit test}");
	// RUN_TEST(test_builtin_11);
	// TEST_MESSAGE("11: {export test | pwd < redirection | unset test}");
	return UNITY_END();
}