/*******************************************************************
* Copyright         : 2026 Jason C McQueen, Deadhead Software
* File Name         : file_config.h
* Description       : currently a constants file, will be replaced later
*                     with XML or TOML parsing, something like that
*                    
* Revision History  :
* Date		        Author 			Comments
* ------------------------------------------------------------------
* 08/1/2026     	Jason C McQueen	        initial file creation
*
/******************************************************************/
#pragma once

#include <iostream>
#include <filesystem>

namespace BE_CONSTANTS
{
    const std::string dh_iwb_fp = "/Deadhead Software/Infinity World Builder";
    const std::filesystem::path iwb_user_folder{"/Deadhead Software/Infinity World Builder"};

    namespace APPLE_CONST
    {
        const std::string appdata_dir = "~/Library/Application Support";
        const std::string userdata_dir = "~/Library/Preferences";
    }
}