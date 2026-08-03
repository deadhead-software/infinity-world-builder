/*******************************************************************
* Copyright         : 2026 Jason C McQueen, Deadhead Software
* File Name         : file_io.h
* Description       : main class for reading and writing to files
*                     - mainly a wrapper for FileSystem (mostly, again, 
*                       for logging)
*                    
* Revision History  :
* Date		        Author 			Comments
* ------------------------------------------------------------------
* 08/2/2026	       Jason C McQueen	        initial file creation
*
/******************************************************************/
#pragma once

#include <iostream>
#include "module/module.h"

namespace FILE_IO
{
    class file_io_main : public module_type
    {
        public:
            bool initialize();
    };
}