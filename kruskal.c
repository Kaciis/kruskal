#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <X11/Xlib.h>
#include <string.h>

int WINDOW_WIDTH = 600;
int WINDOW_HEIGHT = 600;

typedef struct node
{
    int x;
    int y;
    struct node *next;
} node;

node *create_node(int x, int y)
{
    node *new_node = malloc(sizeof(node));
    new_node->x = x;
    new_node->y = y;
    new_node->next = NULL;
    return new_node;
}

void Append(node *head, node *odeasdf)
{
    node *tmp = head;
    if (head == NULL)
    {
        head = odeasdf;
        return;
    }
    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    tmp->next = odeasdf;
    return;
}

int main(int argc, char **argv)
{

    struct node *head = NULL;

    head = create_node(-1, -1);

    // point1->next = point2;

    // for (int i = 0; i < 5; i++)
    // {
    //     struct node *point = NULL;
    //     point = create_node(i);
    //     Append(head, point);
    // }
    //     printf("head.x = %i, point2.x = %i, point3.x = %i, point4.x = %i, point6.x = %i\n", head->x, head->next->x, head->next->next->x, head->next->next->next->x, head->next->next->next->next->next->x);

    char *hello = "Hello world!";

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

    // XSelectInput(display, window, );
    XMapWindow(display, window);

    XSelectInput(display, window, ExposureMask | KeyPressMask | ButtonPressMask | ButtonReleaseMask);
    gc = XCreateGC(display, window, valuemask, &values);

    XSetLineAttributes(display, gc, 2, 0, 0, 0); // 2 = thickness

    myFont = XLoadQueryFont(display, "micro");
    
    while (1)
    {
        XAllowEvents(display, AsyncPointer, CurrentTime);

        XNextEvent(display, &event);
        switch (event.type)
        {
        case KeyPress:
        {
            printf("Key pressed: %s\n", XKeysymToString(XKeycodeToKeysym(display, event.xkey.keycode, 0)));
            break;
        }
        case ButtonPress:
        {
            if (event.xbutton.button == 1)
            {
                struct node *point = NULL;
                point = create_node(event.xbutton.x, event.xbutton.y);
                Append(head, point);
            }
            break;
        }
        }
        node *tmp = head;
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
            XFillRectangle(display, window, gc, tmp->x-5, tmp->y-5, 10, 10);
            // printf("x:%i\ty:%i\n", tmp->x, tmp->y);
        }

        XDrawLine(display, window, gc, 30, 30, 60, 60);
        XDrawString(display, window, gc, 60, 60, hello, strlen(hello));
    }

    XFreeGC(display, gc);
    XDestroyWindow(display, window);
    XCloseDisplay(display);
    return 0;
}