/* $Id$ */
/*
 *  Copyright (c) 2008 Nick Schermer <nick@xfce.org>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <xfconf/xfconf.h>
#include <gdk/gdk.h>
#include <X11/extensions/Xrandr.h>

#ifndef __XFCE_RANDR_H__
#define __XFCE_RANDR_H__

#define XFCE_RANDR_MODE(randr)        (randr->mode[randr->active_output])
#define XFCE_RANDR_ROTATION(randr)    (randr->rotation[randr->active_output])
#define XFCE_RANDR_OUTPUT_INFO(randr) (randr->output_info[randr->active_output])

/* check for randr 1.2 or better */
#if RANDR_MAJOR > 1 || (RANDR_MAJOR == 1 && RANDR_MINOR >= 2)
#define HAS_RANDR_ONE_POINT_TWO
#else
#undef HAS_RANDR_ONE_POINT_TWO
#endif

#ifdef HAS_RANDR_ONE_POINT_TWO
typedef struct _XfceRandr          XfceRandr;
typedef enum   _XfceDisplayLayout  XfceDisplayLayout;
typedef enum   _XfceOutputPosition XfceOutputPosition;
typedef enum   _XfceOutputStatus   XfceOutputStatus;

enum _XfceDisplayLayout
{
    XFCE_DISPLAY_LAYOUT_SINGLE,
    XFCE_DISPLAY_LAYOUT_CLONE,
    XFCE_DISPLAY_LAYOUT_EXTEND
};

enum _XfceOutputPosition
{
    XFCE_OUTPUT_POSITION_LEFT,
    XFCE_OUTPUT_POSITION_RIGHT,
    XFCE_OUTPUT_POSITION_TOP,
    XFCE_OUTPUT_POSITION_BOTTOM
};

enum _XfceOutputStatus
{
    XFCE_OUTPUT_STATUS_NONE,
    XFCE_OUTPUT_STATUS_PRIMARY,
    XFCE_OUTPUT_STATUS_SECONDARY
};

struct _XfceRandr
{
    /* display for this randr config */
    GdkDisplay          *display;
    
    /* screen resource for this display */
    XRRScreenResources  *resources;

    /* the active selected layout */
    gint                 active_output;

    /* cache for the output info */
    XRROutputInfo      **output_info;

    /* selected display layout */
    XfceDisplayLayout    layout;

    /* selected settings for all outputs */
    RRMode              *mode;
    Rotation            *rotation;
    XfceOutputPosition  *position;
    XfceOutputStatus    *status;
};



XfceRandr   *xfce_randr_new           (GdkDisplay    *display);

void         xfce_randr_free          (XfceRandr     *randr);

void         xfce_randr_reload        (XfceRandr     *randr);

void         xfce_randr_save          (XfceRandr     *randr,
                                       const gchar   *scheme,
                                       XfconfChannel *channel);

void         xfce_randr_load          (XfceRandr     *randr,
                                       const gchar   *scheme,
                                       XfconfChannel *channel);

const gchar *xfce_randr_friendly_name (const gchar   *name);

#endif /* !HAS_RANDR_ONE_POINT_TWO */

#endif /* !__XFCE_RANDR_H__ */