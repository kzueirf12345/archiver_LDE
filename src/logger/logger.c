#include <stdarg.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#include "logger.h"

#define START_LOGGING_LINE "========START LOGGING======="
#define END_LOGGING_LINE   "=========END LOGGING========"

enum LogCode log_info(const char* const format, const char* const func_name, 
                       const int line_num, va_list* const args);


static struct
{
    unsigned output_flags;
    const char* logout_name;
    FILE* logout;
} LOGGER = {.output_flags = LOG_LEVEL_DETAILS_ZERO, .logout_name = NULL, .logout = NULL};



enum LogCode init_logger()
{
    if (LOGGER.logout_name || LOGGER.logout)
        return LOG_CODE_FAILURE;

    LOGGER.logout_name = "./logout.log";
    if (!(LOGGER.logout = fopen(LOGGER.logout_name, "ab")))
        return LOG_CODE_FAILURE;

    LOGGER.output_flags = LOG_LEVEL_DETAILS_INFO;


    fprintf(LOGGER.logout, "\n" START_LOGGING_LINE "\n\n");

    return LOG_CODE_SUCCES;
}

enum LogCode destroy_logger()
{
    fprintf(LOGGER.logout, "\n" END_LOGGING_LINE "\n");


    LOGGER.output_flags = LOG_LEVEL_DETAILS_ZERO;

    LOGGER.logout_name = NULL;

    if (LOGGER.logout && fclose(LOGGER.logout))
        return LOG_CODE_FAILURE;
    LOGGER.logout = NULL;

    return LOG_CODE_SUCCES;
}


enum LogCode set_level_details(const unsigned level_details)
{
    if (LOG_LEVEL_DETAILS_ALL >= level_details)
        return LOG_CODE_FAILURE;

    LOGGER.output_flags = level_details;

    return LOG_CODE_SUCCES;
}

enum LogCode set_logout_file(const char* const filename)
{
    assert(filename);

    if (LOGGER.logout)
        fprintf(LOGGER.logout, "\n" END_LOGGING_LINE "\n");

    LOGGER.logout_name = filename;

    if (LOGGER.logout && fclose(LOGGER.logout))
        return LOG_CODE_FAILURE;
    
    if (!(LOGGER.logout = fopen(filename, "ab"))) // TODO perror
        return LOG_CODE_FAILURE;
    
    fprintf(LOGGER.logout, "\n" START_LOGGING_LINE "\n\n");
    
    return LOG_CODE_SUCCES;
}



enum LogCode log_not_use(const char* const func_name, const int line_num, // FIXME naming
                         enum LogLevelDetails level_details, const char* const format, ...) {
    assert(func_name);
    assert(format);

    va_list args;
    va_start(args, format);

    if (LOGGER.output_flags & LOG_LEVEL_DETAILS_INFO & level_details)
    {
        if (log_info(format, func_name, line_num, &args) == LOG_CODE_FAILURE)
            return LOG_CODE_FAILURE;
    }
    else if(LOGGER.output_flags & LOG_LEVEL_DETAILS_ERROR & level_details)
    {
        // TODO
    }

    va_end(args);
    return LOG_CODE_SUCCES;
}

enum LogCode log_info(const char* const format, const char* const func_name, 
                       const int line_num, va_list* const args)
{
    assert(format);
    assert(args);
    assert(func_name);

    if (fprintf(LOGGER.logout, "Date: %s, Time: %s. LOGG_INFO about %s. Calles in %d line:\n\t",
                __DATE__, __TIME__, func_name, line_num) <= 0) // FIXME time
        return LOG_CODE_FAILURE;
 
    if (vfprintf(LOGGER.logout, format, *args) < 0)
        return LOG_CODE_FAILURE;
    
    fprintf(LOGGER.logout, "\n");

    return LOG_CODE_SUCCES;
}

void func(int* ptr) {
    assert(ptr);
    MY_ASSERT(ptr);


}

#define MY_ASSERT()