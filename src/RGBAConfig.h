//
// Created by matth on 16/12/2018.
//

#ifndef NOVELRT_RGBACONFIG_H
#define NOVELRT_RGBACONFIG_H

namespace NovelRT {
    class RGBAConfig {
    public:
        RGBAConfig(int r, int g, int b, int a);

        int getR() const;

        void setR(int value);

        int getG() const;

        void setG(int value);

        int getB() const;

        void setB(int value);

        int getA() const;

        void setA(int value);

    private:
        int _r;
        int _g;
        int _b;
        int _a;

    };
}


#endif //NOVELRT_RGBACONFIG_H
