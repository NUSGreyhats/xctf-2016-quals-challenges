#ifndef DROP_PRIVS
#define DROP_PRIVS

#include <seccomp.h>

void drop_privileges(void) {
    scmp_filter_ctx ctx = seccomp_init(SCMP_ACT_KILL);
    if (ctx == NULL) {
        return;
    }

    int rc = 0;
    rc |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(sigreturn), 0);
    rc |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(epoll_wait), 0);
    rc |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(accept4), 0);
    rc |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(accept), 0);
    rc |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(write), 0);
    rc |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(recv), 0);
    rc |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(fstat), 0);
    rc |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(brk), 0);
    rc |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(fstat64), 0);
    rc |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(mmap2), 0);
    rc |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit_group), 0);
    rc |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(rt_sigaction), 0);
    if (rc != 0) {
        goto fail;
    }

    rc = seccomp_load(ctx);
    if (rc < 0) {
        goto fail;
    }

fail:
    seccomp_release(ctx);
}

#endif
