
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
    cout << "" << endl;
    cout << "按任意键继续..." << endl;
    nextAction_ = ACTION_OPERATOR_CONTROL;
}

void ConsoleInterface::DisplayAccessOption() {
    preAction_ = ACTION_DISDPLAY_OPTIONS;
    cout << endl;
    cout << "**************   读取配置文件，当前程序可以处理以下功能： ****************" << endl;
    cout << "--------------------------------------------------------------------------" << endl;
    cout << "  |" << endl;
    const FeatureManager& mng = FeatureManager::GetInstance();
    const vector<string>& featureList = mng.GetFeatureList();
    for (size_t i = 0; i < featureList.size(); ++i) {
        cout << "  |     [功能" << i + 1 << "]:  " << featureList[i] << " 特性日志分析" << endl;
        cout << "  |" << endl;
    }
        cout << "  |" << endl;
        cout << "  |    < 选择功能序号进行下一步操作:  >" << endl;
        cout << "  |" << endl;
    cout << "--------------------------------------------------------------------------" << endl;
    nextAction_ = ACTION_OPERATOR_CONTROL;
}

void ConsoleInterface::DisplayFinishPage() {
    preAction_ = ACTION_DISPLAY_FINISH_PAGE;
    cout << "****************     程序执行完成，请选择后续操作：   *********************" << endl;
    cout << "--------------------------------------------------------------------------" << endl;
    cout << "  |" << endl;
    cout << "  |" << "< 按 q/Q 键退出程序....>" << endl;
    cout << "  |" << "< 按其它键返回菜单栏...>" << endl;
    cout << "  |" << endl;
    cout << "--------------------------------------------------------------------------" << endl;
    nextAction_ = ACTION_OPERATOR_CONTROL;
}

void ConsoleInterface::OperatorControl() {
    switch(preAction_) {
        case ACTION_DISDPLAY_HOME_PAGE: {
            char temp;
            cin >> temp;
            nextAction_ = ACTION_DISDPLAY_OPTIONS;
        } break;
        case ACTION_DISDPLAY_OPTIONS: {
            uint32_t selectedFeatureId = UINT32_MAX;
            if (cin >> selectedFeatureId) {
                LogAnalyzer logAna;
                logAna.DoAnalysis(selectedFeatureId - 1);  // 内部序号从0开始
            } else {
                cout << "警告: 输入非法, 拒绝分析!!!" << endl;
            }
            nextAction_ = ACTION_DISPLAY_FINISH_PAGE;
        } break;
        case ACTION_DISPLAY_FINISH_PAGE: {
            char temp;
            cin >> temp;
            if (temp == 'q' || temp == 'Q') {
                isExit_ = true;
            }
            nextAction_ = ACTION_DISDPLAY_OPTIONS;
        } break;
    }
    preAction_ = ACTION_OPERATOR_CONTROL;
}