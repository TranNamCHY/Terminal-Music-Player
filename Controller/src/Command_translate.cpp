#include "Command_translate.h"
#include <string>
#include <iostream>
#include "Command.h"

using namespace std;

int isReceiveCommandValid(string cmd) {
    // Check start & stop byte
    if (cmd[START_BYTE] != START_BYTE_VALUE
            || cmd[STOP_BYTE] != STOP_BYTE_VALUE) {
                return MESSAGE_ERROR;
            }

    // Check sum
    uint8_t check_sum = 0;
    for(int i = CHECK_SUM_START; i <= CHECK_SUM_STOP; i++) {
        check_sum += (uint8_t)cmd[i];
    }

    if (check_sum != (uint8_t)cmd[CHECK_SUM_INDEX]) {
        return MESSAGE_ERROR;
    }
    
	return MESSAGE_CORRECT;
}

string translateReceiveCommand(string cmd) {
    std::cout << std::endl << std::flush;
    char command[3];
    command[0] = cmd[MEASSAGE_OPTION_BYTE];

    if(command[0] == OPTION_VOLTAGE) {
        command[1] = cmd[MEASSAGE_VALUE_BYTE];
        command[2] = '\0';
        return string(command);       
    } else if (command[0] == OPTION_UP || command[0] == OPTION_CONFIRM ||
                command[0] == OPTION_GO_BACK || command[0] == OPTION_FORWARD) {
        command[1] = '\0';
        return string(command);
    } else {
        return to_string(-1);
    }
}

string createSendMessage(uint8_t option, uint8_t value) {
    char message[MESSAGE_LENGTH + 1];
    message[0] = START_BYTE_VALUE;
    message[1] = option;
    message[2] = value;
    message[3] = (uint8_t)(option + value);
    message[4] = STOP_BYTE_VALUE;
    message[5] = '\0';
    return string(message);
}
