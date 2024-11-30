#include "TimeLine.hpp"

#include "wx/wx.h"
#include "wx/log.h"
#include <format>



TimeLine::TimeLine(wxWindow *parent, FullModel &model) :  wxPanel(parent), model_{model} {

}


void TimeLine::update() {
    DestroyChildren();
    SetSizer(nullptr);

     wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

    int index = 0;
    for(auto const &track : model_.get_track_list()) {
        auto ti = model_.get_track_info(track.uuid_);

        auto label = std::format("{} id = {} '{}'", index, track.uuid_, ti.name_ );

        auto *track_panel = new wxStaticText(this, -1, label);

        vbox->Add(track_panel, wxSizerFlags().Proportion(0).Expand());

    }

    SetSizer(vbox);


}
