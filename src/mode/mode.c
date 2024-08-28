#include <string.h>
#include <stdio.h>

#include "mode.h"

#define KWORD_ZIP "ZIP"
#define KWORD_UNZIP "UNZIP"

enum Mode change_mode()
{ 
    enum Mode current_mode = MODE_FAILURE;
    do
    {
        printf("Enter programm mode (ZIP / UNZIP): ");
        char answer[10] = {};
        if (scanf("%s", answer) != 1)
            return MODE_FAILURE;

        if (!strcmp(answer, KWORD_ZIP))
            return MODE_ZIP;
        if (!strcmp(answer, KWORD_UNZIP))
            return MODE_UNZIP;

        printf("Incorrect mode, try again!\n");
        current_mode = MODE_INCORRECT;

    } while (current_mode == MODE_INCORRECT);

    return MODE_FAILURE;
}
