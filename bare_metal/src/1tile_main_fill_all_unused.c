// Copyright 2021 XMOS LIMITED.
// This Software is subject to the terms of the XMOS Public Licence: Version 1.

#include <xs1.h>
#include <platform.h>
#include <xcore/parallel.h>

DECLARE_JOB(test, (void));
DECLARE_JOB(pause, (void));

void test() {
    while(1) { asm volatile("nop"); }
}

void pause() {
    while(1) { asm volatile("waiteu"); }
}

int main(void) {
#if CORES == 1
    PAR_JOBS (
        PJOB(test, ()),
        PJOB(pause, ()),
        PJOB(pause, ()),
        PJOB(pause, ()),
        PJOB(pause, ()),
        PJOB(pause, ()),
        PJOB(pause, ()),
        PJOB(pause, ())
    );
#elif CORES == 5
    PAR_JOBS (
        PJOB(test, ()),
        PJOB(test, ()),
        PJOB(test, ()),
        PJOB(test, ()),
        PJOB(test, ()),
        PJOB(pause, ()),
        PJOB(pause, ()),
        PJOB(pause, ())
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
