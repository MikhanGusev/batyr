#ifndef __batyr_configuration_h__
#define __batyr_configuration_h__

#include <string>
#include <memory>
#include <vector>
#include <stdexcept>
#include <unordered_map>


namespace Batyr
{
    
    struct Layer
    {
        std::string name;
        std::string source;
        std::string source_layer;
        std::string description;
        std::string target_table_name;
        std::string target_table_schema;

        typedef std::shared_ptr<Layer> Ptr;
    };


    class ConfigurationError : public std::runtime_error 
    {
        public:
            ConfigurationError(const std::string & message) 
                    : std::runtime_error(message)
            {
            };
    };


    class Configuration
    {
        public:
            Configuration(const std::string & configFile);

            /**
             * get a layer by its name.
             * throws ConfigurationError if it does not exist
             */
            Layer::Ptr getLayer(const std::string &) const;

            unsigned int getHttpPort() const
            {
                return http_port;
            }

            unsigned int getNumWorkerThreads() const
            {
                return num_worker_threads;
            }

            unsigned int getLayerCount() const
            {
                return layers.size();
            }

            unsigned int getMaxAgeDoneJobs() const
            {
                return max_age_done_jobs;
            }


            std::string getDbConnectionString() const
            {
                return db_connection_string;
            }

            /**
             * get a vector with all layers ordered by their names
             */
            std::vector<Layer::Ptr> getOrderedLayers() const;

            typedef std::shared_ptr<Configuration> Ptr;

        private:
            std::unordered_map<std::string, Layer::Ptr> layers;

            /* settings */
            unsigned int http_port;
            unsigned int num_worker_threads;
            unsigned int max_age_done_jobs;
            std::string db_connection_string;

            void parse(const std::string & configFile);
    };

};

#endif // __batyr_configuration_h__
