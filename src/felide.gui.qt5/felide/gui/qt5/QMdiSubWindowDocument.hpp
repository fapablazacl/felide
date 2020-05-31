
#pragma once

#include <QWidget>

#include <felide/gui/document/Document.hpp>

namespace felide {
    class QMdiSubWindowDocument : public QWidget, public Document {
        Q_OBJECT

    public:
        explicit QMdiSubWindowDocument(QWidget *parent);

        virtual ~QMdiSubWindowDocument();

        void setTitle(const std::string &title) override;
        std::string getTitle() const override;

        void setContent(const std::string &content) override;
        std::string getContent() const override;

        void setConfig(const DocumentConfig &config) override;
        DocumentConfig getConfig() const override;

        void clearAll() override;

        void clearUndoBuffer() override;

        void undo() override;
        void redo() override;

        void cut() override;
        void copy() override;
        void paste() override;
        
        void setSelection(const TextSelection &selection) override;

        void selectAll() override;

        void clearSelection() override;

        TextSelection getSelection() const override;
    };
}
