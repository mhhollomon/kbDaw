#pragma once

#include "Model/FullModel.hpp"

#include "wx/panel.h"
#include "wx/event.h"
#include "wx/log.h"


class TimeLine : public wxPanel {

    FullModel &model_;

public:

    TimeLine(wxWindow *parent, FullModel &model);

    void update();

};