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
	ID_FIND_CONFIG = 1,
	ID_REFRESH
};

class Frame : public wxFrame
{
public:
	Frame()
		: wxFrame(nullptr, wxID_ANY, "RSS Client", wxDefaultPosition, wxSize(800, 600))
	{
		// Initialize Menu
		wxMenu *config_tab = new wxMenu();
		config_tab->Append(ID_FIND_CONFIG, "&Open config...\tCtrl-H", "Open a configuration file");
		config_tab->Append(ID_REFRESH, "&Refresh\tCtrl-r", "Refresh list");

		wxMenuBar *bar = new wxMenuBar();
		bar->Append(config_tab, "&Config");

		SetMenuBar(bar);

		CreateStatusBar();
		Bind(
			wxEVT_MENU, [this](auto &e) { on_config_open(e); }, ID_FIND_CONFIG);
		Bind(
			wxEVT_MENU, [this](auto &e) { on_refresh(e); }, ID_REFRESH);

		// Create Layout
		wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
		wxPanel *	pane  = new wxPanel(this);

		// Initialize components
		m_list = new RSSList(&m_data, &m_view, pane, sizer);
		m_view.init(pane, sizer);

		pane->SetSizer(sizer);
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

	void on_refresh(wxCommandEvent &e) { m_list->rebuild(m_data.begin(), m_data.end()); }

	void refresh(int pos)
	{
		parse_web(&m_data[pos]);
		m_list->push_set(&m_data[pos]);
	}

private:
	RSSDB	 m_data;
	RSSList *m_list;
	View	 m_view;
};