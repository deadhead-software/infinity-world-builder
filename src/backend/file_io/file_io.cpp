#include "file_io.h"

namespace FILE_IO
{

     bool file_io_main::initialize()
     {
        bool rc = initialize_module("file_io");
#ifdef MACOS
        logger->info("FILE I/O using MACOS directories");
#endif
     }
}