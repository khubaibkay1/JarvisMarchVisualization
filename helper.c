#include "helper.h"

int randomcoord(int minimum, int maximum)
{
    // generate random number within a range. [min,max)
    return minimum + rand() % (maximum - minimum);
}

void makepoints(point arr[], cairo_t *context, int points)
{
    // generate all points randomly and draw them within the context and save
    // in array
    for (int i = 0; i < points; ++i)
    {
        int x = randomcoord(100, 1800);
        int y = randomcoord(100, 1000);
        arr[i].x = x;
        arr[i].y = y;
        // random color
        cairo_set_source_rgba(context, r2(), r2(), r2(), 0.6);
        cairo_arc(context, x, y, 10.0, 0, 2 * M_PI);
        cairo_fill(context);
    }
}

double r2()
{
    // return random number from 0 to 1
    return (double)(rand() % 10001) / 10000.0;
}
void makeline(point p1, point p2, cairo_t *context, int white)
{
    // set color to blue
    cairo_set_source_rgb(context, 0, 0, 1.0);
    // change color to white if white is 1
    if (white == 1)
    {
        cairo_set_source_rgb(context, 1.0, 1.0, 1.0);
    }
    cairo_move_to(context, p1.x, p1.y);
    // draw line
    cairo_line_to(context, p2.x, p2.y);
    cairo_set_line_width(context, 5);
    cairo_stroke(context);
}

int find_left_most(struct point *points, int num_points)
{
    point left = points[0];
    int index = 0;

    for (int i = 0; i < num_points; ++i)
    {
        if (points[i].x < left.x)
        {
            left = points[i];
            index = i;
        }
        else if (points[i].x == left.x)
        {
            if (points[i].y < left.y)
            {
                left = points[i];
                index = i;
            }
        }
    }

    return index;
}

int is_same(point p1, point p2)
{
    return p1.x == p2.x && p2.y == p1.y;
}

double distance(point a, point b, point c)
{
    int y1 = a.y - b.y;
    int y2 = a.y - c.y;
    int x1 = a.x - b.x;
    int x2 = a.x - c.x;
    double dist = x1 * x1 + y1 * y1 - x2 * x2 + y2 * y2;
    return -dist;
}
double crossproduct(point a, point b, point c)
{
    int y1 = a.y - b.y;
    int y2 = a.y - c.y;
    int x1 = a.x - b.x;
    int x2 = a.x - c.x;
    return y2 * x1 - y1 * x2;
}

void copy_state(cairo_surface_t *src, cairo_t *dest)
{
    cairo_set_source_surface(dest, src, 0, 0);
    cairo_fill(dest);
}

void makeimagefromsurface(int *imagenum, cairo_surface_t *surface)
{
    char str[50];
    sprintf(str, "./images/image%05d.png", *imagenum);
    ++(*imagenum);
    cairo_surface_write_to_png(surface, str);
}

void copysurfacetocontext(cairo_t *destination, cairo_surface_t *surface)
{
    cairo_set_source_surface(destination, surface, 0, 0);
    cairo_paint(destination);
}