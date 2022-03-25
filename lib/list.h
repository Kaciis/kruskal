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
        if (tmp->x >= odeasdf->x - 12 && tmp->x <= odeasdf->x +12 && tmp->y >= odeasdf->y -12 && tmp->y <= odeasdf->y + 12)
            return;
    }

    tmp->next = odeasdf;
    printf("point created at [%i; %i]\n", tmp->next->x, tmp->next->y);

    return;
}