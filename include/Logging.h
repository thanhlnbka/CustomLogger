#ifndef LOGGING_H
#define LOGGING_H

#include "quill/Backend.h"
#include "quill/Frontend.h"
#include "quill/LogMacros.h"
#include "quill/Logger.h"
#include "quill/sinks/RotatingFileSink.h"
#include "quill/sinks/ConsoleSink.h"
#include "quill/TriviallyCopyableCodec.h"
#include "quill/bundled/fmt/ostream.h"
#include "quill/std/Array.h"
#include "quill/std/Chrono.h"
#include <iostream>
#include <utility>
#include <mutex>
#include <string>
#include <unordered_map>
#include <memory>

class Logging {
public:
    // Singleton pattern: Get the single instance of Logging with a specific name
    static std::shared_ptr<Logging> get_instance(const std::string &instance_name);

    // Method to log info using the existing logger
    template <typename... Args>
    void log_info(const std::string& message, Args&&... args) {
        std::lock_guard<std::mutex> lock(mutex_); // Thread safety
        auto formatted_message = fmtquill::v11::format(message, std::forward<Args>(args)...);
        LOG_INFO(logger_, "{}", formatted_message);
    }

    // Method to log debug messages
    template <typename... Args>
    void log_debug(const std::string& message, Args&&... args) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto formatted_message = fmtquill::v11::format(message, std::forward<Args>(args)...);
        LOG_DEBUG(logger_, "{}", formatted_message);
    }

    // Method to log errors
    template <typename... Args>
    void log_error(const std::string& message, Args&&... args) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto formatted_message = fmtquill::v11::format(message, std::forward<Args>(args)...);
        LOG_ERROR(logger_, "{}", formatted_message);
    }

private:
    std::shared_ptr<quill::Logger> logger_; // The main logger
    std::mutex mutex_;                     // Mutex for thread-safe logging

    static std::mutex instance_mutex_;    // Mutex for managing instances
    static std::unordered_map<std::string, std::shared_ptr<Logging>> instances_; // Map of instances

    // Private constructor for singleton
    Logging(const std::string& instance_name);

    // Delete copy constructor and assignment operator to ensure singleton pattern
    Logging(const Logging&) = delete;
    Logging& operator=(const Logging&) = delete;
};

#endif // LOGGING_H
