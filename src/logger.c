#include <stdio.h>
#include "logger.h"

void log_info(const char *msg)
{
    printf("[INFO] %s\n", msg);
}

void log_warning(const char *msg)
{
    printf("[WARNING] %s\n", msg);
}

void log_fault(const char *msg)
{
    printf("[FAULT] %s\n", msg);
}