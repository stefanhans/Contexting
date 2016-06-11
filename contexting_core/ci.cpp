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

void CI::resizeCiBricks()
{
    CI_Bricks.resize(ciSize);
}



const QVector<CI_Brick> CI::getCiBricks() const
{
    return CI_Bricks;
}

CI_Brick CI::getCiBricks(quint8 index) const
{
    return (CI_Brick) CI_Bricks.at(index);
}

void CI::setCiBricks(const QVector<CI_Brick> &value)
{
    CI_Bricks = value;
}


void CI::setCiBricks(const QVector<CI_Brick> &value, quint8 index)
{
    for (int i=index, j=0; i<index+value.size(); i++, j++) {

        if(i < CI_Bricks.size()) {
            CI_Bricks.replace(i, value.at(j));
            qDebug() << QString("CI_Bricks.replace(%1, value.at(%2)): %3").arg(i).arg(j).arg(value.at(j).getContent());
            qDebug() << QString("CI_Bricks.replace(%1, value.at(%2)): %3").arg(i).arg(j).arg(value.at(j).getMask());
            return;
        }

        if(i > 255) {
            return;
        }

        CI_Bricks.append(value.at(j));
        qDebug() << "append: ";
    }
}

void CI::setCiBrick(const CI_Brick &value, quint8 index)
{
    CI_Bricks.replace(index, value);
}

quint8 CI::getCiBrickContent(quint8 index)
{
    return CI_Bricks[index].getContent();
}

void CI::setCiBrickContent(const quint8 &value, quint8 index)
{
    CI_Bricks[index].setContent(value);
}

quint8 CI::getCiBrickMask(quint8 index)
{
    return CI_Bricks[index].getMask();
}

void CI::setCiBrickMask(const quint8 &value, quint8 index)
{
    CI_Bricks[index].setMask(value);
}
