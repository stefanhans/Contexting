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
        ciBricks(QVector<CI_Brick>(1)) {}

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
     * Is equal to another ciBrick
     */
    bool ciBricksAreEqual(const QVector<CI_Brick> &value);

    /*
     * Path functions
     */
    QString getFullPath() const;
    QString getRoutingPath() const;

    /*
     * Context functions
     */
    QString getContextRoute() ;

    /*
     * Validate
     */
    bool validate();

private:

    quint8 ciType;
    CI_Brick rootCIC;
    quint8 ciSize;
    QVector<CI_Brick> ciBricks;
};

#endif // CI_H
