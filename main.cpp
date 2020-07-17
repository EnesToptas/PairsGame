#include <QApplication>
#include <QPushButton>
#include <QButtonGroup>
#include <QLCDNumber>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <string>
#include <vector>
#include <QTest>
#include "pushbutton.h"
#include "buttoncontroller.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);           //Create the app here
    QWidget       window ;                  //Create the window
    window.setWindowTitle("Find The Pair"); //Set window's title
    QGridLayout   glayout;                  //Create the layout
    ButtonController  buttongroup(nullptr,&glayout) ;   //Create the game logic here

    QLabel pairs_text("Pairs");             //"Pairs" text in the window
    QLabel tries_text("Tries");             //"Tries" text in the window

    pairs_text.setStyleSheet("font: 12pt"); //Set font size to 12pt
    glayout.addWidget(&pairs_text,0,0,1,-1);//Add "Pairs" to layout
    tries_text.setStyleSheet("font: 12pt"); //Set font size to 12pt
    glayout.addWidget(&tries_text,0,2,1,-1);//Add "Tries" to layout

    glayout.addWidget(&buttongroup.pairs,0,1,1,-1); //Add Pairs number to layout
    glayout.addWidget(&buttongroup.tries,0,3,1,-1); //Add Tries number to layout


    QPushButton *resetButton = new QPushButton("Reset");    //Create the reset button
    QObject::connect(resetButton,SIGNAL(clicked()),&buttongroup,SLOT(reset())); //Connect this button to corresponding function
    glayout.addWidget(resetButton,0,4,1,-1);    //Add reset button to layout

    window.setLayout(&glayout);     //Apply the layout to the window
    window.show();                  //Show window

    QTest::qWait(2000);             //Show what is on the cards

    buttongroup.haveAPeek();        //Flips the cards back

    return app.exec();
}


