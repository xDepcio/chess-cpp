#pragma once
#include <qlabel.h>
class ClickableLabel : public QLabel
{
    Q_OBJECT

public:
    ClickableLabel(QWidget* parent = nullptr) : QLabel(parent) {}

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event) override {
        // emit the clicked() signal when the label is clicked
        emit clicked();

        // call the base class implementation
        QLabel::mousePressEvent(event);
    }
};


