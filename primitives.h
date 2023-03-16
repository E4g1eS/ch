#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <string>
#include <sstream>

namespace Chess
{


    enum class Color
    {
        White,
        Black
    };

    struct Vector2
    {
        int m_x;
        int m_y;

        Vector2()
            : m_x(0), m_y(0){};

        Vector2(int x, int y)
            : m_x(x), m_y(y){};

        Vector2(std::string s)
        {
            if (s.length() != 2) return;

            m_x = (int)(s[0]) - 'a';
            m_y = (int)(s[1]) - '1';
        }

        Vector2 operator+=(const Vector2 &add)
        {
            m_x += add.m_x;
            m_y += add.m_y;

            return *this;
        }

        Vector2 operator+(const Vector2 &add)
        {
            (*this) += add;

            return *this;
        }

        std::string toString()
        {
            std::string str;

            std::stringstream ss("");

            ss << "(" << m_x << "," << m_y << ") == '" << (m_x + 97) << (m_y + 49) << "'";
            ss >> str;

            return str;
        }
    };
}

#endif