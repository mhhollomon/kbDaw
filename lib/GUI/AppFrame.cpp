#include "AppFrame.hpp"

#include "TimeLine.hpp"

wxDEFINE_EVENT(EVT_OPEN_MODEL, OpenModelEvent);


// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

// frame constructor
AppFrame::AppFrame(const wxString& title, const std::string& project_file)
       : wxFrame(nullptr, wxID_ANY, title), logWindow(this, "Logging", true, false)
{
    // set the frame icon
    SetIcon(wxICON(sample));

    Bind(EVT_OPEN_MODEL, &AppFrame::OnOpenModel, this, OpenModelDest);
    Bind(wxEVT_MENU, &AppFrame::OnQuit, this, kbDawQuit);
    Bind(wxEVT_MENU, &AppFrame::OnAbout, this, kbDawAbout);


#if wxUSE_MENUBAR
    // create a menu bar
    wxMenu *fileMenu = new wxMenu;

    // the "About" item should be in the help menu
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(kbDawAbout, "&About\tF1", "Show about dialog");

    fileMenu->Append(kbDawQuit, "E&xit\tAlt-X", "Quit this program");

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

timeline_ = new TimeLine(this, model_);
vbox->Add(timeline_, wxSizerFlags().Proportion(1).Expand());

auto * cmd = new wxTextCtrl(this, -1);
vbox->Add(cmd, wxSizerFlags().Proportion(0).Expand());

SetSizer(vbox);

wxLogMessage("Hello, there");

wxLogMessage("project_file = '%s'", project_file);

QueueEvent(new OpenModelEvent(EVT_OPEN_MODEL, project_file));

}


// event handlers

void AppFrame::OnQuit(wxCommandEvent& event)
{
    // true is to force the frame to close
    model_.close_model();
    Close(true);
}

void AppFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxLogMessage("Got About Event");
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

void AppFrame::OnOpenModel(OpenModelEvent &event) {

    wxLogMessage("Got OpenModelEvent in AppFrame");

    model_.open_model(event.get_file_name());

    timeline_->update();

}