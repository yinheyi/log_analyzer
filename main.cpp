#include "config_init.h"
#include "output_stream.h"
#include "console_display.h"

int main() {
    // 配置初始化
    ConfigInitializer cfgInit;
    cfgInit.init();

    // 初始化输出流
    OStreamManager::GetInstance().Init(OSTREAM_TYPE_CONSOLE);

    // 启用交互
    ConsoleInterface interface;
    interface.Run();

    return true;
}