#pragma once

#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/listctrl.h>
#include <wx/frame.h>

#include <array>
#include <utility>

class RSSList
{
public:
	static constexpr auto COLUMNS =
		std::array{ std::pair<const char *, float>{ "Source", .25F }, std::pair<const char *, float>{ "Heading", .5F },
					std::pair<const char *, float>{ "Date", .25F } };

	void init(wxPanel *top_panel, wxSizer *top_sizer)
	{
		// Create pane with list
		m_item_list =
			new wxListCtrl(top_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_ALIGN_LEFT);

		// Add columns
		for (size_t i = 0; i < COLUMNS.size(); ++i)
		{
			m_item_list->InsertColumn(i, _(COLUMNS[i].first), wxLIST_FORMAT_LEFT,
									  m_item_list->GetSize().x * COLUMNS[i].second);
		}

		top_sizer->Add(m_item_list, 1, wxEXPAND | wxALL, 10);
	}

private:
	wxListCtrl *m_item_list;
};