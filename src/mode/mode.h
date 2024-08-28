#ifndef SRC_MODE_H
#define SRC_MODE_H

#include <stdbool.h>

enum Mode
{
    MODE_ZIP,
    MODE_UNZIP,
    MODE_INCORRECT,
    MODE_FAILURE
};  

enum Mode change_mode();


#endif /* SRC_MODE_H */