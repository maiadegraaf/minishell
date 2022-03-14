/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Testtoken_reader.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: fpolycar <fpolycar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/28 11:12:08 by fpolycar      #+#    #+#                 */
/*   Updated: 2022/03/14 18:43:14 by fpolycar      ########   odam.nl         */
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

void test_lexer_1(void)
{
    init_test("   test   ");
    assert_token( 0, "test");
}

void test_lexer_2(void)
{
    init_test("   test  | test ");
    assert_token(0, "test");
    assert_token(PIPE, NULL);
    assert_token(0, "test");
}

void test_lexer_3(void)
{
    init_test("   test test test          test || test       test");
    assert_token(0, "test");
    assert_token(0, "test");
    assert_token(0, "test");
    assert_token(0, "test");
    assert_token(PIPE, NULL);
    assert_token(PIPE, NULL);
    assert_token(0, "test");
    assert_token(0, "test");
}

void test_lexer_4(void)
{
    init_test("   test   \n\n  test\n \ntest");
    assert_token(0, "test");
    assert_token(NEW_LINE, NULL);
    assert_token(NEW_LINE, NULL);
    assert_token(0, "test");
    assert_token(NEW_LINE, NULL);
    assert_token(NEW_LINE, NULL);
    assert_token(0, "test");
}

void test_lexer_5(void)
{
    init_test("test '  test | test' '  ");
    assert_token(0, "test");
    assert_token(0, "'  test | test'");
}

void test_lexer_6(void)
{
    init_test("test    \" |  test\"");
    assert_token(0, "test");
    assert_token(0, "\" |  test\"");
}

void test_lexer_7(void)
{
    init_test("test < | test > | test << | test >> |");
    assert_token(0, "test");
    assert_token(LESS, NULL);
    assert_token(PIPE, NULL);
    assert_token(0, "test");
    assert_token(GREAT, NULL);
    assert_token(PIPE, NULL);
    assert_token(0, "test");
    assert_token(LESS_LESS, NULL);
    assert_token(PIPE, NULL);
    assert_token(0, "test");
    assert_token(GREAT_GREAT, NULL);
    assert_token(PIPE, NULL);
}

void test_lexer_8(void)
{
    init_test("test -nBa -n");
    assert_token(0, "test");
    assert_token(0, "-nBa");
    assert_token(0, "-n");
}

void test_lexer_9(void)
{
    init_test("test $BLA$BLA=10$BLA");
    assert_token(0, "test");
    assert_token(0, "$BLA$BLA=10$BLA");
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_lexer_1);
    RUN_TEST(test_lexer_2);
    RUN_TEST(test_lexer_3);
    RUN_TEST(test_lexer_4);
    RUN_TEST(test_lexer_5);
    RUN_TEST(test_lexer_6);
    RUN_TEST(test_lexer_7);
    RUN_TEST(test_lexer_8);
    RUN_TEST(test_lexer_9);
    return UNITY_END();
}
