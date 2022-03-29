
typedef struct edge
{
    point from;
    point to;
    int weight;
} edge;

typedef struct node_edge
{
    edge edge;
    struct node_edge *next;
} node_edge;

void DrawEdges(node_edge *head, Display *display, Drawable window)
{
    GC gc;
    XGCValues values;
    unsigned long valuemask = 0;
    GC gcSelected;

    if (head != NULL)
    {
        ;
        node_edge *tmp = head;
        gc = XCreateGC(display, window, valuemask, &values);
        XSetLineAttributes(display, gc, 2, 0, 0, 0); // 2 = thickness

        // XSetForeground(display, gc, _RGB(255, 0, 127));
        // gcSelected = XCreateGC(display, window, valuemask, &values);
        // XSetForeground(display, gcSelected, _RGB(0, 255, 0));

        do
        {
            XDrawLine(display, window, gc, tmp->edge.from.x, tmp->edge.from.y, tmp->edge.to.x, tmp->edge.to.y);
            // if (tmp->point.selected)
            // {
            //     XDrawLine(display, window, gcSelected, tmp->point.x - 5, tmp->point.y - 5, 10, 10);
            // }
            // else
            // {
            //     XDrawLine(display, window, gc, tmp->point.x - 5, tmp->point.y - 5, 10, 10);
            // }
            XFlush(display);
            // tmp = tmp->next;
        } while ((tmp = tmp->next) != NULL);
    }
}

