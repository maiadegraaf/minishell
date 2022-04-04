/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Testtoken_reader.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: fpolycar <fpolycar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/28 11:12:08 by fpolycar      #+#    #+#                 */
/*   Updated: 2022/03/31 12:22:21 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "unity.h"
#include "lexor.h"

t_tools test_tools;

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void init_test(char *line)
{
    test_tools.args = line;
    token_reader(&test_tools);
}

void assert_token(int token, char *expected)
{
    TEST_ASSERT_EQUAL_STRING(expected, test_tools.lexor_list->str);
    TEST_ASSERT_EQUAL_INT(token, test_tools.lexor_list->token);
    test_tools.lexor_list = test_tools.lexor_list->next;
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
    init_test("   test     test test");
    assert_token(0, "test");
    assert_token(0, "test");
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

void test_lexer_10(void)
{
    init_test("test bla=\"test\" bla=\"t est\"");
    assert_token(0, "test");
    assert_token(0, "bla=\"test\"");
    assert_token(0, "bla=\"t est\"");
}

void test_lexer_11(void)
{
    init_test("test\n\ntest\ftest\rtest\ttest");
    assert_token(0, "test");
    assert_token(0, "test");
    assert_token(0, "test");
    assert_token(0, "test");
    assert_token(0, "test");
}

void test_lexer_12(void)
{
    init_test("test|test|test>test<test");
    assert_token(0, "test");
    assert_token(PIPE, NULL);
    assert_token(0, "test");
    assert_token(PIPE, NULL);
    assert_token(0, "test");
    assert_token(GREAT, NULL);
    assert_token(0, "test");
    assert_token(LESS, NULL);
    assert_token(0, "test");
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_lexer_1);
    ft_lexorclear(&test_tools.lexor_list);
    RUN_TEST(test_lexer_2);
    ft_lexorclear(&test_tools.lexor_list);
    RUN_TEST(test_lexer_3);
    ft_lexorclear(&test_tools.lexor_list);
    RUN_TEST(test_lexer_4);
    ft_lexorclear(&test_tools.lexor_list);
    RUN_TEST(test_lexer_5);
    ft_lexorclear(&test_tools.lexor_list);
    RUN_TEST(test_lexer_6);
    ft_lexorclear(&test_tools.lexor_list);
    RUN_TEST(test_lexer_7);
    ft_lexorclear(&test_tools.lexor_list);
    RUN_TEST(test_lexer_8);
    ft_lexorclear(&test_tools.lexor_list);
    RUN_TEST(test_lexer_9);
    ft_lexorclear(&test_tools.lexor_list);
    RUN_TEST(test_lexer_10);
    ft_lexorclear(&test_tools.lexor_list);
    RUN_TEST(test_lexer_11);
    ft_lexorclear(&test_tools.lexor_list);
     RUN_TEST(test_lexer_12);
    ft_lexorclear(&test_tools.lexor_list);
    return UNITY_END();
}
