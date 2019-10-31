#ifndef INCLUDE_NETSMENU_H_
#define INCLUDE_NETSMENU_H_
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <QTimer>
#include "menu.h"

class NetsMenu : public Menu {
private:
    Q_OBJECT
private:
    static const int SLOTS_COUNT = 9;
    Game *game;
    QPushButton backButton;
    QLabel netsDescription,
           netSlotLabel[SLOTS_COUNT];
    QComboBox netSlot[SLOTS_COUNT];
    QString nets[SLOTS_COUNT];
    QTimer netsTimer;
    QGridLayout *grid;
private:
    void updateNets();
private slots:
    void netsTimerTick();
private slots:
    void backFunction();
public:
    NetsMenu(Game *game, QGridLayout *grid);
    ~NetsMenu();
    void display() override;
    void hide() override;
    void foldNets();
};

#endif  // INCLUDE_NETSMENU_H_
