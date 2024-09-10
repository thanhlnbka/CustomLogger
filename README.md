# CustomLogger

CustomLogger is a flexible and easy-to-use logging library built on top of Quill. It provides efficient and customizable logging features for C++ applications, supporting logging to both console and file with flexible formatting and configurable log levels.

## Installation

### Requirements

* C++17 or later
* Quill - The logging library that CustomLogger depends on

#### Installing the Library

```sh 
git clone https://github.com/odygrd/quill.git
cd quill
mkdir build && cd build && cmake ..
make
sudo make install
```

#### Build CustomLogger

```sh
cd CustomLogger
mkdir build
cd build
cmake ..
make
```

### Example Usage

1. Initialize Logger

    In a .cpp file, include Logging.h and initialize the global logger:

    ```cpp
    #include "Logging.h"
    
    std::shared_ptr<Logging> logger = Logging::get_instance("main");

    void some_function() {
        logger->log_info("This is a log message from some_function.");
    }

    void another_function() {
        logger->log_debug("This is a log message from another_function.");
    }
    ```

    