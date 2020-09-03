#include "intervalset.h"
#include "ui_intervalset.h"

IntervalSet::IntervalSet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IntervalSet)
{
    ui->setupUi(this);

    void (QSpinBox:: *QSpinBoxValueChanged)(int) = &QSpinBox::valueChanged;
    connect(ui->spinBoxInterval, QSpinBoxValueChanged, [=](int value){
        ui->horizontalSliderInterval->setValue(value);
    });

    void (QSlider:: *QSliderValueChanged)(int) = &QSlider::valueChanged;
    connect(ui->horizontalSliderInterval, QSliderValueChanged, [=](int value){
        ui->spinBoxInterval->setValue(value);
    });
}

IntervalSet::~IntervalSet()
{
    delete ui;
}

void IntervalSet::setValue(int value)
{
    ui->spinBoxInterval->setValue(value);
}

int IntervalSet::getValue()
{
    return ui->spinBoxInterval->value();
}

