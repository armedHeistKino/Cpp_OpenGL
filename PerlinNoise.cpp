#include <iostream>
#include <vector>

#include <algorithm>
#include <random>

class PerlinNoise {
public:
    unsigned int mask;
    std::vector<int> hashPermutation;
    int* p;
    
    PerlinNoise(unsigned int mask = 256) {
        for (int i = 0; i < mask; i++) { hashPermutation.push_back(i); }

        auto rng = std::default_random_engine {};
        std::shuffle(hashPermutation.begin(), hashPermutation.end(), rng);
        
        p = new int[mask];
        for (int i = 0; i < mask; i++) { p[i] = hashPermutation.at(i); }

    }
    ~PerlinNoise() {
        delete[] p;
    }

    double noise(double x, double y, double z) {
        int X = (int)floor(x) & mask;
        int Y = (int)floor(y) & mask;
        int Z = (int)floor(z) & mask;

        x = x - int(x);
        y = y - int(y);
        z = z - int(z);

        double u = fade(x);
        double v = fade(y);
        double w = fade(z);

        // Hash code for each unit square's corner:
        int h000 = p[p[p[  X]+  Y]+  Z];
        int h100 = p[p[p[X+1]+  Y]+  Z];
        int h010 = p[p[p[  X]+Y+1]+  Z];
        int h001 = p[p[p[  X]+  Y]+Z+1];
        int h110 = p[p[p[X+1]+Y+1]+  Z];
        int h101 = p[p[p[X+1]+  Y]+Z+1];
        int h011 = p[p[p[  X]+Y+1]+Z+1];
        int h111 = p[p[p[X+1]+Y+1]+Z+1];

        double x1, x2, y1, y2;

        x1 = lerp(gradientDot(h000, x, y, z), gradientDot(h100, x-1, y, z), u);
        x2 = lerp(gradientDot(h010, x, y-1, z), gradientDot(h110, x-1, y-1, z), u);
        y1 = lerp(x1, x2, v);

        x1 = lerp(gradientDot(h001, x, y, z-1), gradientDot(h101, x-1, y, z-1), u);
        x2 = lerp(gradientDot(h011, x, y-1, z-1), gradientDot(h111, x-1, y-1, z-1), u);
        y2 = lerp(x1, x2, v);

        return (lerp(y1, y2, w) + 1.0) / 2.0;
    }

private:
    double fade(double t) { return t * t * t * (t * (t * 6 - 15) + 10); }
    double gradientDot(int hash, double x, double y, double z) {
        switch(hash & 0xF) {
            case 0x0: return  x + y;
            case 0x1: return -x + y;
            case 0x2: return  x - y;
            case 0x3: return -x - y;
            case 0x4: return  x + z;
            case 0x5: return -x + z;
            case 0x6: return  x - z;
            case 0x7: return -x - z;
            case 0x8: return  y + z;
            case 0x9: return -y + z;
            case 0xA: return  y - z;
            case 0xB: return -y - z;
            case 0xC: return  y + x;
            case 0xD: return -y + z;
            case 0xE: return  y - x;
            case 0xF: return -y - z;
        }
    }
    double lerp(double a, double b, double t) { return a + t*(b-a); }
};