#ifndef CI_BRICK_H
#define CI_BRICK_H

#include <QVector>

class CI_Brick {

public:

    CI_Brick(quint8 content=0, quint8 mask=0) :
    content(content),
    mask(mask) {}

    ~CI_Brick() {}

    bool operator==(const CI_Brick &ci_brick);

    quint8 getContent() const;
    void setContent(const quint8 &value);

    quint8 getMask() const;
    void setMask(const quint8 &value);

    bool contentMatch(quint8 otherContent) const;
    bool contextMatch(quint8 otherContent, quint8 otherMask) const;

    bool contentMatch(CI_Brick otherBrick) const;
    bool contextMatch(CI_Brick otherBrick) const;

    bool hasEmptyMask() const;
    bool hasFullMask() const;

    QString contentToHex() const;
    QString maskToHex() const;

    QString contentToBinary() const;
    QString maskToBinary() const;

    QString contentToPath() const;

    QString contextToRoute() const;
    QString contextToRoutePath() const;

private:

    quint8 content;
    quint8 mask;
};


#endif // CI_BRICK_H
