
#include "console_display.h"
#include "log_analyzer.h"
#include "feature_manager.h"

void ConsoleInterface::Run() {
    while (!isExit_) {
        switch(nextAction_) {
            case ACTION_DISDPLAY_HOME_PAGE:
                DisplayHomePage(); break;
            case ACTION_DISDPLAY_OPTIONS:
                DisplayAccessOption(); break;
            case ACTION_OPERATOR_CONTROL:
                OperatorControl(); break;
            case ACTION_DISPLAY_FINISH_PAGE:
                DisplayFinishPage();
            default:
                /* no thing */;
        }
    }
}

void ConsoleInterface::DisplayHomePage() {
    preAction_ = ACTION_DISDPLAY_HOME_PAGE;

cout << endl;
cout << endl;
cout << "####################################################################################" << endl;
cout << "                               #                #" << endl;
cout << "                               #  LOG ANALYZER  #" << endl;
cout << "                               #                #" << endl;
cout << "                               ##################" << endl;
cout << endl;
cout << endl;
cout << endl;
                                                                                       
cout << "   88888888ba,   88        88          88        88 88888888888 88b           d88 " << endl; 
cout << "   88        8b  88        88          88        88 88          888b         d888 " << endl; 
cout << "   88        `8b 88        88          88        88 88          88`8b       d8'88 " << endl; 
cout << "   88         88 88        88          88        88 88aaaaa     88 `8b     d8' 88 " << endl; 
cout << "   88         88 88        88 aaaaaaaa 88        88 88\"\"\"\"\"     88  `8b   d8'  88 " << endl; 
cout << "   88         8P 88        88 \"\"\"\"\"\"\"\" 88        88 88          88   `8b d8'   88 " << endl; 
cout << "   88      .a8P  Y8a.    .a8P          Y8a.    .a8P 88          88    `888'    88 " << endl; 
cout << "   88888888Y\"'    `\"Y8888Y\"'            `\"Y8888Y\"'  88888888888 88     `8'     88 " << endl; 
cout << endl;
cout << endl;
cout << "                             __                  " << endl;
cout << "                            /\\ \\                 " << endl;
cout << "                            \\ \\ \\____  __  __    " << endl;
cout << "                             \\ \\ '__`\\/\\ \\/\\ \\   " << endl;
cout << "                              \\ \\ \\L\\ \\ \\ \\_\\ \\  " << endl;
cout << "                               \\ \\_,__/\\/`____ \\ " << endl;
cout << "                                \\/___/  `/___/> \\" << endl;
cout << "                                           /\\___/" << endl;
cout << "                                           \\/__/ " << endl;
cout << endl;
cout << "                                                                   '  / _   '" << endl; 
cout << "                                                                (///)/)(-(// " << endl; 
cout << "                                                                /        /   " << endl; 
cout << endl;
cout << endl;
cout << endl;
cout << "[Note]: If The Chinese Characters Incorrect Display, Do It: " << endl;
cout << endl;
cout << "            - Close this pragram by press [Ctrl-C]. " << endl;
cout << "            - Execute 'chcp 65001' commond on the terminal." << endl;
cout << "            - Restart the program." << endl;
cout << endl;
cout << endl;
cout << "####################################################################################" << endl;

nextAction_ = ACTION_OPERATOR_CONTROL;
}

void ConsoleInterface::DisplayAccessOption() {
    preAction_ = ACTION_DISDPLAY_OPTIONS;
    cout << endl;
    cout << endl;
    cout << "**************   ???????????????????????????????????????????????????????????? ****************" << endl;
    cout << "--------------------------------------------------------------------------" << endl;
    cout << "  |" << endl;
    const FeatureManager& mng = FeatureManager::GetInstance();
    const vector<string>& featureList = mng.GetFeatureList();
    for (size_t i = 0; i < featureList.size(); ++i) {
        cout << "  |     [??????" << i + 1 << "]:  " << featureList[i] << " ??????????????????" << endl;
        cout << "  |" << endl;
    }
        cout << "  |" << endl;
        cout << "  |  ???????????????????????????????????????:" << endl;
        cout << "  |" << endl;
    cout << "--------------------------------------------------------------------------" << endl;
    nextAction_ = ACTION_OPERATOR_CONTROL;
}

void ConsoleInterface::DisplayFinishPage() {
    preAction_ = ACTION_DISPLAY_FINISH_PAGE;
    cout << endl;
    cout << endl;
    cout << "****************     ?????????????????????????????????????????????   *********************" << endl;
    cout << "--------------------------------------------------------------------------" << endl;
    cout << "  |" << endl;
    cout << "  |" << "< ??? q/Q ???????????????....>" << endl;
    cout << "  |" << "< ???????????????????????????...>" << endl;
    cout << "  |" << endl;
    cout << "--------------------------------------------------------------------------" << endl;
    nextAction_ = ACTION_OPERATOR_CONTROL;
}

void ConsoleInterface::OperatorControl() {
    switch(preAction_) {
        case ACTION_DISDPLAY_HOME_PAGE: {
            cin.sync();
            cin.get();
            cin.sync();
            nextAction_ = ACTION_DISDPLAY_OPTIONS;
        } break;
        case ACTION_DISDPLAY_OPTIONS: {
            cin.sync();
            uint32_t selectedFeatureId = UINT32_MAX;
            if (cin >> selectedFeatureId) {
                LogAnalyzer logAna;
                logAna.DoAnalysis(selectedFeatureId - 1);  // ???????????????0??????
            } else {
                cin.clear();
                cout << "??????: ????????????, ????????????!!!" << endl;
            }
            cin.sync();
            nextAction_ = ACTION_DISPLAY_FINISH_PAGE;
        } break;
        case ACTION_DISPLAY_FINISH_PAGE: {
            cin.sync();
            char temp = cin.get();
            cin.sync();
            if (temp == 'q' || temp == 'Q') {
                isExit_ = true;
            }
            nextAction_ = ACTION_DISDPLAY_OPTIONS;
        } break;
    }
    preAction_ = ACTION_OPERATOR_CONTROL;
}