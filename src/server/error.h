#ifndef __batyr_error_h__
#define __batyr_error_h__

#include "rapidjson/document.h"

#include <string>
#include <iostream>
#include <memory>

namespace Batyr
{
    class Error
    {
        public:
            Error(const std::string msg);

            friend std::ostream& operator<< (std::ostream& , const Error&);

            typedef std::shared_ptr<Error> Ptr;

            void setErrorMessage(const std::string & em)
            {
                errorMessage = em;
            }

            /** return the object as a json string */
            std::string toString() const;

            /** push the contents of the object into rapidjson document or value */
            void toJsonValue(rapidjson::Value & targetValue, rapidjson::Document::AllocatorType & allocator) const;

        private:
            std::string errorMessage;
    };

    std::ostream& operator<< (std::ostream& , const Error&);
};

#endif // __batyr_error_h__
