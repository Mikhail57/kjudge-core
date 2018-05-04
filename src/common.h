//
// Created by Mikhail Mustakimov on 03.05.2018.
//

#ifndef KJUDGE_CORE_STRUCTS_H
#define KJUDGE_CORE_STRUCTS_H

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

#endif //KJUDGE_CORE_STRUCTS_H
