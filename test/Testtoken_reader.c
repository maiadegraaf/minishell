/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Testtoken_reader.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: fpolycar <fpolycar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/28 11:12:08 by fpolycar      #+#    #+#                 */
/*   Updated: 2022/03/01 17:16:25 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "unity.h"
#include "lexor.h"

t_tools test_tools;
t_lexor *test_lexor;

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void init_test(char *line)
{
    test_tools.args = line;
    test_lexor = token_reader(&test_tools);
}

void assert_token(int token, char *expected)
{
    TEST_ASSERT_EQUAL_STRING(expected, test_lexor->str);
    TEST_ASSERT_EQUAL_INT(token, test_lexor->token);
    test_lexor = test_lexor->next;
}

void test_parser_1(void)
{
    init_test("   test   ");
    assert_token( 0, "test");
}

void test_parser_2(void)
{
    init_test("   test  | test ");
    assert_token(0, "test");
    assert_token(PIPE, NULL);
    assert_token(0, "test");
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_parser_1);
    return UNITY_END();
}
