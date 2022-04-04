using System;	

class GFG
{

static int V = 5;
static int[] parent = new int[V];
static int INF = int.MaxValue;

static int find(int i)
{
	while (parent[i] != i)
		i = parent[i];
	return i;
}

static void union1(int i, int j)
{
	int a = find(i);
	int b = find(j);
	parent[a] = b;
}

static void kruskalMST(int [,]cost)
{
	int mincost = 0; // Cena minimalni kostry

	for (int i = 0; i < V; i++)
		parent[i] = i;

	
	int edge_count = 0;
	while (edge_count < V - 1)
	{
		int min = INF, a = -1, b = -1;
		for (int i = 0; i < V; i++)
		{
			for (int j = 0; j < V; j++)
			{
				if (find(i) != find(j) && cost[i, j] < min)
				{
					min = cost[i, j];
					a = i;
					b = j;
				}
			}
		}

		union1(a, b);
		Console.Write("Edge {0}:({1}, {2}) cost:{3} \n",
			edge_count++, a, b, min);
		mincost += min;
	}
	Console.Write("\n Minimum cost= {0} \n", mincost);
}

public static void Main(String[] args)
{
    /* 
          2    3
      (0)--(1)--(2)
       |   / \   |
      6| 8/   \5 |7
       | /     \ |
      (3)-------(4)
            9          */
	int [,]cost = {
		{ INF, 2, INF, 6, INF },    //bod 0 {cesta k 0, cesta k 1, cesta k 2} pokud neni cesta je to inf
		{ 2, INF, 3, 8, 5 },        //bod 1
		{ INF, 3, INF, INF, 7 },    //bod 2
		{ 6, 8, INF, INF, 9 },      //bod 3
		{ INF, 5, 7, 9, INF },      //bod 4  
	};

    // vypsat reseni

	kruskalMST(cost);
}
}

