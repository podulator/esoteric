/***************************************************************************
 *   Copyright (C) 2006 by Massimiliano Torromeo   *
 *   massimiliano.torromeo@gmail.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "menusettingimage.h"
#include "browsedialog.h"
#include "utilities.h"

MenuSettingImage::MenuSettingImage(	Esoteric *app, 
									const std::string &title, 
									const std::string &description, 
									std::string *value, 
									const std::string &filter, 
									const std::string &startPath, 
									const std::string &dialogTitle, 
									const std::string &dialogIcon, 
									const std::string &skin) 
	: MenuSettingFile(app, title, description, value, filter, startPath, dialogTitle, dialogIcon) {
		this->skin = skin;
	}

void MenuSettingImage::setValue(const std::string &value) {
	std::string skinpath(app->getExePath() + "skins/" + skin);
	bool inSkinDir = value.substr(0, skinpath.length()) == skinpath;
	if (!inSkinDir && skin != "Default") {
		skinpath = app->getExePath() + "skins/Default";
		inSkinDir = value.substr(0, skinpath.length()) == skinpath;
	}
	if (inSkinDir) {
		std::string tempIcon = value.substr(skinpath.length(), value.length());
		std::string::size_type pos = tempIcon.find("/");
		if (pos != std::string::npos) {
			*_value = "skin:" + tempIcon.substr(pos + 1, value.length());
		} else {
			*_value = value;
		}
	} else {
		*_value = value;
	}
}
