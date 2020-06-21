
#pragma once 

#include <string>

namespace felide {
    class MainFrame {
    public:
        MainFrame() = delete;

        enum Window {
            W_OUTPUT = 0,
            W_FOLDERBROWSER
        };

        enum VisibleState {
            VS_SHOW,
            VS_HIDE
        };

        class View {
        public:
            virtual ~View() = 0;

            virtual void changeTitle(const std::string &value) = 0;

            virtual void changeWindowState(const Window window, const VisibleState state) = 0;

            virtual void show() = 0;

            virtual void close() = 0;

            virtual bool askCloseConfirmation(const std::string &title, const std::string &prompt);
        };

        class Model {
        public:
            virtual ~Model() = 0;

            virtual std::string getTitle() const = 0;

            virtual bool hasModifiedFiles() const = 0;
        };

        class Presenter {
        public:
            explicit Presenter(MainFrame::Model *model);

            void handleInitializedView(MainFrame::View *view);

            void handleCloseRequest();

        private:
            View *view = nullptr;
            Model *model = nullptr;
        };
    };
}
