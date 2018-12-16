//
// Created by matth on 15/12/2018.
//

#ifndef NOVELRT_COORDINATEVECTOR_H
#define NOVELRT_COORDINATEVECTOR_H
#include<memory>

namespace NovelRT {
    template<typename T>
    class GeoVector {
    public:
        GeoVector(T x, T y);

        T getX();

        void setX(T value);

        T getY();

        void setY(T value);


        inline GeoVector<T> operator + (const GeoVector<T>& other) const;

        inline GeoVector<T> operator * (const GeoVector<T>& other) const;

        inline GeoVector<T> operator - (const GeoVector<T>& other) const;


    private:
        T _x;
        T _y;
    };
}

#endif //NOVELRT_COORDINATEVECTOR_H
