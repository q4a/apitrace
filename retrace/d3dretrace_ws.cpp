/**************************************************************************
 *
 * Copyright 2012 Jose Fonseca
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 **************************************************************************/


#include <assert.h>

#include "d3dretrace.hpp"

#ifdef _WIN32
#include "ws_win32.hpp"
#else
#include "glproc.hpp"
#include "glws.hpp"
#include "glws_xlib.hpp"
#endif


namespace d3dretrace {


#ifdef _WIN32
HWND
createWindow(int width, int height)
{
    HWND hWnd;

    hWnd = ws::createWindow("d3dretrace", width, height);

    ws::showWindow(hWnd);

    return hWnd;
}


typedef std::map<HWND, HWND> HWND_MAP;
static HWND_MAP g_hWndMap;


HWND
createWindow(HWND hWnd, int width, int height)
{
    HWND_MAP::iterator it;
    it = g_hWndMap.find(hWnd);
    if (it == g_hWndMap.end()) {
        // Create a new window
        hWnd = createWindow(width, height);
        g_hWndMap[hWnd] = hWnd;
    } else {
        // Reuse the existing window
        hWnd = it->second;
        ws::resizeWindow(hWnd, width, height);
    }
    return hWnd;
}
#else
Window
createWindow(int width, int height)
{
    //const GlxVisual *glxvisual = static_cast<const GlxVisual *>(glws::visual);
    //XVisualInfo *visinfo = glxvisual->visinfo;
    // FIXME: DXVK need to create Vulkan window
    XVisualInfo *visinfo;
    Window wnd = glws::createWindow(visinfo, "d3dretrace", width, height);
    glws::showWindow(wnd);

    return wnd;
}
#endif


#ifdef _WIN32
void
resizeWindow(HWND hWnd, int width, int height)
{
    ws::resizeWindow(hWnd, width, height);
}
#else
void
resizeWindow(Window window, int width, int height)
{
    glws::resizeWindow(window, width, height);
}
#endif


bool
processEvents(void)
{
#ifdef _WIN32
    return ws::processEvents();
#else
    return glws::processEvents();
#endif
}


} /* namespace d3dretrace */
