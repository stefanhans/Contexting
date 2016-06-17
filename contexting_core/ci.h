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

    quint8 getRootCicContent() const;
    void setRootCicContent(const quint8 &value);

    quint8 getRootCicMask() const;
    void setRootCicMask(const quint8 &value);


    /*
     * CI SIZE
     */
    quint8 getCiSize() const;
    void setCiSize(const quint8 &value);


    /*
     * CI BRICKS
     */
    const QVector<CI_Brick> getCiBricks() const;
    void setCiBricks(const QVector<CI_Brick> &value);

    const QVector<CI_Brick> getCiBricks(quint8 index, quint8 length) const;
    void setCiBricks(const QVector<CI_Brick> &value, quint8 index);

    void appendCiBricks(const QVector<CI_Brick> &value);


    /*
     * Resize CI_Bricks according to ciSize
     */
    void resizeCiBricks();

    bool ciBricksAreEqual(const QVector<CI_Brick> &value);

    CI_Brick getCiBrick(quint8 index) const;
    void setCiBrick(const CI_Brick &value, quint8 index);

    quint8 getCiBrickContent(quint8 index);
    void setCiBrickContent(const quint8 content, quint8 index);

    quint8 getCiBrickMask(quint8 index);
    void setCiBrickMask(const quint8 mask, quint8 index);

private:

    quint8 ciType;
    CI_Brick rootCIC;
    quint8 ciSize;
    QVector<CI_Brick> CI_Bricks;
};

#endif // CI_H
