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
        ciBrickArray() {}

    /*
     * ciType
     */
    quint8 getCiType() const;
    void setCiType(const quint8 &value);


    /*
     * rootCIC
     */
    CI_Brick getRootCIC() const;
    void setRootCIC(const CI_Brick &value);

    quint8 getRootCicContent() const;
    void setRootCicContent(const quint8 &value);

    quint8 getRootCicMask() const;
    void setRootCicMask(const quint8 &value);


    /*
     * ciSize
     */
    quint8 getCiSize() const;
    void setCiSize(const quint8 &value);


    /*
     * ciBricks complete
     */
    const QVector<CI_Brick> getCiBricks(quint8 index=0, quint8 length=0) const;
    void setCiBricks(const QVector<CI_Brick> &value, quint8 index=0);

    /*
     * Context functions
     */
    QString getContextContent() const;
    QString getContextRoute() const;

    /*
     * Path functions
     */
    QString getFullPath(const QChar delim='/') const;
    QString getRoutingPath(const QChar delim='/') const;

private:

    quint8 ciType;
    CI_Brick rootCIC;
    quint8 ciSize;
    CI_Brick ciBrickArray[255];

    QString hexToPath(const QString hex, QChar delim) const;
};

#endif // CI_H
