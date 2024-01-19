/*
** EPITECH PROJECT, 2023
** test_error_generating
** File description:
** Tests for mini_printf function
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdio.h>

int main(int ac, char **av);

Test (main, NoProblem)
{
    char **tab = malloc(sizeof(char *) * 3);

    tab[0] = "./setting_up";
    tab[1] = "5";
    tab[2] = "..oo";
    cr_assert_eq(main(3, tab), 0);
    free(tab[2]);
    free(tab[1]);
    free(tab[0]);
    free(tab);
}

// Test (main, String, .init=redirect_all_stdout)
// {
//     main("str");
//     cr_assert_stdout_eq_str("str");
// }

// Test (main, number, .init=redirect_all_stdout)
// {
//     main("0123456789");
//     cr_assert_stdout_eq_str("0123456789");
// }

// Test (main, Unprintable, .init=redirect_all_stdout)
// {
//     main("\n\n\t\n");
//     cr_assert_stdout_eq_str("\n\n\t\n");
// }

// Test (main, Return_Value_Character, .init=redirect_all_stdout)
// {
//     cr_assert_eq(main("c"), 1);
// }

// Test (main, Return_Value_String, .init=redirect_all_stdout)
// {
//     cr_assert_eq(main("str"), 3);
// }

// Test (main, Return_Value_Number, .init=redirect_all_stdout)
// {
//     cr_assert_eq(main("0123456789"), 10);
// }

// Test (main, Return_Value_Unprintable, .init=redirect_all_stdout)
// {
//     cr_assert_eq(main("\n\n\t\n"), 4);
// }