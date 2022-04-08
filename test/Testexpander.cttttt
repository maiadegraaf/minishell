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
	test_tools.args = line;
	token_reader(&test_tools);
	parser(&test_tools);
	expander(&test_tools);
}

void	assert_expander(char **expected)
{
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected, test_tools.simple_cmds->str, (ft_strlen(*expected) - 2), "Incorrect variable replacement");
}

void	test_expander_1(void)
{
	init_test("echo $USER");
	assert_expander(ft_split(ft_strjoin("echo ", getenv("USER")), ' '));
	ft_simple_cmdsclear(&test_tools.simple_cmds);
}

void	test_expander_2(void)
{
	init_test("echo \"$HOME\"");
	assert_expander(ft_split(ft_strjoin("echo ", getenv("HOME")), ' '));
	ft_simple_cmdsclear(&test_tools.simple_cmds);
}

void	test_expander_3(void)
{
	init_test("echo \'$HOME\'");
	assert_expander(ft_split("echo \'$HOME\'", ' '));
	ft_simple_cmdsclear(&test_tools.simple_cmds);
}

// void	test_expander_4(void)
// {
// 	init_test(ft_strjoin("cd /Users/", ft_strjoin(getenv("USER"), "/Documents")));
// 	assert_expander(ft_strjoin("/Users/", ft_strjoin(getenv("USER"), "/Documents")), path_to_minishell);
// 	ft_simple_cmdsclear(&test_tools.simple_cmds);
// }

// void	test_expander_5(void)
// {
// 	init_test(ft_strjoin(ft_strjoin("cd ", path_to_minishell), "/src"));
// 	assert_expander(ft_strjoin(path_to_minishell, "/src"), ft_strjoin("/Users/", ft_strjoin(getenv("USER"), "/Documents")));
// 	ft_simple_cmdsclear(&test_tools.simple_cmds);
// }

// void	test_expander_6(void)
// {
// 	init_test("export test=\"a\"");
// 	assert_expander("test", "test=a");
// 	ft_simple_cmdsclear(&test_tools.simple_cmds);
// }

// void	test_expander_7(void)
// {
// 	init_test("export test=\"b\"");
// 	assert_expander("test", "test=b");
// 	ft_simple_cmdsclear(&test_tools.simple_cmds);
// }

// void	test_expander_8(void)
// {
// 	init_test("unset test");
// 	assert_expander("test");
// 	ft_simple_cmdsclear(&test_tools.simple_cmds);
// }

// void	test_expander_9(void)
// {
// 	init_test("export test2=c");
// 	assert_expander("test2", "test2=c");
// 	ft_simple_cmdsclear(&test_tools.simple_cmds);
// }

// void	test_expander_10(void)
// {
// 	init_test("env");
// 	assert_expander(test_envp);
// 	ft_simple_cmdsclear(&test_tools.simple_cmds);
// }

// void	test_expander_11(void)
// {
// 	init_test("pwd");
// 	assert_expander(getcwd(NULL, sizeof(NULL)));
// 	ft_simple_cmdsclear(&test_tools.simple_cmds);
// }

// void	test_expander_12(void)
// {
// 	init_test("unset test2");
// 	assert_expander("test2");
// 	ft_simple_cmdsclear(&test_tools.simple_cmds);
// }

int	main(int argc, char **argv, char **envp)
{
	test_tools.envp = ft_arrdup(envp);
	UNITY_BEGIN();
	RUN_TEST(test_expander_1);
	TEST_MESSAGE("1: {echo $USER}");
	RUN_TEST(test_expander_2);
	TEST_MESSAGE("2: {echo \"$HOME\"}");
	RUN_TEST(test_expander_3);
	TEST_MESSAGE("3: {echo \'$HOME\'}");
	// RUN_TEST(test_expander_4);
	// TEST_MESSAGE("4: {cd {path to} Documents'}");
	// RUN_TEST(test_expander_5);
	// TEST_MESSAGE("5: {cd {path from Documents to} minishell/src}");
	// RUN_TEST(test_expander_6);
	// TEST_MESSAGE("6: {export test=\"a\"}");
	// RUN_TEST(test_expander_7);
	// TEST_MESSAGE("7: {export test=\"b\"}");
	// RUN_TEST(test_expander_8);
	// TEST_MESSAGE("8: {unset test}");
	// RUN_TEST(test_expander_9);
	// TEST_MESSAGE("9: {export test2=c}");
	// // RUN_TEST(test_expander_10);
	// // TEST_MESSAGE("10: {env}");
	// RUN_TEST(test_expander_11);
	// TEST_MESSAGE("11: {pwd}");
	// RUN_TEST(test_expander_12);
	// TEST_MESSAGE("12: {unset test2}");
	return UNITY_END();
}