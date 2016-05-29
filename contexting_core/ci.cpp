#include "ci.h"

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



QVector<CI_Brick> CI::getCI_Bricks() const
{
    return CI_Bricks;
}

CI_Brick CI::getCI_Bricks(quint8 index) const
{
    return (CI_Brick) CI_Bricks.at(index);
}

void CI::setCI_Bricks(const QVector<CI_Brick> &value)
{
    CI_Bricks = value;
}

void CI::setCI_Bricks(const QByteArray &value)
{
    CI_Bricks.clear();

    for(int i=0; i<value.size();i++) {
        quint8 content = value.at(i++);
        if(i<value.size()) {
            CI_Bricks.append(CI_Brick(content, value.at(i)));
        }
    }
}

void CI::setCI_Brick(const CI_Brick &value, quint8 index)
{
   CI_Bricks.replace(index, value);
}

void CI::setCI_BrickContent(const quint8 &value, quint8 index)
{
   CI_Bricks[index].setContent(value);
}

void CI::setCI_BrickMask(const quint8 &value, quint8 index)
{
    CI_Bricks[index].setMask(value);
}

void CI::truncateCI_Bricks(quint8 size) {
    CI_Bricks.resize(size);
}
