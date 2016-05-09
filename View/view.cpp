#include "view.h"
#include "ui_view.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QDebug>

view::view(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::view)
{
    ui->setupUi(this);
    auto vlMain = new QVBoxLayout(ui->centralWidget);
    auto glLetters = new QGridLayout();

    //
    for (char c='a'; c<='z';++c)
    {
        auto btn = new QPushButton();
        btn->setMinimumSize(20,20);
        btn->setMaximumSize(20,20);
        btn->setText(QString(c));

        int idx = c-'a';
        glLetters->addWidget(btn, idx / 6, idx%6);


        connect(btn, &QPushButton::clicked,this, &view::onLetterClicked);
    }

    vlMain->addLayout(glLetters);
}

view::~view()
{
    delete ui;
}

void view::onLetterClicked()
{
    //sender must be a QPushButon
    //downcasting is safe
    QPushButton* btn = dynamic_cast<QPushButton*>(sender()); //lets us use the btn that was pressed

    //updates the model
    //hangman.guess(btn->text()) <- QString



    //draw():
    btn->setEnabled(false);
    qWarning() << btn->text();
}
