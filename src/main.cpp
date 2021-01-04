#include <wx/wxprec.h>
#include <wx/app.h>

#include "Frame.hpp"

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