#define _POSIX_C_SOURCE 200809L
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define AC_THREAD_NAME_MAX_SIZE 16
#define AC_TIMESTAMP_MAX_SIZE 30

static int get_timestamp(char *restrict timestamp, const size_t size)
{
    time_t now;
    struct tm timeinfo;
    time(&now);
    localtime_r(&now, &timeinfo);
    size_t len = strftime(timestamp, size, "%Y-%m-%d %H:%M:%S", &timeinfo);
    return (len == 0 ? EMSGSIZE : 0);
}

static const char *policy_string(const int policy)
{
    const char *result = "";
    switch (policy)
    {
        case SCHED_RR:
        {
            result = "SCHED_RR";
            break;
        }
        case SCHED_FIFO:
        {
            result = "SCHED_FIFO";
            break;
        }
        case SCHED_OTHER:
        {
            result = "SCHED_OTHER";
            break;
        }
        default:
        {
            result = "UNKNOWN";
            break;
        }
    }
    return result;
}

int main(void)
{
    const int seconds_to_wait = 30;

    char thread_name[AC_THREAD_NAME_MAX_SIZE] = {'\0'};

    struct sched_param param = {.sched_priority = -1};
    pthread_t thread_id = 0;

    int policy = -1;
    int min_priority = -1;
    int max_priority = -1;

    struct timespec rt_time = {.tv_sec = -1, .tv_nsec = -1};
    struct timespec rt_res = {.tv_sec = -1, .tv_nsec = -1};
    struct timespec mono_time = {.tv_sec = -1, .tv_nsec = -1};
    struct timespec mono_res = {.tv_sec = -1, .tv_nsec = -1};

    /*
     * STUDENT WORK SECTION BEGIN
     * ==========================
     */

    // set the main thread (this thread) policy and priority to inputs:
    // ----------------------------------------------------------------
    // desired_thread_priority
    // desired_policy

    // Get main thread and time information:
    // -------------------------------------
    // thread_name
    // param
    // thread_id
    // policy
    // min_priority
    // max_priority
    // mono_time (CLOCK_MONOTONIC)
    // mono_res (resolution of CLOCK_MONOTONIC)
    // rt_time (CLOCK_REALTIME)
    // rt_time (resolution of CLOCK_REALTIME)

    // Useful functions (check man pages):
    // -----------------------------------
    // pthread_self
    // pthread_getname_np
    // pthread_setschedparam
    // pthread_getschedparam
    // sched_get_priority_min
    // sched_get_priority_max
    // clock_gettime
    // clock_getres

    /*
     * ========================
     * STUDENT WORK SECTION END
     */

    // get timestamp
    char timestamp[AC_TIMESTAMP_MAX_SIZE] = {'\0'};
    const size_t timestamp_max_size = AC_TIMESTAMP_MAX_SIZE;

    int result = get_timestamp(timestamp, timestamp_max_size);
    if (result != 0)
    {
        errno = result;
        perror("Failed to get timestamp string");
        return EXIT_FAILURE;
    }

    printf("Hello World!\n");
    printf("    timestamp: %s\n", timestamp);
    printf("    CLOCK_REALTIME (epoch)\n");
    printf("                  seconds: %ld\n", rt_time.tv_sec);
    printf("              nanoseconds: %ld\n", rt_time.tv_nsec);
    printf("        resolution (nsec): %ld\n", rt_res.tv_nsec);
    printf("    CLOCK_MONOTONIC\n");
    printf("                  seconds: %ld\n", mono_time.tv_sec);
    printf("              nanoseconds: %ld\n", mono_time.tv_nsec);
    printf("        resolution (nsec): %ld\n", mono_res.tv_nsec);
    printf("    process id: %d\n", getpid());
    printf("    user id: %d\n", getuid());
    printf("    main thread info:\n");
    printf("        name: %s\n", thread_name);
    printf("        policy: %s\n", policy_string(policy));
    printf("        min priority: %d\n", min_priority);
    printf("        max priority: %d\n", max_priority);
    printf("        thread priority: %d\n", param.sched_priority);
    printf("        thread id: %lu\n", thread_id);

    printf("\nWaiting for %d seconds...\n", seconds_to_wait);
    fflush(stdout);

    /*
     * STUDENT WORK SECTION BEGIN
     * ==========================
     */

    // Sleep for duration of variable `seconds_to_wait`

    // Useful functions (check man pages):
    // -----------------------------------
    // clock_nanosleep

    /*
     * ========================
     * STUDENT WORK SECTION END
     */

    printf("Done.\n");

    return EXIT_SUCCESS;
}
