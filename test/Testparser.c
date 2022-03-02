#include "unity.h"
#include "lexor.h"

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
    test_lexor = token_reader(&test_tools);
	test_simple_cmds = parser(test_lexor);
}

void assert_parser(int num_direction, char **expected, int (*builtin)(t_tools *))
{
	while (*expected)
	{
    TEST_ASSERT_EQUAL_STRING(*expected++, test_simple_cmds->str++);
	}
    test_simple_cmds = test_simple_cmds->next;
}

void test_parser_1()

int main(void)
{
    UNITY_BEGIN();
	RUN_TEST(test_lexer_1);
    return UNITY_END();
}