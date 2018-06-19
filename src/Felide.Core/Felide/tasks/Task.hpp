
#ifndef __borc_task_hpp__
#define __borc_task_hpp__

#include <string>

namespace borc {
    /**
     * @brief A task to be performed an a later time.
     */
    class Task {
    public:
        virtual ~Task();

        /**
         * @brief Perform the task. Throws an exception for reporting to the user
         */
        virtual void perform() = 0;

        /**
         * @brief Get a user-readable description of what will be done by this task
         */
        virtual std::string toString() const = 0;
    };
}

#endif
