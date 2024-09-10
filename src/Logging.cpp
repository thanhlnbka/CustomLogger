#include "Logging.h"

std::mutex Logging::instance_mutex_;
std::unordered_map<std::string, std::shared_ptr<Logging>> Logging::instances_;

std::shared_ptr<Logging> Logging::get_instance(const std::string &instance_name) {
    std::lock_guard<std::mutex> lock(instance_mutex_);

    auto it = instances_.find(instance_name);
    if (it != instances_.end()) {
        return it->second;
    }

    // Create a new instance if not found
    auto new_instance = std::shared_ptr<Logging>(new Logging(instance_name));
    instances_[instance_name] = new_instance;
    return new_instance;
}



Logging::Logging(const std::string& instance_name) {
    // Start the Quill backend
    quill::BackendOptions backend_options;
    quill::Backend::start(backend_options);

     // Frontend
    auto rotating_file_sink = quill::Frontend::create_or_get_sink<quill::RotatingFileSink>(
        instance_name + ".log",
        []()
        {
        // See RotatingFileSinkConfig for more options
        quill::RotatingFileSinkConfig cfg;
        cfg.set_open_mode('w');
        cfg.set_filename_append_option(quill::FilenameAppendOption::StartDateTime);
        cfg.set_rotation_time_daily("00:00");
        cfg.set_rotation_max_file_size(10*1024*1024); // 10MB
        return cfg;
        }());   

    auto console_sink = quill::Frontend::create_or_get_sink<quill::ConsoleSink>("console_sink");


    // Create or get the logger
    // Assuming quill::Frontend::create_or_get_logger returns a raw pointer
    logger_ = std::shared_ptr<quill::Logger>(quill::Frontend::create_or_get_logger(
        instance_name,
        {
        std::move(rotating_file_sink),
        std::move(console_sink)
        },
        quill::PatternFormatterOptions{
            "%(time) [%(thread_id)] "
            "LOG_%(log_level:<9) %(message)",
            "%H:%M:%S.%Qns",
            quill::Timezone::GmtTime
        }
    ), [](quill::Logger* ptr) { 
        delete ptr; // Custom deleter if needed
    });


    // Set the log level (can be changed dynamically if needed)
    logger_->set_log_level(quill::LogLevel::Debug);
}
