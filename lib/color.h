#include <stdio.h>
#include <stdlib.h>

unsigned long _RGB(int r,int g, int b)
{
    return b + (g<<8) + (r<<16);
}
