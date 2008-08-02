/*
 *
 *  C++ Portable Types Library (PTypes)
 *  Version 1.8.3  Released 25-Aug-2003
 *
 *  Copyright (c) 2001, 2002, 2003 Hovik Melikyan
 *
 *  http://www.melikyan.com/ptypes/
 *  http://ptypes.sourceforge.net/
 *
 */

#ifdef WIN32
#  include <windows.h>
#else
#  include <unistd.h>
#endif

#include "pstreams.h"


PTYPES_BEGIN


void infile::pipe(outfile& out)
{
#ifdef WIN32

    SECURITY_ATTRIBUTES sa;
    HANDLE h[2];

    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = NULL;

    if (!CreatePipe(&h[0], &h[1], &sa, 0))
#else
    int h[2];
    if (::pipe(h) != 0)
#endif
        error(uerrno(), "Couldn't create a local pipe");

    set_syshandle(int(h[0]));
    peerhandle = int(h[1]);
    out.set_syshandle(int(h[1]));
    out.peerhandle = int(h[0]);
    open();
    out.open();
}


PTYPES_END
