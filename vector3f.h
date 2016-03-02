#ifndef VECTOR3F_H
#define VECTOR3F_H

#include <cmath>

/**
 * @brief The Vector3f class
 */
class Vector3f
{
    float x, y, z; //coordenadas x, y e v do vetor
public:
    Vector3f(float x = 0, float y = 0, float z = 0); //construtor geral
    Vector3f(const Vector3f &copy); //construtor por cópia
    Vector3f mult(float scale) const; //produto escalar: multiplica o vetor por um escalar e retorna o resultado
    Vector3f mult(const Vector3f v) const; //multiplica o vetor por outro, componente por componente.
    float dot(const Vector3f &v) const; //produto interno
    Vector3f operator  +(const Vector3f &v) const; //soma vetorial
    Vector3f operator  -(const Vector3f &v) const; //subtração vetorial
    Vector3f operator *(const Vector3f &v) const; //produto vetorial
    bool operator ==(const Vector3f &v) const; //testa se dois vetores no espaço são iguais
    Vector3f& operator=(const Vector3f &v); //atribui - copia os valores - de um vetor v para o vetor atribuído.

    Vector3f project(const Vector3f &v) const;

    float operator [](char x) const; //retorna um componente do vetor

    float lenght() const ;
    float lenght2() const ;

    Vector3f normalize() const;

    float X() const; //retorna a coordenada x do vetor
    float Y() const; //retorna a coordenada y do vetor
    float Z() const; //retorna a coordenada z do vetor
};

#endif // VECTOR3F_H
