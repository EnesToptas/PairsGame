#include "buttoncontroller.h"

ButtonController::ButtonController(QObject *parent,QGridLayout *glayout) : QObject(parent)
{
    layout_pointer = glayout;       //Assign the pointer

    letters = {"A","B","C","D","E","F","G","H","I","J","K","L","A","B","C","D","E","F","G","H","I","J","K","L"};

    pairs.setText(QString::number(pairs_int));  //Turn pairs number into label
    pairs.setStyleSheet("color: black; font: 12pt");
    tries.setText(QString::number(tries_int));  //Turn tries number into label
    tries.setStyleSheet("color: black; font: 12pt");

    allButtons.resize(24);  //Set button lists size to 24

    srand (time (0));
    for(int i=0 ; i < 4 ; i++) {
      for(int j=0 ; j < 6 ; j++) {
         int duduk = rand() % letters.size();   //Get a random number
         QString s = QString::fromStdString(letters[duduk]);    //Get a letter from the list
         letters.erase(letters.begin()+duduk);  //Erase this letter from the list not to use it again
         allButtons[6*i+j] = new PushButton(s,6*i+j);   //Create a button
         allButtons[6*i+j]->setStyleSheet("font: bold;background-color: rgb(255, 161, 127);font-size: 36px;");
         allButtons[6*i+j]->setFixedSize(btnSize);      //Set the size of the button
         allButtons[6*i+j]->blockSignals(true);         //Make it unclickable(so that until all cards are flipped back, no card is clickable)
         glayout->addWidget(allButtons[6*i+j],i+1,j);   //Add this button to layout
         QObject::connect(this->allButtons[6*i+j], SIGNAL(imOpen(int)),this,SLOT(oneOpened(int)));  //connect buttons signal to controllers slot
         QObject::connect(this, SIGNAL(dontClick()),this->allButtons[6*i+j],SLOT(imNotClicking())); //connect controllers dontClick signal to buttons slot
         QObject::connect(this, SIGNAL(doClick()),this->allButtons[6*i+j],SLOT(imClicking()));      //connect controllers doClick signal to buttons slot

       }
    }
}
void ButtonController::oneOpened(int a)
{
    openButtons.push_back(a);   //add the clicked button to the list
    if(openButtons.size()==2){  //if two are open check them if they have the same letter
        if(allButtons[openButtons[0]]->s == allButtons[openButtons[1]]->s){ //if they have the same letter
            pairs_int++;        //incremenet pairs
            tries_int++;        //increment tries
            pairs.setText(QString::number(pairs_int));
            tries.setText(QString::number(tries_int));
            emit dontClick();   //make other buttons unclickable
            QTest::qWait(750);  //show the letters for 0.750 second
            emit doClick();     //make other buttons clickable again
            allButtons[openButtons[0]]->setDisabled(true);  //make the buttons disappear
            allButtons[openButtons[0]]->setVisible(false);
            allButtons[openButtons[1]]->setDisabled(true);
            allButtons[openButtons[1]]->setVisible(false);
            openButtons.pop_back(); //reset the openButtons list
            openButtons.pop_back();
        }
        else{   //if they don't have the same letter
            tries_int++;    //increment tries
            tries.setText(QString::number(tries_int));
            emit dontClick();   //make other buttons unclickable
            QTest::qWait(750);  //show the letters for 0.750 second
            emit doClick();     //make other buttons clickable again
            allButtons[openButtons[1]]->secondButton = 1;   //set the secondButton value to true for the second clicked button
            allButtons[openButtons[0]]->turnBack(); //flip back the opened cards
            allButtons[openButtons[1]]->turnBack();
            openButtons.pop_back(); //reset the openButtons list
            openButtons.pop_back();
        }
    }
}
//flips back the cards
void ButtonController::haveAPeek()
{
    for(int i=0 ; i < 4 ; i++) {
      for(int j=0 ; j < 6 ; j++) {
         allButtons[6*i+j]->setText("X");
         allButtons[6*i+j]->blockSignals(false);
       }
    }
}
//basically resets everything, does the same things with constructor
void ButtonController::reset()
{
    this->pairs_int=0;
    this->tries_int=0;

    for (int i = 0; i < layout_pointer->columnCount(); ++i) {
        for (int j=1;j< layout_pointer->rowCount(); ++j) {
            QLayoutItem* item = layout_pointer->itemAtPosition(j, i);
            if (!item) continue;
            if (item->widget()) {delete item->widget();}
            else {
                layout_pointer->removeItem(item);
                delete item;
            }
        }
    }

    letters = {"A","B","C","D","E","F","G","H","I","J","K","L","A","B","C","D","E","F","G","H","I","J","K","L"};

    pairs.setText(QString::number(pairs_int));
    pairs.setStyleSheet("color: black; font: 12pt");
    tries.setText(QString::number(tries_int));
    tries.setStyleSheet("color: black; font: 12pt");

    allButtons.resize(24);
    openButtons = {};

    srand (time (0));
    for(int i=0 ; i < 4 ; i++) {
      for(int j=0 ; j < 6 ; j++) {
         int duduk = rand() % letters.size();
         QString s = QString::fromStdString(letters[duduk]);
         letters.erase(letters.begin()+duduk);
         allButtons[6*i+j] = new PushButton(s,6*i+j);
         allButtons[6*i+j]->setStyleSheet("font: bold;background-color: rgb(255, 161, 127);font-size: 36px;");
         allButtons[6*i+j]->setFixedSize(btnSize);
         allButtons[6*i+j]->blockSignals(true);
         layout_pointer->addWidget(allButtons[6*i+j],i+1,j);
         QObject::connect(this->allButtons[6*i+j], SIGNAL(imOpen(int)),this,SLOT(oneOpened(int)));
         QObject::connect(this, SIGNAL(dontClick()),this->allButtons[6*i+j],SLOT(imNotClicking()));
         QObject::connect(this, SIGNAL(doClick()),this->allButtons[6*i+j],SLOT(imClicking()));

       }
    }

    QTest::qWait(2000);
    haveAPeek();

}
