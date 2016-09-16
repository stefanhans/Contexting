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
        return out;
    }

    for (int i = index; i < index+length; i++) {
        out.append(ciBrickArray[i]);
    }
    return out;
}

void CI::setCiBricks(const QVector<CI_Brick> &value, quint8 index)
{

    int size = value.size() + index;

    if(size > 255) {
       ciSize = 255;
    }
    else {
        ciSize = size;
    }

    for(int i=0; i<value.size(); i++) {
        ciBrickArray[index++] = value.at(i);
    }
}

void CI::setCiBricks(const QByteArray &value)
{
    ciSize = value.size()/2;

    for(int i=0; i<ciSize; i++) {
        ciBrickArray[i] = CI_Brick(value.at(i*2), value.at(i*2+1));
    }
}


/*
 * Context functions
 */
QString CI::getContextContent() const
{
    QString out;

    for (int i=0; i<ciSize; i++) {

        out += ((CI_Brick) ciBrickArray[i]).contentToHex();
    }
    return out;
}

QString CI::getContextRoute() const
{

    QString out;

    for (int i=0; i<ciSize; i++) {

        out += ((CI_Brick) ciBrickArray[i]).contextToRoute();

        if(((CI_Brick) ciBrickArray[i]).getMask() != 0) {

            return out;
        }
    }
    return out;
}


/*
 * Path functions
 */
QString CI::getFullPath(const QChar delim) const
{
    return hexToPath(getContextContent(), delim);

}

QString CI::getRoutingPath(const QChar delim) const
{
    return hexToPath(getContextRoute(), delim);
}


bool CI::match(const QVector<CI_Brick> &otherBricks) const
{
    if(ciSize != otherBricks.size()) {
        return false;
    }
    for (int i =0; i<ciSize; i++) {
        if( ! ciBrickArray[i].contextMatch(otherBricks.at(i))) {
            return false;
        }
    }
    return true;
}


/*
 * Private String Functions
 */
QString CI::hexToPath(const QString hex, QChar delim) const
{
    QString out;

    for (int i=0; i<hex.size(); i++) {
        out += hex.at(i) + QString(delim);
    }
    return out;
}

