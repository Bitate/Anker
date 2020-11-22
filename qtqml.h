#ifndef QTQML_H
#define QTQML_H

#include <QObject>

class qtQML : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int sum READ sum WRITE setSum NOTIFY sumChanged)
public:
    explicit qtQML(QObject *parent = nullptr);
    int sum();
    Q_INVOKABLE void setSum(int s);


signals:
    void sumChanged();
private:
    int m_sum;
};

#endif // QTQML_H
