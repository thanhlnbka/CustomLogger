// Include the Logging header
#include "Logging.h"
#include <thread>

void log_process1() {
    // auto logger = Logging::get_instance("process1");
    auto logger = Logging::get_instance("main");
    while(true){
        logger->log_info("Logging process {}", 1);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
}
