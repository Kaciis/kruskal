#include <X11/Xlib.h>
// #include "list.h"
// #include "color.h"

void DrawPoints(node *head, Display *display, Drawable window)
{
    GC gc;
    XGCValues values;
    unsigned long valuemask = 0;

    node *tmp = head;
    gc = XCreateGC(display, window, valuemask, &values);

    XSetForeground(display, gc, _RGB(255, 0, 127));

    while (tmp->next != NULL)
    {
        gc = XCreateGC(display, window, valuemask, &values);
        XSetForeground(display, gc, _RGB(255, 0, 127));

        tmp = tmp->next;
        XFillRectangle(display, window, gc, tmp->x - 5, tmp->y - 5, 10, 10);
        XFlush(display);
    }
}