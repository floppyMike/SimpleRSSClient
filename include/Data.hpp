#pragma once

#include <wx/string.h>
#include <vector>

struct ItemData
{
	ItemData() = default;
	wxString title, desc, image, link, date;
};

struct WebData
{
	WebData() = default;
	wxString			  title, desc, image;
	std::vector<ItemData> items;
};

struct ConfigData
{
	ConfigData() = default;
	wxString title, desc, image, url, item, item_title, item_desc, item_image, item_link, item_date;
};

struct Data
{
	Data() = default;
	ConfigData config;
	WebData	   content;
};

using RSSDB = std::vector<Data>;