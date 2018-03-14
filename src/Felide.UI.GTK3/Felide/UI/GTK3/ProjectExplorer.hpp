
#ifndef __FELIDE_GTK3_PROJECTEXPLORER_HPP__
#define __FELIDE_GTK3_PROJECTEXPLORER_HPP__

#include <string>
#include <gtkmm.h>

namespace Felide::GTK3 {
    /**
     * @brief ProjectExplorer thats open a "vanilla" project style (it just open a folder and shows it contents)
     */ 
    class ProjectExplorer : public Gtk::Bin {
    public:
        static Glib::RefPtr<ProjectExplorer> create();

        virtual ~ProjectExplorer() {}

        virtual void LoadProject(const std::string &projectPath) = 0;

    public:
        typedef sigc::signal<void, std::string> signal_item_activated_t;

        virtual signal_item_activated_t signal_item_activated() = 0;
    };
}

#endif
