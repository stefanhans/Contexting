#include "ci.h"

#include <QDebug>


/*
 * ciType
 */
quint8 CI::getCiType() const
{
    return ciType;
}

void CI::setCiType(const quint8 &value)
{
    ciType = value;
}


/*
 * rootCIC
 */
CI_Brick CI::getRootCIC() const
{
    return rootCIC;
}

void CI::setRootCIC(const CI_Brick &value)
{
    rootCIC = value;
}

quint8 CI::getRootCicContent() const
{
    return rootCIC.getContent();
}

void CI::setRootCicContent(const quint8 &value)
{
    rootCIC.setContent(value);
}

quint8 CI::getRootCicMask() const
{
    return rootCIC.getMask();
}

void CI::setRootCicMask(const quint8 &value)
{
    rootCIC.setMask(value);
}


/*
 * ciSize
 */
quint8 CI::getCiSize() const
{
    return ciSize;
}

void CI::setCiSize(const quint8 &value)
{
    ciSize = value;
}


/*
 * ciBricks
 */
const QVector<CI_Brick> CI::getCiBricks(quint8 index, quint8 length) const
{
    QVector<CI_Brick> out;

    if(length == 0) {
        for (int i = index; i < ciSize-index; i++) {
            out.append(ciBrickArray[i]);
        }
    }

    for (int i = index; i < length; i++) {
        out.append(ciBrickArray[i]);
    }
    return out;
}

void CI::setCiBricks(const QVector<CI_Brick> &value, quint8 index)
{
    for(int i=0; i<value.size(); i++) {
        ciBrickArray[index++] = value.at(i);
    }
    ciSize = value.size() + index;
}


/*
 * Path functions
 */
QString CI::getFullPath(const QChar delim) const
{
    QString out;

    qDebug() << "ciSize: " << ciSize;

    for (int i=0; i<ciSize; i++) {

        out += ((CI_Brick) ciBrickArray[i]).contentToPath();

        if(i < (ciSize-1)) {
            out += delim;
        }
    }
    return out;
}

QString CI::getRoutingPath(const QChar delim) const
{
    QString out;

    for (int i=0; i<ciSize; i++) {

        out += ((CI_Brick) ciBrickArray[i]).contextToRoutePath();

        if(i < (ciSize-1)) {
            out += delim;
        }
    }
    return out;
}

/*
 * Context functions
 */
QString CI::getContextRoute()
{

    QString out;

    for (int i=0; i<ciSize; i++) {

        out += ((CI_Brick) ciBrickArray[i]).contextToRoute();
    }
    return out;
}

