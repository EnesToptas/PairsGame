#ifndef BUTTONCONTROLLER_H
#define BUTTONCONTROLLER_H

#include <QObject>
#include <vector>
#include "pushbutton.h"
#include <QTest>
#include <QLabel>
#include <QString>
#include <string>
#include <vector>
#include <QGridLayout>

using namespace std;

class ButtonController : public QObject
{
    Q_OBJECT
    int pairs_int=0;    //Pairs number
    int tries_int=0;    //Tries number
    vector<string> letters; //Letters on the cards
    const QSize btnSize = QSize(50, 50);    //Create this to make buttons size 50x50
    QGridLayout* layout_pointer;    //Layout pointer is needed to access the layout inside class functions
public:
    QLabel       pairs ;    //Label to display pairs number
    QLabel       tries ;    //Label to display tries number
    std::vector<int> openButtons;   //List of currently open cards
    std::vector<PushButton*> allButtons;    //List of all cards
    explicit ButtonController(QObject *parent = nullptr,QGridLayout *glayout = nullptr);    //Constructor
    void haveAPeek();   //Flips cards back
signals:
    void dontClick();   //Send this signal to make buttons unclickable
    void doClick();     //Send this signal to make buttons clickable
public slots:
    void oneOpened(int a);  //This slot is triggered every time a card is opened
    void reset();           //This slot is triggered if the reset button is clicked
};

#endif // BUTTONCONTROLLER_H
