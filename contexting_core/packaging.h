#ifndef PACKAGING_H
#define PACKAGING_H

#include "cip.h"

#include <QVector>


class Packaging {

public:

    Packaging() :
    packets() {}

    ~Packaging() {}

    void add(const QByteArray &packet);

private:

    QVector<QByteArray> packets;
};

#endif // PACKAGING_H
