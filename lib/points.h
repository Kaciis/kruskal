#include <X11/Xlib.h>
// #include "list.h"
// #include "color.h"

void DrawPoints(node_point *head, Display *display, Drawable window)
{
    GC gc;
    XGCValues values;
    unsigned long valuemask = 0;
    GC gcSelected;

    if (head != NULL)
    {
        node_point *tmp = head;
        gc = XCreateGC(display, window, valuemask, &values);
        XSetForeground(display, gc, _RGB(255, 0, 127));
        gcSelected = XCreateGC(display, window, valuemask, &values);
        XSetForeground(display, gcSelected, _RGB(0, 255, 0));

        do
        {
            if (tmp->point.selected)
            {
                XFillRectangle(display, window, gcSelected, tmp->point.x - 5, tmp->point.y - 5, 10, 10);
            }
            else
            {
                XFillRectangle(display, window, gc, tmp->point.x - 5, tmp->point.y - 5, 10, 10);
            }
            XFlush(display);
            // tmp = tmp->next;
        } while ((tmp = tmp->next) != NULL);
    }
}
