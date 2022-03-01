/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Testmain.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fpolycar <fpolycar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/28 11:12:08 by fpolycar      #+#    #+#                 */
/*   Updated: 2022/03/01 13:38:49 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "unity.h"
#include "minishell.h"

t_tools tools;
t_lexor *lexor;

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void init_test(char *line)
{
    tools.args = line;
    
}

void test_parser_1(void)
{
    init_test("   test   ");
    TEST_ASSERT_EQUAL_STRING("echo", token_reader(&tools)->str);
}


// TEST_ASSERT_EQUAL_STRING("echo", token_reader(&tools)->str);
// TEST_ASSERT_EQUAL_HEX8(33, AverageThreeBytes(33, 33, 33));
// }


int main(void)
{
UNITY_BEGIN();
RUN_TEST(test_parser_1);
return UNITY_END();
}
