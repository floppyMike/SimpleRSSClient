#pragma once

#include <wx/xml/xml.h>
#include <vector>

struct XMLConfig
{
	XMLConfig() = default;
	wxString title, desc, image, item, item_title, item_desc, item_image, item_link, item_date;
};

auto parse_config(const wxString &path, XMLConfig *conf) -> bool
{
	wxXmlDocument doc;
	if (!doc.Load(path))
		return false;

	if (doc.GetRoot()->GetName() != "RSS")
		return false;

	constexpr const char *children[]	   = { "title", "description", "image" };
	constexpr const char *entry_children[] = { "entry_name", "title", "description", "image", "link", "date" };

	for (auto *child = doc.GetRoot()->GetChildren(); child; child = child->GetNext())
	{
		for (size_t i = 0; i < sizeof(children) / sizeof(*children); ++i)
			if (child->GetName() == children[i])
			{
				*((wxString *)conf + i) = child->GetNodeContent();
				break;
			}

		if (child->GetName() == "entry")
			for (auto *childchild = child->GetChildren(); childchild; childchild = childchild->GetNext())
				for (size_t i = 0; i < sizeof(entry_children) / sizeof(*entry_children); ++i)
					if (childchild->GetName() == entry_children[i])
					{
						*((wxString *)conf + i + 3) = childchild->GetNodeContent();
						break;
					}
	}

	return true;
}

/*
<RSS>
	<title></title>
	<description></description>
	<image></image>
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