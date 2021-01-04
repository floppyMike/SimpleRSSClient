#pragma once

#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/msgdlg.h>

enum
{
    ID_FIND_CONFIG = 1
};

class Frame : public wxFrame
{
public:
    Frame()
        : wxFrame(nullptr, wxID_ANY, "RSS Client")
    {
        wxMenu *find_config = new wxMenu();
        find_config->Append(ID_FIND_CONFIG, "&Open config...\tCtrl-H", "Open a configuration file");

        wxMenuBar *bar = new wxMenuBar();
        bar->Append(find_config, "&Config");

        SetMenuBar(bar);

        CreateStatusBar();
        Bind(wxEVT_MENU, [this](auto &e) { on_config_open(e); }, ID_FIND_CONFIG);
    }

    void on_config_open(wxCommandEvent &e)
    {
        wxMessageBox("Yo", "ASS", wxOK | wxICON_INFORMATION);
    }
};