#include "module.h"
#include "main.h"
#include "spdlog/async.h"
#include "spdlog/logger.h"
#include <iostream>

    std::shared_ptr<spdlog::logger> module_type::get_logger()
    {
        std::lock_guard<std::mutex> lock(my_mutex);
        return logger;
    }

    bool module_type::initialize_module(std::string name)
    {
        module_name = name;
        try
        {
            if (spdlog::get(module_name) == nullptr)
            {
                std::lock_guard<std::mutex> lock(my_mutex);
                logger = std::make_shared<spdlog::async_logger>(module_name, 
                iwb_main::get_instance().get_logger_sinks().begin(),
                iwb_main::get_instance().get_logger_sinks().end(),
                spdlog::thread_pool(), spdlog::async_overflow_policy::block);
                spdlog::register_logger(logger);
                logger->info("{} module initialized.", module_name);
            }
            else
            {
                logger = spdlog::get(module_name);
                logger->warn("{} logger will share a logger with a module of the same name. This is probably a fail state.", module_name);
            }
            return true;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << "FAILED TO INITIALIZE MODULE " << name.c_str() << '\n';
        }
    }

    std::string module_type::get_name()
    {
        std::lock_guard<std::mutex> lock(my_mutex);
        return module_name;
    }
    void module_type::set_name(std::string new_name)
    {
        std::lock_guard<std::mutex> lock(my_mutex);
        module_name = new_name;
    }