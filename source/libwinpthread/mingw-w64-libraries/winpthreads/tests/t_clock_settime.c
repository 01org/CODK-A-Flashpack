#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define assert(_Expression) (void)( (!!(_Expression)) || (_my_assert(#_Expression, __FILE__, __LINE__), 0) )

static __inline void _my_assert(char *message, char *file, unsigned int line)
{
    fprintf(stderr, "Assertion failed: %s , file %s, line %u\n", message, file, line);
    exit(1);
}

void test_clock_settime()
{
    int rc;
    struct timespec tp, request = { 1, 0 }, remain;

    rc = clock_gettime(CLOCK_REALTIME, &tp);
    assert(rc == 0);
    printf("[%10"PRId64".%09d] clock_gettime (CLOCK_REALTIME)\n", (__int64) tp.tv_sec, (int) tp.tv_nsec);
    
    rc = clock_settime(CLOCK_MONOTONIC, &tp);
    assert(rc == -1 && (errno == EINVAL));
    
    rc = clock_settime(CLOCK_PROCESS_CPUTIME_ID, &tp);
    assert(rc == -1 && (errno == EINVAL));
    
    rc = clock_settime(CLOCK_THREAD_CPUTIME_ID, &tp);
    assert(rc == -1 && (errno == EINVAL));
    
    rc = clock_settime(CLOCK_REALTIME, &tp);
    assert(rc == 0 || (errno == EPERM));

    rc = clock_gettime(CLOCK_REALTIME, &tp);
    assert(rc == 0);
    printf("[%10"PRId64".%09d] clock_gettime (CLOCK_REALTIME)\n", (__int64) tp.tv_sec, (int) tp.tv_nsec);
}

int main(int argc, char *argv[])
{
    test_clock_settime();

    return 0;
}
