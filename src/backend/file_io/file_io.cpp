#include "file_io.h"
#include "file_config.h"

#ifdef MACOS
#include "sysdir.h"
#endif

namespace FILE_IO
{

    bool file_io_main::initialize()
    {
        bool rc = initialize_module("file_io");
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
#endif
        }
    }