
#include "FolderService.hpp"

namespace felide {
    class FolderServiceImpl : public FolderService {
    public:
    };
}


namespace felide {
    std::unique_ptr<FolderService> FolderService::create() {
        return std::make_unique<FolderServiceImpl>();
    }
}
