#define WXDEBUG true

#include <wx/wxprec.h>
#include <wx/app.h>
#include <wx/event.h>

#include "Frame.hpp"

wxBEGIN_EVENT_TABLE(RSSList, wxListCtrl)
    EVT_LIST_COL_BEGIN_DRAG(LIST_CTRL, RSSList::on_col_beg_drag)
    EVT_LIST_ITEM_SELECTED(LIST_CTRL, RSSList::on_select)
wxEND_EVENT_TABLE()

class Core : public wxApp
{
public:
	auto OnInit() -> bool final
	{
		auto *f = new Frame();
		f->Show();
		return true;
	}
};

wxIMPLEMENT_APP(Core);

/*
1. Create Window                        -> Done
2. Read configuration from file (XML)	-> Done
3. Load file of the internet            -> Done
4. Assign to correct values             -> Done
5. Display the values
*/