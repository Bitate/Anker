#include "qtqml.h"

qtQML::qtQML(QObject *parent) : QObject(parent)
{

}

void qtQML::setSum(int s)
{
    m_sum = s;
}

int qtQML::sum()
{
    return m_sum;
}

