
#ifndef __FELIDE_UI_SEARCHREPLACEDIALOG_PRESENTER_HPP__
#define __FELIDE_UI_SEARCHREPLACEDIALOG_PRESENTER_HPP__

#include <string>

namespace felide {
    class Document;
    class FindReplaceDialog;
    class FindReplaceDialogPresenter {
    public:
        void attachView(FindReplaceDialog *view, Document *documentView);

        void handleEditFindReplace();

        void handleFindWhatTextBox_Change(const std::string &value);

        void handleReplaceWithCheckBox_Click(const bool checked);

        void handleReplaceWithTextBox_Change(const std::string &value);

        void handleMatchCaseCheckBox_Click(const bool checked);

        void handleMatchWholeWordCheckBox_Click(const bool checked);

        void handleSelectionScopeOptionBox_Click();

        void handleCurrentDocumentScopeOptionBox_Click();

        void handleFindNextButton_Click();

        void handleReplaceNextButton_Click();

        void handleReplaceAllButton_Click();

        void handleCloseButton_Click();

    private:
        bool findNext(const size_t offset);

    private:
        FindReplaceDialog *view = nullptr;
        Document *documentView = nullptr;

        std::string findWhat;
        std::string replaceWith;
        bool replaceInsteadOfFind = false;
        bool matchCase = false;
        bool matchWholeWord = false;

        enum Scope {
            Selection, CurrentDocument
        } scope = CurrentDocument;
    };
}

#endif
