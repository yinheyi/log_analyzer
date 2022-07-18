#include "config_init.h"
#include "output_stream.h"
#include "file_system_manager.h"
#include "console_display.h"

int main() {
    try {
        FsManager::GetInstance().Init();    // 文件系统初始化
        ConfigInitializer cfgInit;
        cfgInit.init();
        OStreamManager::GetInstance().Init(OSTREAM_TYPE_CONSOLE);
        ConsoleInterface interface;
        interface.Run();
    } catch(std::exception& e) {
        cerr << "软件运行失败，原因如下： " << endl;
        cerr << e.what() << endl;
    }
    return 0;
}