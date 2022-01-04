// Copyright 2021 XMOS LIMITED.
// This Software is subject to the terms of the XMOS Public Licence: Version 1.

#include <xs1.h>
#include <platform.h>
#include <xcore/parallel.h>
#include <xcore/triggerable.h>

extern void vpu_op(int* ptr);

#define SETSR(c) asm volatile("setsr %0" : : "n"(c));

DECLARE_JOB(test, (void));

__attribute__((aligned(4)))
static int arr[256] = {0xFF};

void test() {
    int a = 0xFFFFFFFF;
    triggerable_disable_all();
#if HP_FAST_MODE == 1
    SETSR(XS1_SR_QUEUE_MASK | XS1_SR_FAST_MASK);
#endif
    vpu_op(arr); // never returns
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
