#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <X11/Xlib.h>
#include <string.h>



int WINDOW_WIDTH = 600;
int WINDOW_HEIGHT = 600;

int main(int argc, char **argv)
{

char* hello = "Hello world!";

    XEvent event;
    Window window;
    int screen;
    Display *display;
    display = XOpenDisplay(NULL);
    GC gc;

    // XSelectInput(dpy, win, ExposureMask | KeyPressMask);
    // XMapWindow(dpy, win);
    XGCValues values;
    unsigned long valuemask = 0;

    XFontStruct *myFont;

    if (display == NULL)
    {
        printf("nic tu neni");
        exit(1);
    }
    screen = DefaultScreen(display);
    window = XCreateSimpleWindow(display, RootWindow(display, screen), 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, 1, BlackPixel(display, screen), WhitePixel(display, screen));
    XMapWindow(display, window);

    XSelectInput(display, window, ExposureMask | KeyPressMask);
    gc = XCreateGC(display, window, valuemask, &values);

    XSetLineAttributes(display, gc, 2, 0, 0, 0); // 2 = thickness

    myFont = XLoadQueryFont(display, "-misc-fixed-medium-r-normal--9-90-75-75-c-60-iso10646-1");
    while (1)
    {
        XNextEvent(display, &event);

        XDrawLine(display, window, gc, 30, 30, 60, 60);
                XDrawString(display, window, gc, 60, 60, hello, strlen(hello)); 

    }


    XFreeGC(display, gc);
XDestroyWindow(display, window);
XCloseDisplay(display);

return 0;
}