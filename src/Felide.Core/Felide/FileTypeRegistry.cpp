
#include "FileTypeRegistry.hpp"

#include <vector>
#include <cassert>
#include <algorithm>
#include <borc/FileType.hpp>
#include <borc/pom/Source.hpp>

namespace borc {
    class FileTypeRegistryImpl : public FileTypeRegistry {
    public:
        FileTypeRegistryImpl() {}

        virtual ~FileTypeRegistryImpl() {}

        virtual const FileType* getFileType(const Source *source) const override {
            assert(source);

            const FileType* resultType = nullptr;

            const std::string ext = source->getExtension();

            for (const auto &fileType : m_fileTypes) {
                if (fileType->check(ext)) {
                    resultType = fileType.get();
                    break;
                }
            }

            return resultType;
        }

        virtual const FileType* addFileType(const std::string &name, const std::vector<std::string> &extensions) override {
            if (extensions.size() == 0) {
                return nullptr;
            } 

            auto fileType = new FileType{name, extensions};

            m_fileTypes.emplace_back(fileType);

            return fileType;
        }

        virtual void removeFileType(const FileType *type) override {
            assert(type);

            auto it = 
                std::find_if( m_fileTypes.begin(), m_fileTypes.end(), [type](auto &fileType) {
                    return fileType.get() == type;
                });

            if (it != m_fileTypes.end()) {
                m_fileTypes.erase(it);
            }
        }

    private:
        std::vector<std::unique_ptr<FileType>> m_fileTypes;
    };

    std::unique_ptr<FileTypeRegistry> FileTypeRegistry::create() {
        return std::make_unique<FileTypeRegistryImpl>();
    }
}
