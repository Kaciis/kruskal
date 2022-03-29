#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <X11/Xlib.h>
#include <string.h>
#include <unistd.h>
#include "lib/point_type.h"
#include "lib/edge.h"
#include "lib/button.h"
#include "lib/list.h"
#include "lib/points.h"
#include "lib/kruskal.h"

int WINDOW_WIDTH = 600;
int WINDOW_HEIGHT = 600;

edge currentEdge;

int appMode = 0;

void changeAppMode(int mode)
{
    appMode = mode;
}

typedef struct edgeData
{
    int poradi;
    node_edge *head;
} edgeData;

edgeData choose(node_point *pointNode, int number, node_point *head_point, node_edge *head_edge);
int main(int argc, char **argv)
{

    int noOfButtons = 2;

    struct node_point *headPoints = NULL;
    struct node_edge *headEdges = NULL;

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

    int connect = 0;

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

                        point new_point;
                        new_point.y = event.xbutton.y;
                        new_point.x = event.xbutton.x;
                        new_point.selected = false;
                        if (headPoints == NULL)
                        {
                            headPoints = create_node_point(new_point);
                            printf("point created at [%i; %i]\n", new_point.x, new_point.y);
                        }
                        else
                        {
                            node_point *tmp = headPoints;
                            bool blizko = false;
                            if (tmp->point.x >= new_point.x - 12 && tmp->point.x <= new_point.x + 12 && tmp->point.y >= new_point.y - 12 && tmp->point.y <= new_point.y + 12)
                            {
                                // printf("blizko\n");
                                blizko = true;
                            }
                            else
                            {
                                while (tmp->next != NULL)
                                {
                                    tmp = tmp->next;
                                    if (tmp->point.x >= new_point.x - 12 && tmp->point.x <= new_point.x + 12 && tmp->point.y >= new_point.y - 12 && tmp->point.y <= new_point.y + 12)
                                    {
                                        // printf("blizko\n");
                                        blizko = true;
                                        break;
                                    }
                                }
                            }

                            if (!blizko)
                            {
                                struct node_point *new_node;
                                new_node = create_node_point(new_point);
                                AppendPoint(headPoints, new_node);
                                printf("point created at [%i; %i]\n", new_point.x, new_point.y);
                            }
                        }
                    }
                    else if (appMode == 1)
                    {
                        point new_point;
                        new_point.y = event.xbutton.y;
                        new_point.x = event.xbutton.x;
                        if (headPoints != NULL && headPoints->next != NULL)
                        {
                            node_point *tmp = headPoints;
                            if (tmp->point.x >= new_point.x - 6 && tmp->point.x <= new_point.x + 6 && tmp->point.y >= new_point.y - 6 && tmp->point.y <= new_point.y + 6)
                            {
                                edgeData data = choose(tmp, connect, headPoints, headEdges);
                                connect = data.poradi;
                                headEdges = data.head;
                            }
                            else
                            {
                                while (tmp->next != NULL)
                                {
                                    tmp = tmp->next;
                                    if (tmp->point.x >= new_point.x - 6 && tmp->point.x <= new_point.x + 6 && tmp->point.y >= new_point.y - 6 && tmp->point.y <= new_point.y + 6)
                                    {
                                        edgeData data = choose(tmp, connect, headPoints, headEdges);
                                        connect = data.poradi;
                                        headEdges = data.head;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            break;
        }
        }
        DrawButton(display, window, 0, 20, 20, 60, 60, "pridat", event, changeAppMode);
        DrawButton(display, window, 1, 90, 20, 60, 60, "spojovat", event, changeAppMode);
        DrawButton(display, window, 2, 160, 20, 60, 60, "hledat", event, changeAppMode);

        DrawEdges(headEdges, display, window);

        DrawPoints(headPoints, display, window);

        XDrawLine(display, window, gc2, 10, 100, windowInfo.width - 10, 100);


        // printf("%i", appMode);
    }
}

edgeData choose(node_point *pointNode, int number, node_point *head_point, node_edge *head_edge)
{

    switch (number)
    {
    case 0:

        pointNode->point.selected = true;
        currentEdge.from = pointNode->point;
        number++;
        break;
    case 1:
        if (!(currentEdge.from.x == pointNode->point.x && currentEdge.from.y == pointNode->point.y))
        {
            currentEdge.to = pointNode->point;

            int distanceX = abs(currentEdge.from.x - currentEdge.to.x);
            int distanceY = abs(currentEdge.from.y - currentEdge.to.y);

            currentEdge.weight = sqrt((distanceX * distanceX) + (distanceY * distanceY));

            if (head_edge == NULL)
            {
                edge new_edge;
                new_edge.from.y = currentEdge.from.y;
                new_edge.from.x = currentEdge.from.x;
                new_edge.to.x = currentEdge.to.x;
                new_edge.to.y = currentEdge.to.y;
                new_edge.weight = currentEdge.weight;
                head_edge = create_node_edge(new_edge);
            }
            else
            {

                struct node_edge *new_node;
                edge new_edge;
                new_edge.from = currentEdge.from;
                new_edge.to = currentEdge.to;
                new_edge.weight = currentEdge.weight;
                new_node = create_node_edge(new_edge);

                AppendEdge(head_edge, new_node);
                printf("created new edge with weight of %i\n", currentEdge.weight);
            }

            node_point *tmp = head_point;
            while (tmp != NULL)
            {
                tmp->point.selected = false;
                tmp = tmp->next;
            }

            number--;
        }
        else
        {
            printf("stejnej bod\n");
        }

        break;
    default:
        break;
    }
    edgeData data;

    data.head = head_edge;
    data.poradi = number;
    return data;
}
