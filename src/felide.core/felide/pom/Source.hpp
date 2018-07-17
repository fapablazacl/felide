
#ifndef __borc_source_hpp__
#define __borc_source_hpp__

#include <string>

namespace felide {
    class Target;
    /**
     * @brief Source file abstraction.
     */
    class Source {
    public:
        explicit Source(const std::string &filePath, const Target *target);

        virtual ~Source();

        /**
         * @brief Get the file name extension, neccesary in order to identify the file type.
         */
        std::string getExtension() const;

        /**
         * @brief Get the file title, without the path and the extension.
         */
        std::string getFileTitle() const;

        /**
         * @brief Get the file name, in the form filename.extesion (without the relative path)
         */
        std::string getFileName() const;

        /**
         * @brief Get the relative path to the target, to identify the physical file.
         */
        std::string getFilePath() const;

        /**
         * @brief Get the parent target
         */
        const Target* getTarget() const;

        // TODO: Generalize to a extension - changing method
        std::string computeOutputFileName(const std::string &extension) const;

        std::string computeOutputDirectory(const std::string &relativePrefix) const;

    private:
        //! The parent target.
        const Target *m_target = nullptr;
        
        //! Relative fullname path to the parent target
        std::string m_filePath;
    };
}

#endif
