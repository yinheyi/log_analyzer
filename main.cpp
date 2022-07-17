#include "config_init.h"
#include "output_stream.h"
#include "console_display.h"

int main() {
    try {
        ConfigInitializer cfgInit;
        cfgInit.init();
        OStreamManager::GetInstance().Init(OSTREAM_TYPE_CONSOLE);
        ConsoleInterface interface;
        interface.Run();
    } catch(std::exception& e) {
        cerr << e.what() << endl;
    }

    return 0;
}