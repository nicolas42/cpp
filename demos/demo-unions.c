#include <stdio.h>
#include <string.h>

#define PI 3.14159

typedef enum shape_type_t { CIRCLE, RECTANGLE } shape_type_t;

typedef struct shape_t { 
    shape_type_t type;
    union { double radius; double width; };
    double height;
} shape_t;

typedef struct rectangle_t { shape_type_t type; double width; double height; } rectangle_t;

int main( ) {

    #define shapes_length 2
    shape_t shapes[shapes_length] = { 
        { .type = RECTANGLE, .width = 2, .height = 3 },
        { .type = CIRCLE, .radius = 3 }
    };

    for (size_t i = 0; i < shapes_length; i++)
    {
        double r,w,h;

        switch (shapes[i].type)
        {
        case CIRCLE:
            r = shapes[i].radius;
            printf("circle :). radius: %f, area: %f\n", r, PI*r*r);
            break;
        case RECTANGLE:
            w = shapes[i].width; h = shapes[i].height;
            printf("rectangle :). width: %f, height: %f, area: %f\n", w, h, w*h);
            break;        
        default:
            break;
        }
    }
        

   return 0;
}