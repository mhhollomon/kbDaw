#include "AppFrame.hpp"

wxBEGIN_EVENT_TABLE(AppFrame, wxFrame)
    EVT_MENU(Minimal_Quit,  AppFrame::OnQuit)
    EVT_MENU(Minimal_About, AppFrame::OnAbout)
wxEND_EVENT_TABLE()


// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

// frame constructor
AppFrame::AppFrame(const wxString& title)
       : wxFrame(nullptr, wxID_ANY, title)
{
    // set the frame icon
    SetIcon(wxICON(sample));

#if wxUSE_MENUBAR
    // create a menu bar
    wxMenu *fileMenu = new wxMenu;

    // the "About" item should be in the help menu
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(Minimal_About, "&About\tF1", "Show about dialog");

    fileMenu->Append(Minimal_Quit, "E&xit\tAlt-X", "Quit this program");

    // now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, "&File");
    menuBar->Append(helpMenu, "&Help");

    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);
#else // !wxUSE_MENUBAR
    // If menus are not available add a button to access the about box
    wxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    wxButton* aboutBtn = new wxButton(this, wxID_ANY, "About...");
    aboutBtn->Bind(wxEVT_BUTTON, &MyFrame::OnAbout, this);
    sizer->Add(aboutBtn, wxSizerFlags().Center());
    SetSizer(sizer);
#endif // wxUSE_MENUBAR/!wxUSE_MENUBAR

#if wxUSE_STATUSBAR
    // create a status bar just for fun (by default with 1 pane only)
    CreateStatusBar(2);
    SetStatusText("kbDAW Startup complete");
#endif // wxUSE_STATUSBAR

wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

auto * timeline = new wxPanel(this, -1);
vbox->Add(timeline, wxSizerFlags().Proportion(1).Expand());

auto * cmd = new wxTextCtrl(this, -1);
vbox->Add(cmd, wxSizerFlags().Proportion(0).Expand());

SetSizer(vbox);

}


// event handlers

void AppFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    // true is to force the frame to close
    Close(true);
}

void AppFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox(wxString::Format
                 (
                    "Welcome to kbDAW!\n"
                    "\n"
                    "This is the start of a silly idea\n"
                    "running under %s (%s).",
                    wxVERSION_STRING,
                    wxGetOsDescription()
                 ),
                 "About kbDAW",
                 wxOK | wxICON_INFORMATION,
                 this);
}