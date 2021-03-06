#include "ci_brick.h"

bool CI_Brick::operator==(const CI_Brick &ci_brick)
{
    return content == ci_brick.content && mask == ci_brick.mask;
}

quint8 CI_Brick::getContent() const
{
    return (quint8) content;
}

void CI_Brick::setContent(const quint8 &value)
{
    content = value;
}

quint8 CI_Brick::getMask() const
{
    return mask;
}

void CI_Brick::setMask(const quint8 &value)
{
    mask = value;
}

bool CI_Brick::contentMatch(quint8 otherContent) const
{
    return content == otherContent;
}

bool CI_Brick::contextMatch(quint8 otherContent, quint8 otherMask) const
{
    quint8 notEqual = content ^ otherContent;
    if (notEqual == 0) {
        return true;
    }

    quint8 offer_relevant = ~notEqual | mask;
    quint8 not_offer_relevant = ~offer_relevant;
    if (not_offer_relevant != 0) {
        return false;
    }

    quint8 request_relevant = ~notEqual | otherMask;
    quint8 not_request_relevant = ~request_relevant;
    if (not_request_relevant != 0) {
        return false;
    }
    return true;
}

bool CI_Brick::contentMatch(CI_Brick otherBrick) const
{
    return contentMatch(otherBrick.getContent());
}

bool CI_Brick::contextMatch(CI_Brick otherBrick) const
{
    return contextMatch(otherBrick.getContent(), otherBrick.getMask());
}

bool CI_Brick::hasEmptyMask() const
{
    return mask == 0;
}

bool CI_Brick::hasFullMask() const
{
    return mask == 255;
}

QString CI_Brick::contentToHex() const
{
    return QString("%1").arg(content, 2, 16, QLatin1Char('0'));
}

QString CI_Brick::maskToHex() const
{
    return QString("%1").arg(mask, 2, 16, QLatin1Char('0'));
}


QString CI_Brick::contentToBinary() const
{
    return QString("%1").arg(content, 8, 2, QLatin1Char('0'));
}

QString CI_Brick::maskToBinary() const
{
    return QString("%1").arg(mask, 8, 2, QLatin1Char('0'));
}


QString CI_Brick::contextToRoute() const
{
    QString out = "";

    if(maskToHex().at(0) == '0') {
        out += contentToHex().at(0);

        if(maskToHex().at(1) == '0') {
            out += contentToHex().at(1);
        }
    }
    return out;
}
