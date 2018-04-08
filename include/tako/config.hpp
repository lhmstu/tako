#ifndef CONFIG_HPP
#define CONFIG_HPP
#include "tako/common_include.hpp"
namespace tako
{
    // read parameter
    class Config
    {
        private:
            static std::shared_ptr<Config> config_;
            cv::FileStorage file_;

            Config() {} //private constructor makes a singleton

        public:
            ~Config (); // close the file when deconstructing

            //set a new config file
            static void setParameterFile( const std::string& filename );

            //access the parameter values
            template< typename T>
            static T get( const std::string& key )
            {
                // key is string , Filenode is value
                return T(Config::config_->file_[key]);
            }
    };
}
#endif //CONFIG_H