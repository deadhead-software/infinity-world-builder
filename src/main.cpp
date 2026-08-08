#include <iostream>
#include "main.h"
#include "spdlog/async.h"
#include "spdlog/logger.h"
#include "spdlog/sinks/stdout_color_sinks.h"


std::shared_ptr<spdlog::logger> iwb_main::get_logger()
{
    std::lock_guard<std::mutex> lock(main_mutex);
    return logger;
}


std::vector<spdlog::sink_ptr>& iwb_main::get_logger_sinks()
{
    std::lock_guard<std::mutex> lock(main_mutex);
    return sinks;
}

bool iwb_main::initialize_modules()
{
     try
     {
         dbio.initialize();
         file_io.initialize();
     }
     catch(const std::exception& e)
     {
         if (logger != nullptr)
         {
             logger->critical("Modules failed to initialize, failing.");
             return false;
         }
    }
    // if we got through everything without returning false, we successfully initialized all modules.
    return true;
    
}

bool iwb_main::initialize()
{
    // create a color multi-threaded logger
    try
    {
        spdlog::init_thread_pool(8192, 1);
        auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt >();
        sinks.push_back(stdout_sink);
        logger = std::make_shared<spdlog::async_logger>("iwb_main", sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
        spdlog::register_logger(logger);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << "FAILED TO INITIALIZE SPDLOG LOGGER, FAILING" << '\n';
        return false;
    }
    if (!initialize_modules())
    {
        std::cerr << "FAILED TO INITIALIZE MODULES, FAILING" << '\n';
        return false;
    }

    // if everything succeeded and we got here, return true
    return true;

}


int main() {
    if (!iwb_main::get_instance().initialize())
    {
        return 1; // return fail condition.
    }
    iwb_main::get_instance().get_logger()->info("Logger initialized and IWB ready to go.");
    while (1) {}; // wait so all logs get there
}