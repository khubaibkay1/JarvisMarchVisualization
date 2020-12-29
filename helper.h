#ifndef HELPERS
#define HELPERS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <cairo.h>
typedef struct point
{
    int x;
    int y;
} point;
int randomcoord(int minimum, int maximum);
void makepoints(point arr[], cairo_t *context, int points);
double r2();
void makeline(point, point, cairo_t * context,int white);
int find_left_most(struct point *points, int num_points);
int is_same(point p1, point p2);
double crossproduct(point,point,point);
double distance(point,point,point);
void copy_state(cairo_surface_t* src, cairo_t* dest);
void makeimagefromsurface(int* imagenum,cairo_surface_t* surface);
void copysurfacetocontext(cairo_t* destination, cairo_surface_t* surface);
#endif