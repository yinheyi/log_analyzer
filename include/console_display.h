#ifndef CONSOLE_DISPLAY_H
#define CONSOLE_DISPLAY_H

#include "comm.h"

enum ConsoleActionEnum {
    ACTION_DISDPLAY_HOME_PAGE,
    ACTION_DISDPLAY_OPTIONS,
    ACTION_OPERATOR_CONTROL,
    ACTION_DISPLAY_FINISH_PAGE,
};

class ConsoleInterface {
public:
    void Run();

private:
    void DisplayHomePage();
    void DisplayAccessOption();
    void DisplayFinishPage();
    void OperatorControl();

    ConsoleActionEnum preAction_ = ACTION_DISDPLAY_HOME_PAGE;
    ConsoleActionEnum nextAction_ = ACTION_DISDPLAY_HOME_PAGE;
    bool isExit_ = false;
};


#endif