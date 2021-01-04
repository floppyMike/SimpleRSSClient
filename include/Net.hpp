#pragma once

#include "XMLDoc.hpp"

auto query(const wxString &url, wxInputStream *s) -> bool
{
	wxURL q(url);
	if (q.GetError() != wxURL_NOERR)
		return false;

	s = q.GetInputStream();

	return true;
}
