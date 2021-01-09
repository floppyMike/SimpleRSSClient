#pragma once

#include <wx/log.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/listctrl.h>
#include <wx/frame.h>

#include <array>
#include <utility>

#include "Data.hpp"
#include "View.hpp"

enum
{
	LIST_CTRL = 1000
};

class RSSList : public wxListCtrl
{
public:
	static constexpr auto COLUMNS =
		std::array{ std::pair<const char *, float>{ "Date", .25F }, std::pair<const char *, float>{ "Heading", .5F },
					std::pair<const char *, float>{ "Source", .25F } };

	explicit RSSList(const RSSDB *db, wxPanel *top_panel, wxSizer *top_sizer)
		: wxListCtrl(top_panel, LIST_CTRL, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_ALIGN_LEFT)
		, m_db(db)
	{
		// Add columns
		for (size_t i = 0; i < COLUMNS.size(); ++i)
			InsertColumn(i, _(COLUMNS[i].first), wxLIST_FORMAT_LEFT, GetSize().x * COLUMNS[i].second);

		top_sizer->Add(this, 1, wxEXPAND | wxALL, 10);
	}

	void push_set(Data *d)
	{
		size_t n = m_start.back();

		for (const auto &i : d->content.items)
		{
			wxListItem item;
			item.SetId(n);
			item.SetText(i.date);

			InsertItem(item);
			SetItem(n, 1, i.title);
			SetItem(n, 2, d->content.title);

			++n;
		}

		m_start.emplace_back(n);
	}

	template<typename Iter>
	void rebuild(const Iter begin,
				 const Iter end) requires std::same_as<typename std::iterator_traits<Iter>::value_type, Data>
	{
		DeleteAllItems();
		m_start = { 0 };
		for (size_t i = 0; i < std::distance(begin, end); ++i) push_set(&*(begin + i));
	}

	void on_col_beg_drag(wxListEvent &e) { e.Veto(); }
	void on_select(wxListEvent &e)
	{
		const auto i =
			std::find_if(m_start.begin(), m_start.end(), [idx = e.m_itemIndex](size_t i) { return i > idx; }) - 1;
		const auto &d = (*m_db)[std::distance(m_start.begin(), i)];

		wxLogDebug("Selected %s with %s.", d.content.title, d.content.items[e.m_itemIndex - *i].title);


	}

private:
	const RSSDB *		m_db;
	View *				m_view;
	std::vector<size_t> m_start = { 0 };

	wxDECLARE_NO_COPY_CLASS(RSSList);
	wxDECLARE_EVENT_TABLE();
};