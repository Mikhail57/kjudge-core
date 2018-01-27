//
// Created by Mikhail Mustakimov on 06.01.2018.
//

#include "ru_kjudge_core_SolutionLauncher.h"
#include "../ktest.h"
#include "utils.h"

#include <sstream>
#include <iostream>
#include <string>

using namespace std;

JNIEXPORT jboolean JNICALL Java_ru_kjudge_core_SolutionLauncher_init
        (JNIEnv *env, jclass thisClass) {
    return ktest_init();
}

JNIEXPORT jobject JNICALL Java_ru_kjudge_core_SolutionLauncher_checkSolution(
        JNIEnv *env,
        jobject thisObject,
        jobject limits,
        jstring command,
        jobject inps,
        jobject outs,
        jobject errorStream
) {
    jclass thisClass = env->FindClass("ru/kjudge/core/SolutionLauncher");

    jclass clsCheckingResult = env->FindClass(
            "ru/kjudge/core/CheckingResult");

    jmethodID ctorCheckingResult = env->GetMethodID(
            clsCheckingResult,
            "<init>",
            "()V");
    jobject result = env->NewObject(
            clsCheckingResult,
            ctorCheckingResult);

    jclass clsInputStream = env->FindClass("java/io/InputStream");

    jmethodID methInpsRead = env->GetMethodID(
            clsInputStream,
            "read",
            "([B)I");

    jclass clsOutputStream = env->FindClass("java/io/OutputStream");

    jmethodID methOutsWrite = env->GetMethodID(
            clsOutputStream,
            "write",
            "([BII)V");

    jclass clsWriter = env->FindClass("java/io/Writer");

    jmethodID methWriterWriteString = env->GetMethodID(
            clsWriter,
            "write",
            "(Ljava/lang/String;)V");


    string exe_command = jstr_conv(env, command);

    string test_dir_path = jstr_conv(
            env,
            (jstring) env->GetObjectField(
                    thisObject,
                    env->GetFieldID(thisClass, "testDir", "Ljava/lang/String;")
            )
    );

    run_limits lims;

    lims.cpu_ms = get_field<jint>(
            env,
            limits,
            "ru/kjudge/core/CheckingLimits",
            "cpuTimeLimit",
            "int");
    lims.timeout_ms = int(lims.cpu_ms * (-0.012 * lims.cpu_ms + 144) / 100);

    lims.mem_bytes = get_field<jint>(
            env,
            limits,
            "ru/kjudge/core/CheckingLimits",
            "memoryLimit",
            "int");
    lims.out_bytes = get_field<jint>(
            env,
            limits,
            "ru/kjudge/core/CheckingLimits",
            "outputLimit",
            "int");
    lims.proc_num = get_field<jint>(
            env,
            limits,
            "ru/kjudge/core/CheckingLimits",
            "processLimit",
            "int");

    stringstream input_test;

    jfieldID bufferField = env->GetFieldID(thisClass, "buffer", "[B");
    jbyteArray bufferJava = (jbyteArray) env->GetObjectField(thisObject, bufferField);
    jbyte buffer[64 * 1024];

    //Записываем содержимое теста в поток.
    jint count;
    while (-1 != (count = env->CallIntMethod(inps, methInpsRead, bufferJava))) {
        env->GetByteArrayRegion(bufferJava, 0, count, buffer);
        input_test.write((const char *) buffer, count);
    }

    stringstream sol_output;

    bool use_privelege_drop = get_property(env, thisObject, "dtest.usePrivelegeDrop", "false") == "true";

    checking_result our_res;

    //Сохраняем старый поток ошибок.
    stringstream my_error_stream;
    //Запускаем проверку решения.
    if (!use_privelege_drop) {
        our_res = check_solution(
                lims,
                exe_command,
                test_dir_path,
                input_test,
                sol_output,
                my_error_stream
        );
    } else {
        our_res = check_solution_as_user(
                lims,
                exe_command,
                test_dir_path,
                input_test,
                sol_output,
                my_error_stream,
                get_property(env, thisObject, "dtest.username", ""),
                get_property(env, thisObject, "dtest.domain", "."),
                get_property(env, thisObject, "dtest.password", "")
        );
    }

    //Возвращаем результаты проверки.
    set_field<jbyte>(env,
                     result,
                     our_res.res_type,
                     "ru/kjudge/core/CheckingResult",
                     "resultType",
                     "byte");

    set_field<jint>(env,
                    result,
                    our_res.ret_value,
                    "ru/kjudge/core/CheckingResult",
                    "returnedValue",
                    "int");

    // Записываем полученный от программы вывод в выходной явовый поток.
    do {
        sol_output.read((char *) buffer, sizeof(buffer));
        count = sol_output.gcount();

        env->SetByteArrayRegion(bufferJava, 0, count, buffer);
        env->CallVoidMethod(outs, methOutsWrite, bufferJava, 0, count);
    } while (!sol_output.fail());

    // Записываем в поток ошибок выведенные системные ошибки.
    env->CallVoidMethod(errorStream, methWriterWriteString, jstr_conv(env, my_error_stream.str()));

    return result;
}

JNIEXPORT jstring JNICALL Java_ru_kjudge_core_SolutionLauncher_createTempDirectory(
        JNIEnv *env,
        jobject thisObject
) {
    return jstr_conv(env, create_test_dir());
}


JNIEXPORT jboolean JNICALL Java_ru_kjudge_core_SolutionLauncher_deleteTemporaryDirectory
        (JNIEnv *env, jobject thisObject, jstring path) {
    return delete_test_dir(jstr_conv(env, path));
}