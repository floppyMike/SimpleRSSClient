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

/*
1. Create Window                        -> Done
2. Read configuration from file (XML)	-> 
3. Load file of the internet
4. Assign to correct values
5. Display the values
*/