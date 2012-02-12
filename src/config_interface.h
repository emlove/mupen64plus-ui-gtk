/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *   Mupen64plus-ui-gtk - config_interface.h                               *
 *   Mupen64Plus homepage: http://code.google.com/p/mupen64plus/           *
 *   Copyright (C) 2012 Adam Mills                                         *
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
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.          *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __CONFIG_INTERFACE_H__
#define __CONFIG_INTERFACE_H__

#include "m64p_types.h"

typedef enum {
  CONFIG_SECTION_CORE = 1,
  CONFIG_SECTION_VIDEO,
  CONFIG_SECTION_UI
} config_section;

m64p_error ConfigGetSectionHandle(config_section ConfigSection, m64p_handle *ConfigSectionHandle);

m64p_error ConfigGet(config_section ConfigSection, 
                        const char *ParamName, 
                        m64p_type ParamType, 
                        void *ParamValue, 
                        int MaxSize);
m64p_error ConfigSet(config_section ConfigSection, 
                        const char *ParamName, 
                        m64p_type ParamType, 
                        const void *ParamValue);

#endif /* __CONFIG_INTERFACE_H__ */

