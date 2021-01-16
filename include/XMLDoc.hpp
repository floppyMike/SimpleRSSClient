#pragma once

#include <wx/xml/xml.h>

#include <array>

#include "Data.hpp"

class FileData
{
public:
	static constexpr auto DESCRIB	   = std::array{ "title", "description", "image", "url" };
	static constexpr auto ITEM_DESCRIB = std::array{ "entry_name", "title", "description", "image", "link", "date" };

	FileData() = default;

	static auto load(const wxString &path, ConfigData *d) -> bool
	{
		wxXmlDocument doc;
		if (!doc.Load(path))
			return false;

		if (doc.GetRoot()->GetName() != "RSS")
			return false;

		_recurse_(doc.GetRoot()->GetChildren(), (wxString *)d, DESCRIB.begin(), DESCRIB.end(), 0, "entry");
		return true;
	}

private:
	template<typename Iter>
	static void _recurse_(wxXmlNode *n, wxString *str, Iter i1, Iter i2, ptrdiff_t offset, std::string_view parent = "")
	{
		for (; n; n = n->GetNext())
			if (const auto i = std::find_if(i1, i2, [n](const char *str) { return str == n->GetName(); }); i != i2)
				str[std::distance(i1, i) + offset] = n->GetNodeContent();
			else if (!parent.empty() && n->GetName() == parent.data())
				_recurse_(n->GetChildren(), str, ITEM_DESCRIB.begin(), ITEM_DESCRIB.end(), 4);
	}
};

auto find_node(wxXmlNode *n, const wxCStrData &str) -> wxXmlNode *
{
	for (; n != nullptr && n->GetName() != str; n = n->GetNext())
		;

	return n;
}

/*
<RSS>
	<title></title>
	<description></description>
	<image></image>
	<url></url>
	<entry>
		<entry_name></entry_name>
		<title></title>
		<description></description>
		<image></image>
		<link></link>
		<date></date>
	</entry>
</RSS>
*/