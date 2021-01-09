#pragma once

#include <wx/log.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/listctrl.h>
#include <wx/frame.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/hyperlink.h>

#include "Data.hpp"

class View
{
public:
	void init(wxPanel *top_panel, wxSizer *top_sizer)
	{
		m_top_sizer = top_sizer;
		auto *sizer = new wxStaticBoxSizer(wxVERTICAL, top_panel, "View");

		m_header = new wxStaticText(top_panel, wxID_ANY, "");
		m_header->SetFont(wxFont(20, 70, 90, 90));
		m_header->SetMinSize(wxSize(-1, 100));
		sizer->Add(m_header, 1, wxALL, 5);

		m_date = new wxStaticText(top_panel, wxID_ANY, "");
		m_date->SetFont(wxFont(7, 70, 90, 90));
		sizer->Add(m_date, 0, wxALL | wxEXPAND, 5);

		m_desc = new wxStaticText(top_panel, wxID_ANY, "");
		sizer->Add(m_desc, 10, wxALIGN_TOP | wxALL | wxEXPAND, 5);

		m_link = new wxHyperlinkCtrl(top_panel, wxID_ANY, "Link", "");
		sizer->Add(m_link, 0, wxALIGN_TOP | wxALL | wxEXPAND, 5);

		top_sizer->Add(sizer, 1, wxALL | wxEXPAND, 5);
	}

	void show(const ItemData *d)
	{
		m_header->SetLabelText(d->title);
		m_date->SetLabelText(d->date);
		m_desc->SetLabelText(d->desc);

		m_link->SetURL(d->link);

		m_top_sizer->Layout();
	}

private:
	wxSizer *		 m_top_sizer;
	wxStaticText *	 m_header, *m_date, *m_desc;
	wxHyperlinkCtrl *m_link;
};