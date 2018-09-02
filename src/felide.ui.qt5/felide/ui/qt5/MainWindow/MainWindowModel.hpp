
#ifndef __FELIDE_UI_MAINWINDOWMODEL_HPP__
#define __FELIDE_UI_MAINWINDOWMODEL_HPP__

namespace felide {
    class MainWindowModel {
    public:
        int getCreatedDocumentCount() const;

        int increaseDocumentCount();

    private:
        int createdDocumentCount = 0;
    };
} 

#endif
