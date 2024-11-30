
// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"


// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "GUI/AppFrame.hpp"

#include "cxxopts.hpp"
#include "AudioEngine/AudioEngine.hpp"

#include "wx/log.h"

// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------

// the application icon (under Windows it is in resources and even
// though we could still include the XPM here it would be unused)
#ifndef wxHAS_IMAGES_IN_RESOURCES
    #include "../sample.xpm"
#endif

auto parse_cl(int argc, char**argv) {

    cxxopts::Options options("kbDAW", "fancy stuff!");

    options.add_options()
        ( "c,config", "Configuration file", cxxopts::value<std::string>())
        ( "project", "Project file", cxxopts::value<std::string>()->default_value(""))
        ;

    options.parse_positional({"project"});
    
    return options.parse(argc, argv);
}

class kbDAWApp : public wxApp {
    AudioEngine *audio_engine_ = nullptr;
    std::unique_ptr<std::thread> audio_thread_;

public:
    virtual bool OnInit() override;
    virtual int OnExit() override;
};


wxIMPLEMENT_APP(kbDAWApp);


// 'Main program' equivalent: the program execution "starts" here
bool kbDAWApp::OnInit()
{
    // Don't call - handle the command line ourselves.
    //if ( !wxApp::OnInit() )
    //    return false;

    // parse command line
    auto options = parse_cl(wxApp::argc, wxApp::argv);

    try {

        // Create the AudioEngine
        audio_engine_ = new AudioEngine();
        audio_thread_.reset(audio_engine_->run());
    } catch (std::exception e) {
        wxLogMessage("Caught an exception when creating audio engine - %s", e.what());
        
    }

        // create the main application window
        AppFrame *frame = new AppFrame("kbDAW", options["project"].as<std::string>());

        frame->Show(true);

        wxLogMessage("Finished with kbDAWApp::OnInit");

    return true;
}

int kbDAWApp::OnExit() {


    if (audio_engine_) {
        audio_engine_->stop();
        audio_thread_->join();

        delete audio_engine_;
        audio_engine_ = nullptr;
    }

    return 0;

}