/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Testmain.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fpolycar <fpolycar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/28 11:12:08 by fpolycar      #+#    #+#                 */
/*   Updated: 2022/02/28 16:02:46 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "unity.h"
#include "minishell.h"



void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_parser_should_word(void)
{
// t_lexor *lexor_list;
// char *str = "echo test | cd nice";


TEST_ASSERT_EQUAL_HEX8(0, main());
// TEST_ASSERT_EQUAL_HEX8(40, AverageThreeBytes(10, 70, 40));
// TEST_ASSERT_EQUAL_HEX8(33, AverageThreeBytes(33, 33, 33));
}


int main(void)
{
UNITY_BEGIN();
RUN_TEST(test_parser_should_word);
return UNITY_END();
}
