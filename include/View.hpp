#pragma once

#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/listctrl.h>
#include <wx/frame.h>
#include <wx/statbox.h>

class View
{
public:
	void init(wxPanel *top_panel, wxSizer *top_sizer)
	{
		wxBoxSizer *view_sizer = new wxStaticBoxSizer(new wxStaticBox(top_panel, wxID_ANY, "View"), wxVERTICAL);
		top_sizer->Add(view_sizer, 1, wxEXPAND | wxALL, 10);
	}

private:
};