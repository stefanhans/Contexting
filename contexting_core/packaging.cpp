#include "packaging.h"

void Packaging::add(const QByteArray &packet)
{
    packets.append(packet);
}
