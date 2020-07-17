#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <QPushButton>

class PushButton : public QPushButton   //class inheriting QPushButton
{
    Q_OBJECT
public:
    PushButton(const QString &text, int ind, QWidget *parent = nullptr);
    QString s;  //letter the card has
    int index;  //index of this card in the allButtons list
    bool secondButton = false;  //when two cards get opened, the second button becomes unclickable, to fix that issue(explained below)
    void turnBack();    //flips them back(show 'X')
signals:
    void imOpen(int number);    //basically the clicked signal but also sends the index
public slots:
    void imNotClicking(){this->blockSignals(true);} //to make it unclickable
    void imClicking(){this->blockSignals(false);}   //to make it clickable again
    void buttonClicked(){       //when a button is clicked, this slot is triggered
        this->setText(s);       //show the letter
        emit imOpen(index);     //send a clicked signal with the buttons corresponding index
        this->blockSignals(true);   //make it unclickable (so one cannot click the same button twice)
        if(secondButton)                //when the second button emits the imOpen signal, cards are compared and all
            this->blockSignals(false);  //buttons become clickable again
        secondButton = false;           //this line sets it to false again
    }
};

#endif // PUSHBUTTON_H
