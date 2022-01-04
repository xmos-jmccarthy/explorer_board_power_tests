// Copyright 2021 XMOS LIMITED.
// This Software is subject to the terms of the XMOS Public Licence: Version 1.

#include <xs1.h>
#include <platform.h>
#include <xcore/parallel.h>
#include <xcore/triggerable.h>

#define SETSR(c) asm volatile("setsr %0" : : "n"(c));

DECLARE_JOB(test, (void));

void test() {
    int a, b;
    int arr[2] = {0,0};
    // int arr[2] = {0xFFFFFFFF,0xFFFFFFFF};
    triggerable_disable_all();
#if HP_FAST_MODE == 1
    SETSR(XS1_SR_QUEUE_MASK | XS1_SR_FAST_MASK);
#endif
    while(1) {
        asm volatile("ldd %0,%1,%2[0]":"=r"(a),"=r"(b):"r"(arr));
    }
}

void main_tile0(void) {
#if CORES == 1
    test();
#elif CORES == 5
    PAR_JOBS (
        PJOB(test, ()),
        PJOB(test, ()),
        PJOB(test, ()),
        PJOB(test, ()),
        PJOB(test, ())
    );
#elif CORES == 8
    PAR_JOBS (
        PJOB(test, ()),
        PJOB(test, ()),
        PJOB(test, ()),
        PJOB(test, ()),
        PJOB(test, ()),
        PJOB(test, ()),
        PJOB(test, ()),
        PJOB(test, ())
    );
#endif
}

void main_tile1(void) {
#if CORES == 1
    test();
#elif CORES == 5
    PAR_JOBS (
        PJOB(test, ()),
        PJOB(test, ()),
        PJOB(test, ()),
        PJOB(test, ()),
        PJOB(test, ())
    );
#elif CORES == 8
    PAR_JOBS (
        PJOB(test, ()),
        PJOB(test, ()),
        PJOB(test, ()),
        PJOB(test, ()),
        PJOB(test, ()),
        PJOB(test, ()),
        PJOB(test, ()),
        PJOB(test, ())
    );
#endif
}
