#ifndef CI_H
#define CI_H

#include "ci_brick.h"

#include <QVector>

class CI {

public:

    CI() :
        ciType(0),
        rootCIC(),
        ciSize(0),
        CI_Bricks(QVector<CI_Brick>(1)) {}

    quint8 getCiType() const;
    void setCiType(const quint8 &value);

    /*
     * CI ROOT CIC
     */
    CI_Brick getRootCIC() const;
    void setRootCIC(const CI_Brick &value);
    void setRootCicContent(const quint8 &value);
    void setRootCicMask(const quint8 &value);
    quint8 getRootCicContent() const;
    quint8 getRootCicMask() const;


    /*
     * CI SIZE
     */
    quint8 getCiSize() const;
    void setCiSize(const quint8 &value);


    /*
     * CI CIC BRICKS
     */
    QVector<CI_Brick> getCI_Bricks() const;
    CI_Brick getCI_Bricks(quint8 index) const;
    void setCI_Bricks(const QVector<CI_Brick> &value);
    void setCI_Bricks(const QByteArray &value);
    void setCI_Brick(const CI_Brick &value, quint8 index);
    void setCI_BrickContent(const quint8 &value, quint8 index);
    void setCI_BrickMask(const quint8 &value, quint8 index);
    void truncateCI_Bricks(quint8 size);

private:

    quint8 ciType;
    CI_Brick rootCIC;
    quint8 ciSize;
    QVector<CI_Brick> CI_Bricks;
};

#endif // CI_H
