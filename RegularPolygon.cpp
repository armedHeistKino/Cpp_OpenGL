#ifndef __REGULAR_POLYGON__
#define __REGULAR_POLYGON__

#include <cmath>

class RegularPolygon {
public:
    RegularPolygon(int division = 3, double radius = 0.50) {
        _division = division;
        _radius = radius;

        // set up vertices array 
        vert = new float[_division * 18];

        for(int i= 0; i < _division; i++) {
            // position
            vert[18*i + 0] = 0.0f;
            vert[18*i + 1] = 0.0f;
            vert[18*i + 2] = 0.0f;

            vert[18*i + 6] = _radius * cos(360/(float)_division * i * 3.14/(float)180);
            vert[18*i + 7] = _radius * sin(360/(float)_division * i * 3.14/(float)180);
            vert[18*i + 8] = 0.0f;

            vert[18*i + 12] = _radius * cos(360/(float)_division * (i+1) * 3.14/(float)180);
            vert[18*i + 13] = _radius * sin(360/(float)_division * (i+1) * 3.14/(float)180);
            vert[18*i + 14] = 0.0f;

            // color
            for (int j = 0; j < 3; j++) {
                if (j % 6 == 3) {
                    vert[18*i + 3 + 6*j] = _r;
                }
                else if (j % 6 == 4) {
                    vert[18*i + 4 + 6*j] = _g;
                }
                else if (j % 6 == 5) {
                    vert[18*i + 5 + 6*j] = _b;
                }
            }
        }

        // Default Color
        _r = 1.0f; _g = 1.0f; _b = 1.0f;
    }

    void setColor(double r, double g, double b) {
        _r = r; _g = g; _b = b;
    }

    ~RegularPolygon() {
        delete[] vert;
    }

    float* vertices() const {
        return vert;
    }

private:
    int _division;
    int _radius;

    float* vert;

    double _r;
    double _g;
    double _b;
};

#endif