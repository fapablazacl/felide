
#ifndef __BORC_DIRECTORYTASK_HPP__
#define __BORC_DIRECTORYTASK_HPP__

#include "Task.hpp"

namespace borc {
    /**
     * @brief Creates a directory hierarchy if doesn't exists, and false in another case
     */
    class DirectoryTask : public Task {
    public:
        explicit DirectoryTask(const std::string &directory);
        
        virtual ~DirectoryTask() {}
        
        virtual void perform() override;

        virtual std::string toString() const override;

    private:
        std::string m_directory;
    };
}

#endif
