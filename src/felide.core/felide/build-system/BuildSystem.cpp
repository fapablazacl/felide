
#include <string>
#include <map>
#include <memory>

namespace felide::experimental {
    class Value {
    public:
        virtual ~Value() {}
        virtual std::string get() = 0; 
    };

    class Constant : public Value {
    public:
        explicit Constant(const std::string &constant) {
            m_constant = constant;
        }

        virtual std::string get() override {
            return m_constant;
        }

    private:
        std::string m_constant;
    };

    typedef std::map<std::string, std::unique_ptr<Value>> ValueMap;

    class Action {};

    class Compiler {
    public:
        std::string compile(const std::string &file, const ValueMap &valueMap);
    };

    class Linker {
    public:

    };
}
