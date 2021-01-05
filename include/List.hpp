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
		std::array{ std::pair<const char *, int>{ "Source", 100 }, std::pair<const char *, int>{ "Heading", 150 },
					std::pair<const char *, int>{ "Date", 50 } };

	void init(wxPanel *top_panel, wxSizer *top_sizer)
	{
		// Create pane with list
		m_item_list = new wxListCtrl(top_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);

		// Add columns
		for (size_t i = 0; i < COLUMNS.size(); ++i)
		{
			wxListItem c;
			c.SetId(i);
			c.SetText(_(COLUMNS[i].first));
			c.SetWidth(COLUMNS[i].second);
			m_item_list->InsertColumn(i, c);
		}

		const int item_amount = 10;
		for (int n = 0; n < item_amount; n++)
		{
			wxListItem item;
			item.SetId(n);
			item.SetText("Ass");

			m_item_list->InsertItem(item);

			// set value in second column
			m_item_list->SetItem(n, 1, "ass");

			// set value in third column
			m_item_list->SetItem(n, 2, "Noice");
		}

		top_sizer->Add(m_item_list, 1, wxEXPAND | wxALL, 10);
	}

private:
	wxListCtrl *m_item_list;
};