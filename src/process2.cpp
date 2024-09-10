// Include the Logging header
#include "Logging.h"
#include <thread>

void log_process2() {
    auto logger = Logging::get_instance("process2"); 
    while(true){
        logger->log_info("Logging process {}", 2);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}