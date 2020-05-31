
#include "QMdiSubWindowDocument.hpp"

namespace felide {
    QMdiSubWindowDocument::QMdiSubWindowDocument(QWidget *parent) : QWidget(parent) {

    }

    QMdiSubWindowDocument::~QMdiSubWindowDocument() {

    }

    void QMdiSubWindowDocument::setTitle(const std::string &title) {

    }

    std::string QMdiSubWindowDocument::getTitle() const {
        return "";
    }

    void QMdiSubWindowDocument::setContent(const std::string &content) {

    }

    std::string QMdiSubWindowDocument::getContent() const {
        return "";
    }

    void QMdiSubWindowDocument::setConfig(const DocumentConfig &config) {

    }

    DocumentConfig QMdiSubWindowDocument::getConfig() const {

    }

    void QMdiSubWindowDocument::clearAll() {

    }

    void QMdiSubWindowDocument::clearUndoBuffer() {

    }

    void QMdiSubWindowDocument::undo() {

    }

    void QMdiSubWindowDocument::redo() {

    }

    void QMdiSubWindowDocument::cut() {

    }

    void QMdiSubWindowDocument::copy() {

    }

    void QMdiSubWindowDocument::paste() {

    }

    void QMdiSubWindowDocument::setSelection(const TextSelection &selection) {

    }

    void QMdiSubWindowDocument::selectAll() {

    }

    void QMdiSubWindowDocument::clearSelection() {

    }

    TextSelection QMdiSubWindowDocument::getSelection() const {
        return TextSelection::all();
    }
}
