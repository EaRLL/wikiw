/*
* This file is part of WikiW <https://github.com/EaRLL/wikiw>.
*
* File: ver.h
*
* WikiW is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* WikiW is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with WikiW.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#define STRINGIZE2(s) #s
#define STRINGIZE(s) STRINGIZE2(s)

#define APP_VERSION_MAJOR               1
#define APP_VERSION_MINOR               0
#define APP_VERSION_REVISION            1
#define APP_VERSION_BUILD               595

#define APP_VERSION_FILE                APP_VERSION_MAJOR, APP_VERSION_MINOR, APP_VERSION_REVISION, APP_VERSION_BUILD
#define APP_VERSION_FILE_STR            STRINGIZE(APP_VERSION_MAJOR) "." STRINGIZE ( APP_VERSION_MINOR ) "." STRINGIZE ( APP_VERSION_REVISION ) " build " STRINGIZE ( APP_VERSION_BUILD )

#define APP_VERSION_COMMENTS            "Beta. Please contact abix.group@gmail.com with any bug reports, suggestions or comments.\0"
