//
// Created by Mikhail Mustakimov on 06.01.2018.
//

#ifndef KJUDGE_CORE_UTILS_H
#define KJUDGE_CORE_UTILS_H

#include <jni.h>

#include <string>
#include <typeinfo>
#include <cstdio>

using std::string;

jstring jstr_conv(JNIEnv *env, const std::string &s);

/* Converts java-string to c++ string. */
std::string jstr_conv(JNIEnv *env, jstring s);

std::string get_property(
        JNIEnv *env,
        jobject obj,
        const std::string &key,
        const std::string &defvalue);

/* Returns field value. */
template<class FIELD_TYPE>
FIELD_TYPE get_field(JNIEnv *env,
                     jobject obj,
                     const std::string &clsname, //Slashes insteadof dots
                     const std::string &fieldname,
                     const std::string &javatname
);

/* Set field value of object. */
template<class FIELD_TYPE>
void set_field(JNIEnv *env,
               jobject obj,
               FIELD_TYPE value,
               const std::string &clsname, //Slashes insteadof dots
               const std::string &fieldname,
               const std::string &javatname
);


#endif //KJUDGE_CORE_UTILS_H
