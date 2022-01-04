.cc_top vpu_op.func, vpu_op
.globl      vpu_op
.linkset    vpu_op.nstackwords, 0
.globl      vpu_op.nstackwords
.issue_mode dual

.align 4
vpu_op:
    { dualentsp 0    ; nop }
    { vclrdr         ; nop }
    { vldd r0[0]     ; nop }
    { vldc r0[0]     ; nop }
.L_loop_top:
    { vlmaccr r0[0]  ; nop }
    { bu .L_loop_top ; nop }

.cc_bottom vpu_op.func
