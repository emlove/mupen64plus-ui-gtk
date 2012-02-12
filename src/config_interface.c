/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *   Mupen64plus-ui-gtk - config_interface.c                               *
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

/* This is the main application entry point for the console-only front-end
 * for Mupen64Plus v2.0. 
 */
#include "config_interface.h"

#include <stdio.h>
#include <stdlib.h>
#include "core_interface.h"
#include "osal_preproc.h"

/** static (local) variables **/
static m64p_handle l_ConfigCore = NULL;
static m64p_handle l_ConfigVideo = NULL;
static m64p_handle l_ConfigUI = NULL;

static m64p_error OpenConfigurationHandles()
{
    m64p_error rval;

    /* Open Configuration sections for core library and console User Interface */
    rval = (*ConfigOpenSection)("Core", &l_ConfigCore);
    if (rval != M64ERR_SUCCESS)
    {
        fprintf(stderr, "Error: failed to open 'Core' configuration section\n");
        return rval;
    }

    rval = (*ConfigOpenSection)("Video-General", &l_ConfigVideo);
    if (rval != M64ERR_SUCCESS)
    {
        fprintf(stderr, "Error: failed to open 'Video-General' configuration section\n");
        return rval;
    }

    rval = (*ConfigOpenSection)("UI-Console", &l_ConfigUI);
    if (rval != M64ERR_SUCCESS)
    {
        fprintf(stderr, "Error: failed to open 'UI-Console' configuration section\n");
        return rval;
    }

    /* Set default values for my Config parameters */
    (*ConfigSetDefaultString)(l_ConfigUI, "PluginDir", OSAL_CURRENT_DIR, "Directory in which to search for plugins");
    (*ConfigSetDefaultString)(l_ConfigUI, "VideoPlugin", "mupen64plus-video-rice" OSAL_DLL_EXTENSION, "Filename of video plugin");
    (*ConfigSetDefaultString)(l_ConfigUI, "AudioPlugin", "mupen64plus-audio-sdl" OSAL_DLL_EXTENSION, "Filename of audio plugin");
    (*ConfigSetDefaultString)(l_ConfigUI, "InputPlugin", "mupen64plus-input-sdl" OSAL_DLL_EXTENSION, "Filename of input plugin");
    (*ConfigSetDefaultString)(l_ConfigUI, "RspPlugin", "mupen64plus-rsp-hle" OSAL_DLL_EXTENSION, "Filename of RSP plugin");

    return M64ERR_SUCCESS;
}

m64p_error ConfigGetSectionHandle(config_section ConfigSection, m64p_handle *ConfigSectionHandle) {
    if (l_ConfigCore == NULL) {
        OpenConfigurationHandles();
    }
    if (ConfigSection == CONFIG_SECTION_CORE) {
        (*ConfigSectionHandle) = l_ConfigCore;
    } else if (ConfigSection == CONFIG_SECTION_VIDEO) {
        (*ConfigSectionHandle) = l_ConfigVideo;
    } else if (ConfigSection == CONFIG_SECTION_UI) {
        (*ConfigSectionHandle) = l_ConfigUI;
    } else {
        return M64ERR_INPUT_INVALID;
    }
    
    return M64ERR_SUCCESS;
}

m64p_error ConfigGet(config_section ConfigSection, 
                        const char *ParamName, 
                        m64p_type ParamType, 
                        void *ParamValue, 
                        int MaxSize)
{
    m64p_handle ConfigSectionHandle;
    m64p_error err = ConfigGetSectionHandle(ConfigSection, &ConfigSectionHandle);
    if (err != M64ERR_SUCCESS) {
        return err;
    }
    
    return (*ConfigGetParameter)(ConfigSectionHandle, ParamName, ParamType, ParamValue, MaxSize);      
}

m64p_error ConfigSet(config_section ConfigSection, 
                        const char *ParamName, 
                        m64p_type ParamType, 
                        const void *ParamValue)
{
    m64p_handle ConfigSectionHandle;
    m64p_error err = ConfigGetSectionHandle(ConfigSection, &ConfigSectionHandle);
    if (err != M64ERR_SUCCESS) {
        return err;
    }
    
    return (*ConfigSetParameter)(ConfigSectionHandle, ParamName, ParamType, ParamValue);            
}

