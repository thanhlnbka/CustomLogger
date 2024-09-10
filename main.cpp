#include <iostream>
#include <thread>  
#include "process1.h"
#include "process2.h"
#include "Logging.h"

int main() {
    auto logger_main = Logging::get_instance("main");
    std::thread thread1(log_process1);
    std::thread thread2(log_process2);
    thread1.detach();
    thread2.detach();

    while (true) {
        logger_main->log_debug("Main HELLOOOO!!");
        // Sleep for a specified duration
        std::this_thread::sleep_for(std::chrono::seconds(1));  // Sleep for 1 second
    }

    return 0;
}
