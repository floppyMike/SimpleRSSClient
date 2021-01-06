#pragma once

#include <wx/url.h>
#include <wx/log.h>
#include "XMLDoc.hpp"

auto query(const wxString &url, wxInputStream *s) -> bool
{
	wxURL q(url);
	if (q.GetError() != wxURL_NOERR)
		return false;

	s = q.GetInputStream();

	return true;
}

class XMLParser
{
public:
	XMLParser(wxXmlDocument *xml, ConfigData *d)
		: m_xml(xml)
		, m_d(d)
		, m_item(_recurse_(m_xml->GetRoot(), d->item.c_str().AsChar()))
	{
		//m_item = find_node(m_item, m_d->item);
	}

	auto title() { return _direct_(m_d->title); }
	auto descr() { return _direct_(m_d->desc); }
	auto image() { return _direct_(m_d->image); }

	auto next_item(ItemData *d) -> bool
	{
		if (!m_item)
			return false;

		for (auto *n = m_item->GetChildren(); n; n = n->GetNext())
			for (size_t i = 0; i < 5; ++i)
				if (n->GetName() == ((wxString *)m_d)[i + 5])
                {
					((wxString *)d)[i] = n->GetNodeContent();
                    break;
                }

		m_item = m_item->GetNext();
		return true;
	}

private:
	wxXmlDocument *m_xml;
	ConfigData *   m_d;

	wxXmlNode *m_item;

	auto _direct_(const wxCStrData &str) -> wxString
	{
		return _recurse_(m_xml->GetRoot(), str.AsChar())->GetNodeContent();
	}

	auto _recurse_(wxXmlNode *target, const wxString &str) -> wxXmlNode *
	{
		size_t pos = str.find(' ');
		wxLogDebug("Finding %s in %s", str.substr(0, pos), target->GetName());
		auto *const t = find_node(target->GetChildren(), str.substr(0, pos));

		if (!t)
			return target;

		return _recurse_(t, str.substr(pos + 1));

		// for (wxXmlNode *n = target; true;)
		// {
		// 	const auto fh = str.substr(str.find(' '));

		// 	if (auto *const t = find_node(n, fh.data()); t == n)
		// 		return n;
		// 	else
		// 		n = t;

		// 	str = str.substr(fh.size() + 2);
		// }
	}
};

auto parse_web(Data *data)
{
	wxURL q(data->config.url);
	if (q.GetError() != wxURL_NOERR)
		return false;

	wxInputStream *in = q.GetInputStream();

	wxXmlDocument xml;
	xml.Load(*in);
	// xml.Save("arpa.xml");
	XMLParser parser(&xml, &data->config);

	data->content.title = parser.title();
	data->content.desc	= parser.descr();
	data->content.image = parser.image();

	while (parser.next_item(&data->content.items.emplace_back()))
		;
    return true;
}