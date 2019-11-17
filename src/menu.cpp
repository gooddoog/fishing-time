#include <QKeyEvent>
#include "menu.h"
#include "game.h"

Menu::Menu(Game *game, QGridLayout *grid, bool floating) :
    game(game),
    grid(grid),
    floating(floating) {
    if (!this->grid) {
        this->grid = new QGridLayout(this);
    }
}

bool Menu::isDisplayed() const {
    return displayed;
}

bool Menu::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *key = static_cast<QKeyEvent *>(event);
        qDebug() << typeid(*this).name() << "->" << key->key();
        if (key->key() == 16777216) { // escape
            this->backFunction();
        }
    }
    return QObject::eventFilter(obj, event);
}

void Menu::pre_display() {
    if (!this->floating) {
        if (game->getCurrentMenu() != nullptr) {
            game->logger.error("Previous menu (" + QString(typeid(*game->getCurrentMenu()).name()) + ") is not hide!");
        }
        game->setCurrentMenu(this);
        game->logger.debug("Set current menu to " + QString(typeid(*game->getCurrentMenu()).name()));
    }
    game->installEventFilter(this);
}

void Menu::pre_hide() {
    if (!this->floating) {
        game->setCurrentMenu(nullptr);
        game->logger.debug("Reset current menu");
    }
    game->removeEventFilter(this);
}

void Menu::backFunction() {

}

Menu::~Menu() {

}
