#include "ci.h"

#include <QDebug>

quint8 CI::getCiType() const
{
    return ciType;
}

void CI::setCiType(const quint8 &value)
{
    ciType = value;
}

CI_Brick CI::getRootCIC() const
{
    return rootCIC;
}

void CI::setRootCIC(const CI_Brick &value)
{
    rootCIC = value;
}


void CI::setRootCicContent(const quint8 &value) {
    rootCIC.setContent(value);
}

void CI::setRootCicMask(const quint8 &value) {
    rootCIC.setMask(value);
}


quint8 CI::getRootCicContent() const {
    return rootCIC.getContent();
}
quint8 CI::getRootCicMask() const {
    return rootCIC.getMask();
}

quint8 CI::getCiSize() const
{
    return ciSize;
}

void CI::setCiSize(const quint8 &value)
{
    ciSize = value;
}

const QVector<CI_Brick> CI::getCiBricks() const
{
    return ciBricks;
}

void CI::setCiBricks(const QVector<CI_Brick> &value)
{
    ciBricks = value;
}


const QVector<CI_Brick> CI::getCiBricks(quint8 index, quint8 length) const
{
    return ciBricks.mid(index, length);
}

void CI::setCiBricks(const QVector<CI_Brick> &value, quint8 index)
{
    for(int i=0; i<value.size(); i++) {
        ciBricks.insert(index++, value.at(i));
    }
}

void CI::appendCiBricks(const QVector<CI_Brick> &value) {

    setCiBricks(value, ciBricks.size());
}


void CI::resizeCiBricks()
{
    ciBricks.resize(ciSize);
}

bool CI::ciBricksAreEqual(const QVector<CI_Brick> &value)
{
    if ( ciBricks.size() != value.size() ) return false;

    for (int i=0; i<ciBricks.size(); i++) {
        if(ciBricks.at(i).getContent() != value.at(i).getContent()) return false;
        if(ciBricks.at(i).getMask() != value.at(i).getMask()) return false;
    }
    return true;
}



CI_Brick CI::getCiBrick(quint8 index) const
{
    return (CI_Brick) ciBricks.at(index);
}


void CI::setCiBrick(const CI_Brick &value, quint8 index)
{
    ciBricks.replace(index, value);
}

quint8 CI::getCiBrickContent(quint8 index)
{
    return ciBricks[index].getContent();
}

void CI::setCiBrickContent(const quint8 content, quint8 index)
{
    ciBricks[index].setContent(content);
}

quint8 CI::getCiBrickMask(quint8 index)
{
    return ciBricks[index].getMask();
}

void CI::setCiBrickMask(const quint8 mask, quint8 index)
{
    ciBricks[index].setMask(mask);
}





/*
 * Path functions
 */
QString CI::getFullPath()
{
    QString out = "./";

    for (int i=0; i<ciBricks.size(); i++) {

        out += ((CI_Brick) ciBricks.at(i)).contentToPath() + '/';
    }

    return out;
}

QString CI::getRoutingPath() const
{
    QString out = "./";

    for (int i=0; i<ciBricks.size(); i++) {

        out += ((CI_Brick) ciBricks.at(i)).contextToRoute() + '/';
    }

    return out;
}

/*
 * Context functions
 */
QString CI::getContextRoute() {

    QString out;

    for (int i=0; i<ciBricks.size(); i++) {

        out += ((CI_Brick) ciBricks.at(i)).contextToRoute();
    }

    return out;
}

QString CI::getContextSearch() {

    QString out;

    for (int i=0; i<ciBricks.size(); i++) {

        out += ((CI_Brick) ciBricks.at(i)).contextToSearch();
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

