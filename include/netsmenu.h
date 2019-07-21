#ifndef INCLUDE_NETSMENU_H_
#define INCLUDE_NETSMENU_H_
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>

class Game;

class NetsMenu : public QObject {
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
    QGridLayout *grid;
private:
    void updateNets();
private slots:
    void backFunction();
public:
    NetsMenu(Game *game, QGridLayout *grid);
    ~NetsMenu();
    void display();
    void hide();
};

#endif  // INCLUDE_NETSMENU_H_