////////////////////////////////////////////////////////////
///     Chris Arsenault
///     QT
///     Hangman project
///
///////////////////////////////////////////////////////////

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../hangmanGit/Model/hangmanclass.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <map>
#include <QMessageBox>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _imageFor({ {Picture::ONE, "border-image:url(:/route/Media/images/gallows0.png)"}, // all the pictures and URLS
    {Picture::TWO, "border-image:url(:/route/Media/images/gallows1.png)"},
    {Picture::THREE, "border-image:url(:/route/Media/images/gallows2.png)"},
    {Picture::FOUR, "border-image:url(:/route/Media/images/gallows3.png)"},
    {Picture::FIVE, "border-image:url(:/route/Media/images/gallows4.png)"},
    {Picture::SIX, "border-image:url(:/route/Media/images/gallows5.png)"},
    {Picture::SEVEN,"border-image:url(:/route/Media/images/gallows6.png)"}})

{
    ui->setupUi(this);
    _game = std::unique_ptr<hangmanClass>(new hangmanClass());

    auto vlMain = new QVBoxLayout(ui->centralWidget);
    auto hlPictureGrid = new QHBoxLayout(); // holds picture and grid layout
    auto glLetters = new QGridLayout(); // letters
    auto hlPhrase = new QHBoxLayout(); // holds phrase
    auto hlNResetBtn = new QHBoxLayout(); // holds reset button

    lblGallows = new QLabel();                             // lbl that holds the picture
    lblGallows->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    lblGallows->setMaximumSize(300,300);
    lblGallows->setMinimumSize(300,300);

    for(char c= 'a'; c <= 'z'; ++c)                                  // all the letter buttons
    {
        auto btn = new QPushButton();
        btn->setMinimumSize(25,25);
        btn->setMaximumSize(25,25);
        btn->setText(QString(c));
        btn->setStyleSheet("QPushButton {color: black; background-color: white }");
        int idx = c - 'a';

        glLetters->addWidget(btn, idx / 6, idx % 6);// adds to grid layout

        connect(btn, &QPushButton::clicked, this, &MainWindow::onLetterClicked);
        letters.push_back(btn);
    }

    hlPictureGrid->addWidget(lblGallows); // adds the picture to the horizontal layout

    QSpacerItem *spacer = new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Fixed); // spacer between picture and letters
    hlPictureGrid->addSpacerItem(spacer); // adds the spacer to top layout

    hlPictureGrid->addLayout(glLetters);  // adds the letters in grid to horizontal

    vlMain->addLayout(hlPictureGrid); // adds the top layout to the main vertical layout

    QSpacerItem *spacer1 = new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Fixed); // spacer on right of phrase

    lblWord = new QLabel;  // label for the hidden phrase
    lblWord->setMaximumSize(400,25);
    lblWord->setMinimumSize(400,25);
    lblWord->setFrameStyle(QFrame::NoFrame);

    hlPhrase->addWidget(lblWord); // add the phrase to the hl
    hlPhrase->addSpacerItem(spacer1);// new spacer between the word and new game button

    vlMain->addLayout(hlPhrase); // add phrase layout to the main layout

    QSpacerItem *spacer2 = new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Fixed); // new spacer for left of new button

    auto btnNewGame= new QPushButton(); // create button for new phrase
    btnNewGame->setMaximumSize(100,25);
    btnNewGame->setMaximumSize(100,25);
    btnNewGame->setText(QString("New Phrase"));


    hlNResetBtn->addSpacerItem(spacer2); // adds the spacer to new button layout
    hlNResetBtn->addWidget(btnNewGame); // adds button to new button layout

    connect(btnNewGame, &QPushButton::clicked, this, &MainWindow::onNewGameClicked);

    vlMain->addLayout(hlNResetBtn); // add sthe new button layout to the main layout

    _game->addWords();
    _game->shuffleWords();

    QString dashWord = QString::fromStdString(_game->newWord()); // gets new phrase in constructor

    lblWord->setText(dashWord); // sets the dash phrase in label

    draw(); // draw shows the gallows and new dash word

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::onLetterClicked()
{
    //downcast. sender must be a QPushButton so downcast is safe

    QPushButton* btn = dynamic_cast<QPushButton*>(sender());
    btn->setEnabled(false);
    btn->setStyleSheet("QPushButton {color: white; background-color: black }"); //sets the color to black so you can tell what you have guessed
    QString letter = btn->text(); //gets the letter from the button
    std::string guess = letter.toLocal8Bit().constData(); //casting it into a string
    _game->processGuess(guess); //checks to see if it was a good guess or not
    draw();
}

void MainWindow::onNewGameClicked()
{
    _game->PrepareGame(); //resets everything
    _game->shuffleWords(); //randoms the words
    _game->newWord(); //gets a new word
    draw();
}

void MainWindow::draw()
{
    QString dashWord = QString::fromStdString(_game->showHiddenPhrase()); // gets new phrase from model

    lblWord->setText(dashWord); // sets the underscores phrase in label

    lblGallows->setStyleSheet(_imageFor.at(_game->showGallows()));

    //draws buttons for th letters
     for (auto btn : letters)
     {
         QString letter = btn->text();
         std::string guess = letter.toLocal8Bit().constData();
         if(_game->letterGuessed(guess))
         {
             btn->setEnabled(false);
         }
         else
         {
            btn->setEnabled(true);
            btn->setStyleSheet("QPushButton {color: black; background-color: white }");
         }
     }
     static bool windowHasBeenShown = false;
     if(_game->won())
     {
         //windowHasBeenShown = true;
         QMessageBox winBox;
         winBox.setText("***************************************\n**                 YOU WIN ^.^                     **\n***************************************");
         winBox.show();
         delay(); //lets the message box stay for more that 0.5 seconds
     }

     if(_game->lost())
     {
         QString word = QString::fromStdString(_game->showPhrase()); // gets new word from the vector
         QMessageBox lossBox;
         lossBox.setText("***************************************\n**                 you lost ;~;                     **\n***************************************");
         lossBox.show();
         delay();
         lblWord->setText(word); // sets the correct amount of underscores
     }
}

void MainWindow::delay() //lets the message box stay for more that 0.5 seconds
{
    QTime dieTime= QTime::currentTime().addSecs(3);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

