//
// Created by Mikhail Mustakimov on 05.01.2018.
//

#ifndef KJUDGE_CORE_KTEST_H
#define KJUDGE_CORE_KTEST_H

#include <iostream>
#include <string>
#include <list>


#define KTEST_PASSED            0
#define KTEST_TIME_LIMIT        1
#define KTEST_MEMORY_LIMIT      2
#define KTEST_OUTPUT_LIMIT      3
#define KTEST_RUNTIME_ERROR     4
#define KTEST_PROCESS_LIMIT     5
#define KTEST_INTERNAL_ERROR    13


struct run_limits {
    unsigned int timeout_ms;
    unsigned int cpu_ms;
    unsigned int mem_bytes;
    unsigned int out_bytes;
    unsigned int proc_num;
};

struct checking_result {
    unsigned char res_type;
    int ret_value;
};


bool ktest_init();

std::string create_test_dir(const std::string &path);

checking_result check_solution(
        const run_limits &limits,
        const std::string &command,
        const std::string &test_dir_path,
        std::istream input_test,
        std::ostream output
);

checking_result check_solution(
        const run_limits &limits,
        const std::string &command,
        const std::string &test_dir_path,
        std::istream &input_test,
        std::ostream &output,
        std::ostream &error_stream
);

checking_result check_solution_as_user(
        const run_limits &limits,
        const std::string &command,
        const std::string &test_dir_path,
        std::istream &input_test,
        std::ostream &output,
        std::ostream &error_stream,
        const std::string &username,
        const std::string &domain,
        const std::string &password
);

#endif //KJUDGE_CORE_KTEST_H
