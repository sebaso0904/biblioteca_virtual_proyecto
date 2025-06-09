//richard prado
#ifndef STATE_H
#define STATE_H

#include <iostream>
using namespace std;

class Libro; // Forward declaration

class Estado {
public:
    virtual void devolver(Libro* libro) = 0;
    virtual ~Estado() {}
};

class Disponible : public Estado {
public:
    void devolver(Libro* libro) override;
};

class Agotado : public Estado {
public:
    void devolver(Libro* libro) override;
};

#endif
