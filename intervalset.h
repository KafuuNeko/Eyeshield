#ifndef INTERVALSET_H
#define INTERVALSET_H

#include <QWidget>

namespace Ui {
class IntervalSet;
}

class IntervalSet : public QWidget
{
    Q_OBJECT

public:
    explicit IntervalSet(QWidget *parent = nullptr);
    ~IntervalSet();

    void setValue(int value);
    int getValue();

private:
    Ui::IntervalSet *ui;
};

#endif // INTERVALSET_H
