#include <X11/Xlib.h>
#include <stdbool.h>
#include "color.h"
#include "trim.h"

void DrawButton(Display *display, Drawable window,int appMode, int x, int y, int width, int height, char *text, XEvent event, void (*f)(int))
{
    bool pressed = false;
    if (event.xbutton.y < 105)
    {
        switch (event.type)
        {
        case ButtonPress:
        {
            if (event.xbutton.button == 1)
            {

                if (event.xbutton.y > y && event.xbutton.y < y + height)
                {
                    if (event.xbutton.x > x && event.xbutton.x < x + width)
                    {
                        pressed = true;
                        // printf("%i, %i", event.xbutton.x, event.xbutton.y);
                    }
                }
            }
            break;
        }
        case ButtonRelease:
        {
            if (event.xbutton.button == 1)
            {
                pressed = false;

                if (event.xbutton.y > y && event.xbutton.y < y + height)
                {
                    if (event.xbutton.x > x && event.xbutton.x < x + width)
                    {
                        // event button press
                        
                        f(appMode);
                        pressed = false;
                    }
                }
            }
        }
        }
    }


    GC blackGC;
    GC grayGC;
    GC PressedGrayGC;

    XGCValues values;
    unsigned long valuemask = 0;

    blackGC = XCreateGC(display, window, valuemask, &values);
    grayGC = XCreateGC(display, window, valuemask, &values);
    PressedGrayGC = XCreateGC(display, window, valuemask, &values);

    // XSetForeground(display, blackGC, _RGB(255, 0, 127));
    XSetForeground(display, PressedGrayGC, _RGB(148, 148, 148));
    XSetForeground(display, grayGC, _RGB(186, 186, 186));

    XSetLineAttributes(display, blackGC, 2, 0, 0, 0); // 2 = thickness

    XDrawRectangle(display, window, blackGC, x, y, width, height);
    if (pressed)
    {
        XFillRectangle(display, window, PressedGrayGC, x + 1, y + 1, width - 2, height - 2);
    }
    else
    {
        XFillRectangle(display, window, grayGC, x + 1, y + 1, width - 2, height - 2);
    }


    XDrawString(display, window, blackGC, (x + width / 2) - 3 * strlen(text), (y + width / 2) + 2, text, strlen(text));
}
