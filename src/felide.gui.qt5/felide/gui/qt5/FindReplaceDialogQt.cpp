
#include "FindReplaceDialogQt.hpp"

namespace felide {
    template<typename TWidget>
    void addChildToParent(QWidget *parent, TWidget **widget, const QRect &geometry, const QString &title) {
        *widget = new TWidget(title, parent);
        (*widget)->setGeometry(geometry);
    }


    FindReplaceDialogQt::FindReplaceDialogQt(QWidget *parent, FindReplaceDialogPresenter *presenter, DocumentQt *document) : QWidget(parent) {
        addChildToParent(parent, &findReplaceGroupBox,  {10, 10, 270, 80}, "Find/Replace parameters");
        addChildToParent(parent, &findWhatLabel,        {30, 30, 100, 20}, "Find what");
        addChildToParent(parent, &findWhatEdit,         {150, 30, 100, 20}, "");
        addChildToParent(parent, &replaceWithCheckBox,  {30, 55, 100, 20}, "Replace with");
        addChildToParent(parent, &replaceWithEdit,      {150, 55, 100, 20}, "");

        addChildToParent(parent, &matchGroupBox,        {10, 100, 270, 80}, "Match options");
        addChildToParent(parent, &matchCaseCheckBox,       {30, 125, 125, 20}, "Match case");
        addChildToParent(parent, &matchWholeWordCheckBox,  {30, 145, 125, 20}, "Match whole word");

        addChildToParent(parent, &scopeGroupBox,                {10, 190, 270, 80}, "Scope");
        addChildToParent(parent, &scopeSelectionRadio,          {30, 210, 125, 20}, "Selection");
        addChildToParent(parent, &scopeCurrentDocumentRadio,    {30, 230, 125, 20}, "Current Document");

        addChildToParent(parent, &findNextButton,       {10, 280, 120, 30}, "Find Next");
        addChildToParent(parent, &closeButton,          {140, 280, 120, 30}, "Close");
        addChildToParent(parent, &replaceNextButton,    {10, 320, 120, 30}, "Replace Next");
        addChildToParent(parent, &replaceAllButton,     {140, 320, 120, 30}, "Replace All");

        this->setupLayout();
        this->setupSignals();
    }

    FindReplaceDialogQt::~FindReplaceDialogQt() {}


    void FindReplaceDialogQt::setupSignals() {
        // TODO: Add implementation
    }

    void FindReplaceDialogQt::setupLayout() {

    }

    void FindReplaceDialogQt::attachPresenter(FindReplaceDialogPresenter *presenter) {

    }

    void FindReplaceDialogQt::show(const ViewData &viewData) {

    }

    void FindReplaceDialogQt::hide() {

    }

    void FindReplaceDialogQt::toggleReplaceControls(const bool status) {

    }
}
