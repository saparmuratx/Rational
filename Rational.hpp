#pragma once

#include <cctype>
#include <iosfwd>
#include <iostream>
#include <stdexcept>

template <typename T>
class Rational {
    T mNum;
    T mDen;

    void reduce(T &num, T &den) {
        T g = gcd(abs(num), abs(den));
        num /= g;
        den /= g;

        if (den < 0) {
            den = -den;
            num = -num;
            if (num == 0) {
                den = 1;
            }
        }
    }

    T gcd(T a, T b) { return b == 0 ? a : gcd(b, a % b); }

   public:
    Rational() : mNum(0), mDen(1) {}

    Rational(const T &num, const T &den) : mNum(num), mDen(den) {
        if (mDen == 0) {
            throw std::runtime_error("Rational: denominator can't be 0!");
        }

        reduce(mNum, mDen);
    }

    const T &num() const { return mNum; }
    const T &den() const { return mDen; }
};

template <typename T>
Rational<T> operator+(const Rational<T> &r1, const Rational<T> &r2) {
    T num = r2.den() * r1.num() + r1.den() * r2.num();
    T den = r1.den() * r2.den();

    return Rational<T>(num, den);
}

template <typename T>
Rational<T> operator-(const Rational<T> &r1, const Rational<T> &r2) {
    T num = r2.den() * r1.num() - r1.den() * r2.num();
    T den = r1.den() * r2.den();

    return Rational<T>(num, den);
}

template <typename T>
Rational<T> operator*(const Rational<T> &r1, const Rational<T> &r2) {
    T num = r1.num() * r2.num();
    T den = r1.den() * r2.den();

    return Rational<T>(num, den);
}

template <typename T>
Rational<T> operator/(const Rational<T> &r1, const Rational<T> &r2) {
    if (r2.num() == 0) {
        throw std::runtime_error("Rational: can't divide by 0 (0/1)!");
    }

    T num = r1.num() * r2.den();
    T den = r1.den() * r2.num();

    return Rational<T>(num, den);
}

template <typename T>
bool operator<(const Rational<T> &r1, const Rational<T> &r2) {
    return r1.num() * r2.den() < r2.num() * r1.den();
}

template <typename T>
bool operator>(const Rational<T> &r1, const Rational<T> &r2) {
    return r2 < r1;
}

template <typename T>
bool operator==(const Rational<T> &r1, const Rational<T> &r2) {
    return r1.num() * r2.den() == r2.num() * r1.den();
}

template <typename T>
bool operator!=(const Rational<T> &r1, const Rational<T> &r2) {
    return !(r1 == r2);
}

template <typename T>
bool operator<=(const Rational<T> &r1, const Rational<T> &r2) {
    return !(r1 > r2);
}

template <typename T>
bool operator>=(const Rational<T> &r1, const Rational<T> &r2) {
    return !(r1 < r2);
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const Rational<T> &r) {
    out << r.num() << "/" << r.den();
    return out;
}

template <typename T>
std::istream &operator>>(std::istream &in, Rational<T> &r) {
    T num, den;
    char ch;

    if (!(in >> num)) return in;

    if (!in.get(ch)) return in;

    if (ch != '/') {
        in.setstate(std::ios_base::failbit);
        return in;
    }

    if (!in.get(ch)) return in;

    if (ch != '+' && ch != '-' && !isdigit(ch)) {
        in.setstate(std::ios_base::failbit);
        return in;
    }
    in.putback(ch);

    if (!(in >> den)) return in;
    r = Rational<T>(num, den);
    return in;
}