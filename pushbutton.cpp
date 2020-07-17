#include "pushbutton.h"


PushButton::PushButton(const QString &text, int ind, QWidget *parent): QPushButton(text,parent){
    QObject::connect(this, SIGNAL(clicked()),this,SLOT(buttonClicked()));   //connects it's default clicked() signal to it's buttonClicked slot
    s = text;
    this->index = ind;
}
//shows "X"
void PushButton::turnBack(){
    this->setText("X");
}

