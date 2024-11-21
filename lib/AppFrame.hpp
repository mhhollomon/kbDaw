
#include "wx/wx.h"

class AppFrame : public wxFrame {
    public:
        // ctor(s)
        AppFrame(const wxString& title);

        // event handlers (these functions should _not_ be virtual)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);

    private:
        // any class wishing to process wxWidgets events must use this macro
        wxDECLARE_EVENT_TABLE();
};


enum
{
    // menu items
    Minimal_Quit = wxID_EXIT,

    // it is important for the id corresponding to the "About" command to have
    // this standard value as otherwise it won't be handled properly under Mac
    // (where it is special and put into the "Apple" menu)
    Minimal_About = wxID_ABOUT
};
