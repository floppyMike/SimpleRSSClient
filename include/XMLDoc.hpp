#pragma once

#include <wx/xml/xml.h>
#include <wx/url.h>

#include <vector>
#include <array>
#include <string_view>
#include <span>

struct QueryResult
{
	QueryResult() = default;
	wxString title, desc, image, item, item_title, item_desc, item_image, item_link, item_date;
};

class XMLStructure
{
	enum
	{
		TITLE,
		DESC,
		IMG,
		URL,
		ITEM,
		ITEM_TITLE,
		ITEM_DESC,
		ITEM_IMG,
		ITEM_LINK,
		ITEM_DATE,
		ALL
	};

public:
	static constexpr auto DESCRIB	   = std::array{ "title", "description", "image", "url" };
	static constexpr auto ITEM_DESCRIB = std::array{ "entry_name", "title", "description", "image", "link", "date" };

	XMLStructure() = default;

	auto load(const wxString &path) -> bool
	{
		wxXmlDocument doc;
		if (!doc.Load(path))
			return false;

		if (doc.GetRoot()->GetName() != "RSS")
			return false;

		_recurse_(doc.GetRoot()->GetChildren(), DESCRIB.begin(), DESCRIB.end(), 0, "entry");
		return true;
	}

	[[nodiscard]] auto name() const noexcept -> const auto & { return m_str[TITLE]; }

private:
	std::array<wxString, ALL> m_str;

	template<typename Iter>
	void _recurse_(wxXmlNode *n, Iter i1, Iter i2, ptrdiff_t offset, std::string_view parent = "")
	{
		for (; n; n = n->GetNext())
			if (const auto i = std::find_if(i1, i2, [n](const char *str) { return str == n->GetName(); }); i != i2)
				m_str[std::distance(i1, i) + offset] = n->GetNodeContent();
			else if (!parent.empty() && n->GetName() == parent.data())
				_recurse_(n->GetChildren(), ITEM_DESCRIB.begin(), ITEM_DESCRIB.end(), ITEM);
	}
};

auto parse_config(const wxString &path, QueryResult *conf) -> bool
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

auto parse_xml(wxInputStream *in, wxString *out, const char **children, const char **entry_children) -> bool {}

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