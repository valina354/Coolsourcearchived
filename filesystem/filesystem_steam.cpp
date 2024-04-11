//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#include "basefilesystem.h"
#include "steamcommon.h"
#include "SteamInterface.h"
#include "tier0/dbg.h"
#include "tier0/icommandline.h"
#include "steam/steam_api.h"
#ifdef POSIX
#include <fcntl.h>
#ifdef LINUX
#include <sys/file.h>
#endif
#include <dlfcn.h>
#define _S_IWRITE S_IWRITE 
#define _S_IWRITE S_IWRITE
#define _S_IFREG S_IFREG
#define FILE_ATTRIBUTE_OFFLINE 0x1000
#endif

