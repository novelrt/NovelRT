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

        T getX() const;

        void setX(T value);

        T getY() const;

        void setY(T value);


        inline GeoVector<T> operator + (const GeoVector<T>& other) const;

        inline GeoVector<T> operator * (const GeoVector<T>& other) const;

        inline GeoVector<T> operator - (const GeoVector<T>& other) const;

        inline GeoVector<T> operator / (const GeoVector<T>& other) const;

        inline GeoVector<T> operator + (const float& other) const;

        inline GeoVector<T> operator * (const float& other) const;

        inline GeoVector<T> operator - (const float& other) const;

        inline GeoVector<T> operator / (const float& other) const;


    private:
        T _x;
        T _y;
    };

    template<typename T>
    GeoVector<T>::GeoVector(T x, T y) {
        _x = x;
        _y = y;
    }

    template<typename T>
    T GeoVector<T>::getX() const {
        return _x;
    }

    template<typename T>
    void GeoVector<T>::setX(T value) {
        GeoVector::_x = value;
    }

    template<typename T>
    T GeoVector<T>::getY() const {
        return _y;
    }

    template<typename T>
    void GeoVector<T>::setY(T value) {
        GeoVector::_y = value;
    }

    template<typename T>
    inline GeoVector<T> GeoVector<T>::operator + (const GeoVector<T>& other) const {
        return GeoVector<T>(GeoVector<T>::getX() + other.getX(), GeoVector<T>::getY() + other.getY());
    }

    template<typename T>
    inline GeoVector<T> GeoVector<T>::operator * (const GeoVector<T>& other) const {
        return GeoVector<T>(GeoVector<T>::getX() * other.getX(), GeoVector<T>::getY() * other.getY());
    }

    template<typename T>
    inline GeoVector<T> GeoVector<T>::operator - (const GeoVector<T>& other) const {
        return GeoVector<T>(GeoVector<T>::getX() - other.getX(), GeoVector<T>::getY() - other.getY());
    }
    template<typename T>
    inline GeoVector<T> GeoVector<T>::operator + (const float& other) const {
        return GeoVector<T>(GeoVector<T>::getX() + other, GeoVector<T>::getY() + other);
    }

    template<typename T>
    inline GeoVector<T> GeoVector<T>::operator * (const float& other) const {
        return GeoVector<T>(GeoVector<T>::getX() * other, GeoVector<T>::getY() * other);
    }

    template<typename T>
    inline GeoVector<T> GeoVector<T>::operator - (const float& other) const {
        return GeoVector<T>(GeoVector<T>::getX() - other, GeoVector<T>::getY() - other);
    }

    template<typename T>
    GeoVector<T> GeoVector<T>::operator / (const GeoVector<T> &other) const {
        return GeoVector<T>(GeoVector<T>::getX() / other, GeoVector<T>::getY() / other);
    }

    template<typename T>
    GeoVector<T> GeoVector<T>::operator / (const float &other) const {
        return GeoVector<T>(GeoVector<T>::getX() / other, GeoVector<T>::getY() / other);
    }
}

#endif //NOVELRT_COORDINATEVECTOR_H
