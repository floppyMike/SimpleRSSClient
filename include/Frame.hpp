#pragma once

#include <wx/frame.h>

class Frame : public wxFrame
{
public:
    Frame()
        : wxFrame(nullptr, wxID_ANY, "RSS Client")
    {

    }
};