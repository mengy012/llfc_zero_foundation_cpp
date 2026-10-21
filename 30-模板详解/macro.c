#include <stdio.h>

#define CAT_IMPL(a, b) a##b
#define CAT(a, b) CAT_IMPL(a, b)

#define STR_IMPL(s) #s
#define STR(s) STR_IMPL(s)

#define VALUE 5

#define LOG(fmt, ...) printf("[LOG]: " fmt __VA_OPT__(, ) __VA_ARGS__)

#define STATUS_LIST(x) \
    x(IDLE)            \
    x(RUNNING)         \
    x(STOPPED)

#define MAKE_ENUM(name) name,

enum Status
{
    STATUS_LIST(MAKE_ENUM)
};

#define MAKE_CASE(name) case name: return #name;

const char* status_name(enum Status status)
{
    switch (status)
    {
        STATUS_LIST(MAKE_CASE)

    default:
        return "UNKNOWN";
    }
}

int main()
{
    printf("%s\n", STR(CAT(var_, VALUE)));
    printf("%s\n", STR(VALUE));
    printf("%s\n", STR(CAT(a, b)));
    // printf("%s\n", CAT("a", "b"));

    LOG("info\n");
    LOG("a: %d\n", 1);

    enum Status s = IDLE;
    LOG("%s\n", status_name(IDLE));
    LOG("%s\n", status_name(RUNNING));
    LOG("%s\n", status_name(STOPPED));
    LOG("%s\n", status_name(8));
}
