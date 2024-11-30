#pragma once

#include "Model/FullModel.hpp"
#include "TimeLine.hpp"

#include "wx/wx.h"
#include "wx/log.h"

enum {OpenModelDest = 1 };

class OpenModelEvent : public wxEvent {
    std::string file_name_;

public :
    OpenModelEvent(wxEventType eventType, const std::string & project_file) 
        : wxEvent(OpenModelDest, eventType), file_name_{project_file}
     {}

     OpenModelEvent(OpenModelEvent * const other) 
        : wxEvent(OpenModelDest, other->m_eventType), file_name_{other->file_name_}
        {}

    std::string get_file_name() const { return file_name_; }

    virtual wxEvent *Clone() const { 
        wxLogMessage("Clone called");
        return new OpenModelEvent(*this); 
    }
};

class AppFrame : public wxFrame {
    public:
        // ctor(s)
        AppFrame(const wxString& title, const std::string& project_file);

        // event handlers (these functions should _not_ be virtual)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnOpenModel(OpenModelEvent& event);


    private:
        wxLogWindow logWindow;
        FullModel model_;

        // Note that wxWidgets takes ownership.
        // So we can hold on to this without leaking.
        TimeLine * timeline_;

};


enum
{
    // menu items
    kbDawQuit = wxID_EXIT,

    // it is important for the id corresponding to the "About" command to have
    // this standard value as otherwise it won't be handled properly under Mac
    // (where it is special and put into the "Apple" menu)
    kbDawAbout = wxID_ABOUT
};
