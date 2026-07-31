#include <iostream>
#include "main.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h" // support for basic file logging
#include "spdlog/sinks/rotating_file_sink.h" // support for rotating file logging


std::shared_ptr<spdlog::logger> iwb_main::get_logger()
{
    return logger;
}

void iwb_main::initialize()
{
    // create a color multi-threaded logger
    logger = spdlog::stdout_color_mt("main");
}


int main() {
    iwb_main::get_instance().initialize();
    iwb_main::get_instance().get_logger()->info("Logger initialized and IWB ready to go.");
    return 0;
}