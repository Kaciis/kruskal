typedef struct node_point
{
    point point;
    struct node_point *next;
} node_point;


node_point *create_node_point(point point)
{

    node_point *new_node = malloc(sizeof(node_point));
    new_node->point = point;
    new_node->next = NULL;
    return new_node;
}

node_edge *create_node_edge(edge Edge)
{

    node_edge *new_node = malloc(sizeof(node_edge));
    new_node->edge = Edge;
    new_node->next = NULL;
    return new_node;
}

void AppendEdge(node_edge *head, node_edge *new_node)
{
    node_edge *tmp = head;
    if (head == NULL)
    {
        head = new_node;
        return;
    }
    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    // tmp->point.selected = false;
    tmp->next = new_node;

    return;
}

void AppendPoint(node_point *head, node_point *new_node)
{
    node_point *tmp = head;
    if (head == NULL)
    {
        head = new_node;
        return;
    }
    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    // tmp->point.selected = false;
    tmp->next = new_node;

    return;
}

void printList(struct node_edge *start)
{
    struct node_edge *temp = start;
    // printf("\n");
    while (temp!=NULL)
    {
        printf("%i ", temp->edge.weight);
        temp = temp->next;
    }
    printf("\n");
}