#pragma once

#include <wx/frame.h>
#include <wx/filedlg.h>
#include <wx/log.h>
#include <wx/menu.h>
#include <wx/msgdlg.h>

#include <vector>

#include "XMLDoc.hpp"
#include "List.hpp"
#include "View.hpp"
#include "Net.hpp"

enum
{
	ID_FIND_CONFIG = 1
};

class Frame : public wxFrame
{
public:
	Frame()
		: wxFrame(nullptr, wxID_ANY, "RSS Client", wxPoint(50, 50), wxSize(800, 600))
	{
		// Initialize Menu
		wxMenu *find_config = new wxMenu();
		find_config->Append(ID_FIND_CONFIG, "&Open config...\tCtrl-H", "Open a configuration file");

		wxMenuBar *bar = new wxMenuBar();
		bar->Append(find_config, "&Config");

		SetMenuBar(bar);

		CreateStatusBar();
		Bind(
			wxEVT_MENU, [this](auto &e) { on_config_open(e); }, ID_FIND_CONFIG);

		// Create Layout
		wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
		wxPanel *	pane  = new wxPanel(this);
		pane->SetSizer(sizer);

		// Initialize components
		m_list.init(pane, sizer);
		m_view.init(pane, sizer);
	}

	void on_config_open(wxCommandEvent &e)
	{
		wxFileDialog open_file(this, "Open XML file", "", "", "XML files (*.xml)|*.xml",
							   wxFD_OPEN | wxFD_FILE_MUST_EXIST);
		if (open_file.ShowModal() == wxID_CANCEL)
			return;

		m_data.emplace_back();
		if (!FileData::load(open_file.GetPath(), &m_data.back().config))
		{
			wxLogError("Cannot open file at: %s.", open_file.GetPath());
			return;
		}

		refresh(m_data.size() - 1);
	}

	void refresh(int pos)
	{
		parse_web(&m_data[pos]);
		m_list.update(&m_data[pos]);
	}

private:
	std::vector<Data> m_data;

	RSSList m_list;
	View	m_view;
};