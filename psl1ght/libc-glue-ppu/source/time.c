#include <psl1ght/lv2/timer.h>
#include <psl1ght/lv2/errno.h>

#include <errno.h>
#include <sys/time.h>

int gettimeofday(struct timeval * tv, void * unused)
{
    int ret;
    u64 sec, nsec;

    ret= lv2GetCurrentTime(&sec, &nsec);

    if(ret<0) return lv2Errno(ret);

    tv->tv_sec = sec;
    tv->tv_usec = nsec/1000;
    
    return 0;
}

int settimeofday(const struct timeval * tv, const struct timezone * tz)
{
    int ret;
    u64 sec, nsec;

    sec  = tv->tv_sec;
    nsec = tv->tv_usec * 1000;
 
    ret = lv2SetCurrentTime(sec, nsec);

    if(ret<0) return lv2Errno(ret);

    return 0;
}