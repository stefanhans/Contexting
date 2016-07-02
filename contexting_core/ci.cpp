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
    if(length == 0) {
        return ciBricks.mid(index, ciSize);
    }
    return ciBricks.mid(index, length);
}

void CI::setCiBricks(const QVector<CI_Brick> &value, quint8 index)
{
//    qDebug() << QString("CI::setCiBricks(%1, quint8 index)").arg(value.size());
    for(int i=0; i<value.size(); i++) {
//        qDebug() << QString("%1: ciBricks.insert(%2, %3 | %4)").arg(i).arg(index).arg(((CI_Brick) value.at(i)).getContent()).arg(((CI_Brick) value.at(i)).getMask());
        ciBricks.insert(index++, value.at(i));
    }
}

bool CI::ciBricksAreEqual(const QVector<CI_Brick> &value)
{
    for (int i=0; i<value.size(); i++) {

//        qDebug() << QString("%1: ciBricks.at(i).getContent(): %2 - %3").arg(i).arg(ciBricks.at(i).getContent()).arg(value.at(i).getContent());
//        qDebug() << QString("%1: ciBricks.at(i).getMask(): %2 - %3").arg(i).arg(ciBricks.at(i).getMask()).arg(value.at(i).getMask());

        if(ciBricks.at(i).getContent() != value.at(i).getContent()) return false;
        if(ciBricks.at(i).getMask() != value.at(i).getMask()) return false;
    }
    return true;
}



/*
 * Path functions
 */
QString CI::getFullPath() const
{
    QString out;

    for (int i=0; i<ciBricks.size(); i++) {

        out += ((CI_Brick) ciBricks.at(i)).contentToPath();

        if(i < (ciBricks.size()-1)) {
            out += '/';
        }
    }

    return out;
}

QString CI::getRoutingPath() const
{
    QString out;

    for (int i=0; i<ciBricks.size(); i++) {

        out += ((CI_Brick) ciBricks.at(i)).contextToRoutePath();

        if(i < (ciBricks.size()-1)) {
            out += '/';
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

    for (int i=0; i<ciBricks.size(); i++) {

        out += ((CI_Brick) ciBricks.at(i)).contextToRoute();
    }

    return out;
}


/*
 * Validate
 */
bool CI::validate()
{
    return ciBricks.size() == ciSize;
}

