#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <X11/Xlib.h>
#include <string.h>
#include "lib/button.h"
#include "lib/list.h"
#include "lib/points.h"

int WINDOW_WIDTH = 600;
int WINDOW_HEIGHT = 600;

enum mode
{
    points,
    ways,
    compute
};

int main(int argc, char **argv)
{

    int noOfButtons = 2;

    enum mode appMode = points;

    struct node *head = NULL;

    head = create_node(-1, -1);

    char *hello = "Hello world!";

    XEvent event;
    Window window;
    int screen;
    Display *display;
    display = XOpenDisplay(NULL);
    GC gc;
    GC gc2;

    // XSelectInput(dpy, win, ExposureMask | KeyPressMask);
    // XMapWindow(dpy, win);
    XGCValues values;
    unsigned long valuemask = 0;

    XFontStruct *myFont;
    myFont = XLoadQueryFont(display, "micro");

    if (display == NULL)
    {
        printf("nic tu neni");
        exit(1);
    }
    screen = DefaultScreen(display);
    window = XCreateSimpleWindow(display, RootWindow(display, screen), 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, 1, BlackPixel(display, screen), WhitePixel(display, screen));

    // XSelectInput(display, window, );
    XMapWindow(display, window);

    XSelectInput(display, window, ExposureMask | KeyPressMask | ButtonPressMask | ButtonReleaseMask);
    gc = XCreateGC(display, window, valuemask, &values);
    gc2 = XCreateGC(display, window, valuemask, &values);

    XSetLineAttributes(display, gc, 2, 0, 0, 0); // 2 = thickness
    Bool tlacitka[] = {false, false};

    while (1)
    {
        XWindowAttributes windowInfo;
        XGetWindowAttributes(display, window, &windowInfo);

        XAllowEvents(display, AsyncPointer, CurrentTime);

        XNextEvent(display, &event);
        switch (event.type)
        {
            // case KeyPress:
            // {
            //     printf("Key pressed: %s\n", XKeysymToString(XKeycodeToKeysym(display, event.xkey.keycode, 0)));
            //     break;
            // }
        case ButtonPress:
        {
            if (event.xbutton.button == 1)
            {
                if (event.xbutton.y > 105)
                {
                    if (appMode == 0)
                    {
                        struct node *point = NULL;
                        point = create_node(event.xbutton.x, event.xbutton.y);
                        Append(head, point);
                    }
                }
            }
            break;
        }
        }

        DrawPoints(head, display, window);

        // printf("%i\n", atr.width);

        XDrawLine(display, window, gc2, 10, 100, windowInfo.width - 10, 100);

        DrawButton(display, window, 20, 20, 60, 60, "press me", event);
        DrawButton(display, window, 90, 20, 60, 60, "text", event);

        // XDrawString(display, window, gc2, 60, 60, hello, strlen(hello));
    }

    XFreeGC(display, gc);
    XDestroyWindow(display, window);
    XCloseDisplay(display);
    return 0;
}