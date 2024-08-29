#ifndef SRC_LOGGER_H
#define SRC_LOGGER_H


enum LogCode
{
    LOG_CODE_SUCCES  = 0,
    LOG_CODE_FAILURE = 1
};

enum LogLevelDetails
{
    LOG_LEVEL_DETAILS_ZERO  = 0b000u,
    LOG_LEVEL_DETAILS_INFO  = 0b001u,
    LOG_LEVEL_DETAILS_ERROR = 0b010u,
    LOG_LEVEL_DETAILS_ALL   = 0b011u,
};


enum LogCode init_logger();
enum LogCode destroy_logger();

enum LogCode set_level_details(const unsigned level_details);
enum LogCode set_logout_file(const char * const filename);


enum LogCode log_not_use(const char* const func_name, const int line_num, 
                 enum LogLevelDetails level_details, const char* const format, ...);
#define logg(level_details, format, ...) log_not_use(__func__, __LINE__, level_details, format, \
                                                     __VA_ARGS__)

#endif /*SRC_LOGGER_H*/