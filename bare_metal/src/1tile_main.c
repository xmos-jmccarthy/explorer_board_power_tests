// Copyright 2021 XMOS LIMITED.
// This Software is subject to the terms of the XMOS Public Licence: Version 1.

#include <xs1.h>
#include <platform.h>
#include <xcore/parallel.h>

DECLARE_JOB(test, (void));

void test() {
    while(1) { asm volatile(THREAD_OP); }
}

int main(void) {
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
    return 0;
}
