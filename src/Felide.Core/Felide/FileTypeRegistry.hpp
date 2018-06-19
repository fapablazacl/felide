
#ifndef __borc_filetyperegistry_hpp__
#define __borc_filetyperegistry_hpp__

#include <string>
#include <vector>
#include <memory>

namespace borc {
    class Source;
    class FileType;

    /**
     * @brief A storage for identification and registration of file types
     *
     * This registry class serves as a local database for known file types, and it's used for 
     * know how to react during certain compilation operations (what command to invoke/execute, etc).
     */
    class FileTypeRegistry {
    public:
        virtual ~FileTypeRegistry() {}

        virtual const FileType* getFileType(const Source *source) const = 0;

        virtual const FileType* addFileType(const std::string &name, const std::vector<std::string> &extensions) = 0;

        virtual void removeFileType(const FileType *type) = 0;

    public:
        static std::unique_ptr<FileTypeRegistry> create();
    };
}

#endif
