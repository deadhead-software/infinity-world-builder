#include "file_io.h"
#include "file_config.h"

#ifdef APPLE
#include "sysdir.h"
#endif
#ifdef WINDOWS
#include <windows.h>
#include <shlobj.h>
#include <iostream>
#endif

namespace FILE_IO
{

    bool file_io_main::initialize()
    {
        bool rc = initialize_module("file_io");
        if (!rc)
        {
            return false;
        }
#ifdef APPLE
        logger->info("FILE I/O using MACOS directories");
        if (!check_for_seed_db())
        {
            return false;
        }
        else
        {
            if (!handle_user_db())
            {
                logger->info("Couldn't create user db nor find it.");
            }
        }
#endif
        logger->info("FILE I/O using WINDOWS directories");
        if (!check_for_seed_db())
        {
            return false;
        }
        else
        {
            if (!handle_user_db())
            {
                logger->info("Couldn't create user db nor find it.");
            }
        }
        return true;
    }

    bool file_io_main::check_for_seed_db()
    {
#ifdef APPLE
        if (std::filesystem::exists(BE_CONSTANTS::APPLE_CONST::seed_db_asset_path))
        {
            logger->info("Seed DB exists!");
            return true;
        }
        else
        {
            logger->error("Seed DB does not exist :(");
            return false;
        }
#endif
#ifdef WINDOWS
        if (std::filesystem::exists(BE_CONSTANTS::WINDOWS_CONST::seed_db_asset_path))
        {
            logger->info("Seed DB exists!");
            return true;
        }
        else
        {
            logger->error("Seed DB does not exist :(");
            return false;
        }
#endif
    }

    bool file_io_main::handle_user_db()
    {
#ifdef APPLE
        if (std::filesystem::exists(BE_CONSTANTS::APPLE_CONST::iwb_appdata_dir))
        {
            logger->info("Deadhead Software/Infinity World Builder directory exists");
            if (std::filesystem::exists(BE_CONSTANTS::APPLE_CONST::iwb_appdata_dir / "app_db.db"))
            {
                logger->info("User Database exists");
            }
            return true;
        }
        else
        {
            logger->info("User IWB app directory doesn't exist.");

            try
            {
                sysdir_search_path_enumeration_state state = sysdir_start_search_path_enumeration(
                    SYSDIR_DIRECTORY_LIBRARY, // Directory type
                    SYSDIR_DOMAIN_MASK_USER   // Domain mask (~/Library)
                );

                char path_buffer[PATH_MAX];
                std::error_code ec;
                if (sysdir_get_next_search_path_enumeration(state, path_buffer))
                {
                    std::filesystem::path preferences_path{path_buffer};
                    std::filesystem::path added_path{"Preferences"};
                    preferences_path = preferences_path / added_path;
                    logger->info("Got preferences path of: {}", preferences_path.c_str());
                    if (std::filesystem::exists(preferences_path / BE_CONSTANTS::dh_app_dir_name, ec))
                    {
                        logger->info("DH/IWB user directory exists");
                    }
                    else
                    {
                        if (std::filesystem::create_directory(preferences_path / BE_CONSTANTS::dh_app_dir_name, ec))
                        {
                            logger->info("Able to create directory");
                        }
                        else
                        {
                            logger->info("failed to create DH/IWB user directory due to {}", ec.message());
                        }
                    }
                }
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
#endif
#ifdef WINDOWS
            PWSTR path = nullptr;
            std::filesystem::path preferences_path;
            // Use FOLDERID_RoamingAppData for Roaming, or FOLDERID_LocalAppData for Local
            HRESULT hr = SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &path);

            if (SUCCEEDED(hr))
            {
                // Convert PWSTR to a standard wide string or print it
                std::wstringstream ss;
                ss << path;
                std::wstring ss_str = ss.str();
                std::string str;
                std::transform(ss_str.begin(), ss_str.end(), std::back_inserter(str), [](wchar_t c)
                               { return (char)c; });
                logger->info("Found user's Local path: {}", str.c_str());
                preferences_path = path;
                // Remember to free the memory allocated by SHGetKnownFolderPath
                CoTaskMemFree(path);
            }
            else
            {
                logger->error("Failed to get user's appdata path");
                return false;
            }

            // find the "Deadhead Software" directory
            //----------------------------------------------------------------------------------------------
            {
                std::filesystem::path app_path = preferences_path / BE_CONSTANTS::WINDOWS_CONST::dh_appdata_dir;
                std::error_code ec;
                std::string app_path_str = app_path.string();
                if (std::filesystem::exists(app_path))
                {
                    logger->info("{} directory exists", app_path_str.c_str());
                }
                else
                {
                    if (std::filesystem::create_directory(app_path, ec))
                    {
                        logger->info("Able to create directory: {}", app_path_str.c_str());
                    }
                    else
                    {
                        logger->info("failed to create {} user directory due to {}", app_path_str.c_str(), ec.message());
                        return false;
                    }
                }
            }
            //----------------------------------------------------------------------------------------------
            // find the "Infinity World Builder" directory
            {
                std::filesystem::path app_path = preferences_path / BE_CONSTANTS::WINDOWS_CONST::iwb_appdata_dir;
                std::error_code ec;
                std::string app_path_str = app_path.string();
                if (std::filesystem::exists(app_path))
                {
                    logger->info("{} directory exists", app_path_str.c_str());
                    // find the database
                    if (std::filesystem::exists(app_path / "app_db.db"))
                    {
                        logger->info("User Database exists");
                        return true;
                    }
                }
                else
                {
                    if (std::filesystem::create_directory(app_path, ec))
                    {
                        logger->info("Able to create directory: {}", app_path_str.c_str());
                    }
                    else
                    {
                        logger->info("failed to create {} user directory due to {}", app_path_str.c_str(), ec.message());
                        return false;
                    }
                }
            }
            return true;
            //----------------------------------------------------------------------------------------------
#endif
        }
    }