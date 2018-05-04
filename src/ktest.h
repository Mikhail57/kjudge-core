//
// Created by Mikhail Mustakimov on 05.01.2018.
//

#ifndef KJUDGE_CORE_KTEST_H
#define KJUDGE_CORE_KTEST_H

#include <iostream>
#include <string>
#include <list>
#include "common.h"


bool ktest_init();

char *create_test_dir(char *path);

char *create_test_dir();


bool delete_test_dir(char *path);;

checking_result check_solution(
        const run_limits &limits,
        const char *command,
        const char *test_dir_path,
        const char *input_test,
        char *output
);

checking_result check_solution(
        const run_limits &limits,
        const char *command,
        const char *test_dir_path,
        const char *input,
        char *output,
        char *error
);

checking_result check_solution_as_user(
        const run_limits &limits,
        const char *command,
        const char *test_dir_path,
        const char *input,
        char *output,
        char *error,
        const char *username,
        const char *domain,
        const char *password
);

#endif //KJUDGE_CORE_KTEST_H
