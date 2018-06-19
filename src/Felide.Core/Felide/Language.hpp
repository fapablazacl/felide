
#ifndef __borc_language_hpp__
#define __borc_language_hpp__

#include <vector>
#include <string>

namespace borc {
    class Toolset;
    class FileType;

    /**
     * @brief A language corresponding to a file type
     */
    class Language {
    public:
        virtual ~Language();

        virtual std::string getName() const = 0;

        /**
         * @brief Get a list of the supported toolset
         */
        virtual std::vector<Toolset*> getToolsets() = 0;

        virtual bool test(const std::string &fileName) const = 0;
    };
}

#endif 
