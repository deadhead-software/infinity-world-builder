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
    const std::filesystem::path dh_app_dir_name {"/Deadhead Software/"};
    const std::filesystem::path iwb_app_dir_name{"/Infinity World Builder"};

    namespace APPLE_CONST
    {
        /// @brief Horrible way to do this but I'm just trying to test things, I'll change how we do this later
        const std::filesystem::path seed_db_asset_path {"/Users/root1/_SRC/infinity-world-builder/assets/db/seed/seed_db.db"};
        const std::filesystem::path appdata_dir {"~/Library/Application Support"};
        const std::filesystem::path iwb_appdata_dir = appdata_dir / dh_app_dir_name / iwb_app_dir_name; // concat operator
        const std::filesystem::path userdata_dir { "~/Library/Preferences"};
        const std::filesystem::path preferences { "/Preferences"};
    }
}