#include <cairo.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "helper.h"
void jarvis(cairo_t *cr, cairo_surface_t *surface, point points[], point hullpoints[], int *hullpoint_num, int numpoints);

int main(int argc, char *argv[])
{
    // Initialize random seed
    srand(time(0));
    // make surface
    cairo_surface_t *surface =
        cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 1920, 1080);
    cairo_t *cr =
        cairo_create(surface);
    // file surface with pure black
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairo_paint(cr);

    // set number of points
    int n = 20;
    point points[n];
    point hullpoints[n];
    int hullpointsnum = 0;
    // generate all the points
    makepoints(points, cr, n);
    jarvis(cr, surface, points, hullpoints, &hullpointsnum, n);
    
    // delete context and surface
    
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
    return 0;
}

void jarvis(cairo_t *cr, cairo_surface_t *surface, point points[], point hullpoints[], int *hullpoint_num, int numpoints)
{

    // set image number to 0 and initialization
    int imgnum = 0;
    cairo_surface_t *destination =
        cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 1920, 1080);
    cairo_t *destcontext =
        cairo_create(destination);
    for (int x = 0; x < 15; ++x)
    {
        makeimagefromsurface(&imgnum, surface);
    }

    // find left most point
    int left_index = find_left_most(points, numpoints);
    point pointonhull = points[left_index];
    point endpoint;
    int endpoint_index;
    // i: number of elements in hull
    int i = 0;
    do
    {
        // put element in hull
        hullpoints[i] = pointonhull;
        // initialize end point
        endpoint = points[0];
        endpoint_index = 0;
        // save current image is destcontext.
        copysurfacetocontext(destcontext, surface);
        // find ideal endpoint
        for (int j = 0; j < numpoints; j++)
        {
            // draw a line and make an image
            makeline(pointonhull, points[j], cr, 1);
            makeimagefromsurface(&imgnum, surface);
            // if point is better, change endpoint
            if ((is_same(endpoint, pointonhull) == 1) || crossproduct(pointonhull, endpoint, points[j]) < 0)
            {
                endpoint = points[j];
                endpoint_index = j;
            }
            // revert to image before line drawn
            copysurfacetocontext(cr, destination);
        }
        // draw the correctline
        makeline(endpoint, pointonhull, cr, 0);
        makeimagefromsurface(&imgnum, surface);
        i++;
        pointonhull = endpoint;

    } while (endpoint_index != left_index); // unitl hull closed
    // draw last line and keep it for 15 frames
    makeline(hullpoints[0], hullpoints[i - 1], cr, 0);
    for (int x = 0; x < 15; ++x)
    {
        makeimagefromsurface(&imgnum, surface);
    }
    *hullpoint_num = i;
    // delete context and surface
    cairo_destroy(destcontext);
    cairo_surface_destroy(destination);
}