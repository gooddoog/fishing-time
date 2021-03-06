#include <QHeaderView>
#include <QSettings>
#include <QStringList>
#include "gamemenu.h"
#include "game.h"

GameMenu::GameMenu(Game *game, QGridLayout *grid, InventoryMenu *inv) :
        Menu(game, grid),
        popUpInventoryTable(inv) {
    QSettings settings;
    if (!popUpInventoryTable->restoreGeometry(settings.value("inventoryWindowGeometry").toByteArray())) {
        this->game->logger.error("Unable to restore inventory window geometry. Loading defaults...");
        popUpInventoryTable->setGeometry(QRect(QPoint(0, 0), QSize(300, 400)));
    }
    popUpInventoryTable->hide();

    grid->addWidget(&infoLabel, 1, 0);
    infoLabel.setWordWrap(true);
    infoLabel.setVisible(false);
    infoLabel.setEnabled(false);
    infoLabel.setAttribute(Qt::WA_TransparentForMouseEvents);
    infoLabel.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    grid->addWidget(&fishLabel, 1, 2);
    fishLabel.setWordWrap(true);
    fishLabel.setVisible(false);
    fishLabel.setEnabled(false);
    fishLabel.setAttribute(Qt::WA_TransparentForMouseEvents);
    fishLabel.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    grid->addWidget(&profileButton, 0, 0);
    profileButton.setVisible(false);
    profileButton.setEnabled(false);
    connect(&profileButton, SIGNAL(released()), this, SLOT(profileFunction()));

    grid->addWidget(&logOutButton, 0, 2);
    logOutButton.setVisible(false);
    logOutButton.setEnabled(false);
    connect(&logOutButton, SIGNAL(released()), this, SLOT(logOutFunction()));

    grid->addWidget(&statisticsButton, 2, 0);
    statisticsButton.setVisible(false);
    statisticsButton.setEnabled(false);
    connect(&statisticsButton, SIGNAL(released()), this, SLOT(statisticsFunction()));

    grid->addWidget(&usersettingsButton, 2, 1);
    usersettingsButton.setVisible(false);
    usersettingsButton.setEnabled(false);
    connect(&usersettingsButton, SIGNAL(released()), this, SLOT(usersettingsFunction()));

    grid->addWidget(&netsButton, 2, 2);
    netsButton.setVisible(false);
    netsButton.setEnabled(false);
    connect(&netsButton, SIGNAL(released()), this, SLOT(netsFunction()));

    grid->addWidget(&storeButton, 3, 0);
    storeButton.setVisible(false);
    storeButton.setEnabled(false);
    connect(&storeButton, SIGNAL(released()), this, SLOT(storeFunction()));

    grid->addWidget(&clickButton, 3, 1);
    clickButton.setVisible(false);
    clickButton.setEnabled(false);
    connect(&clickButton, SIGNAL(released()), this, SLOT(clickFunction()));

    grid->addWidget(&locationButton, 3, 2);
    locationButton.setVisible(false);
    locationButton.setEnabled(false);
    connect(&locationButton, SIGNAL(released()), this, SLOT(locationFunction()));

    grid->addWidget(&inventoryButton, 4, 0);
    inventoryButton.setVisible(false);
    inventoryButton.setEnabled(false);
    connect(&inventoryButton, SIGNAL(released()), this, SLOT(inventoryFunction()));

    grid->addWidget(&marketButton, 4, 1);
    marketButton.setVisible(false);
    marketButton.setEnabled(false);
    connect(&marketButton, SIGNAL(released()), this, SLOT(marketFunction()));

    grid->addWidget(&backButton, 4, 2);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void GameMenu::display() {
    this->pre_display();

    game->setMouseTracking(true);

    updateInfo();
    infoLabel.setVisible(true);
    infoLabel.setEnabled(true);

    fishLabel.setVisible(true);
    fishLabel.setEnabled(true);

    nameHeader.setText(game->str.name);
    quantityHeader.setText(game->str.quantity);

    clickButton.setText(game->str.click);
    clickButton.setVisible(true);
    clickButton.setEnabled(true);

    profileButton.setText(game->str.profile);
    profileButton.setVisible(true);
    profileButton.setEnabled(true);

    logOutButton.setText(game->str.logOut);
    logOutButton.setVisible(true);
    logOutButton.setEnabled(true);

    backButton.setText(game->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);

    inventoryButton.setText(game->str.inventory);
    inventoryButton.setVisible(true);
    inventoryButton.setEnabled(true);

    marketButton.setText(game->str.market);
    marketButton.setVisible(true);
    marketButton.setEnabled(true);

    storeButton.setText(game->str.store);
    storeButton.setVisible(true);
    storeButton.setEnabled(true);

    netsButton.setText(game->str.nets);
    netsButton.setVisible(true);
    netsButton.setEnabled(true);

    statisticsButton.setText(game->str.statistics);
    statisticsButton.setVisible(true);
    statisticsButton.setEnabled(true);

    usersettingsButton.setText(game->str.userSettings);
    usersettingsButton.setVisible(true);
    usersettingsButton.setEnabled(true);

    locationButton.setText(game->str.location);
    locationButton.setVisible(true);
    locationButton.setEnabled(true);

    displayed = true;
}

void GameMenu::clickFunction() {
    const int MOD = 100;
    std::uniform_int_distribution<> dist(1, 99);
    int rnd = dist(game->randomGenerator) % MOD;
    QString fish = game->locations[game->activeLocation].getFish(
            qMin(rnd / (MOD / game->locations[game->activeLocation].getFishCount()),
            game->locations[game->activeLocation].getFishCount() - 1));
    game->users[game->activeUser].inventory.changeItem(fish, 1);
    game->users[game->activeUser].inventory.updateStats(fish, "stats.caught", 1, &game->str.stats);
    game->users[game->activeUser].incClicks();
    game->users[game->activeUser].changeExperience(1);
    updateInfo();
}

bool GameMenu::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *key = static_cast<QKeyEvent *>(event);
        if (key->key() == Qt::Key_Enter || key->key() == Qt::Key_Return) {
            if (!key->isAutoRepeat()) {
                clickFunction();
            }
        }
    } else if (event->type() == QEvent::MouseMove) {
        QMouseEvent *e = static_cast<QMouseEvent *>(event);
        qDebug() << e->pos() << game->height();
        if (!displayedButtons && e->pos().y() > game->height() * 2 / 3) {
            qDebug() << "display";
            displayButtons();
        } else if (displayedButtons && e->pos().y() <= game->height() * 2 / 3) {
            qDebug() << "hide";
            hideButtons();
        }
    }
    return Menu::eventFilter(obj, event);
}

void GameMenu::displayButtons() {
    clickButton.setVisible(true);
    clickButton.setEnabled(true);

    backButton.setVisible(true);
    backButton.setEnabled(true);

    inventoryButton.setVisible(true);
    inventoryButton.setEnabled(true);

    marketButton.setVisible(true);
    marketButton.setEnabled(true);

    storeButton.setVisible(true);
    storeButton.setEnabled(true);

    netsButton.setVisible(true);
    netsButton.setEnabled(true);

    statisticsButton.setVisible(true);
    statisticsButton.setEnabled(true);

    usersettingsButton.setVisible(true);
    usersettingsButton.setEnabled(true);

    locationButton.setVisible(true);
    locationButton.setEnabled(true);

    displayedButtons = true;
}

void GameMenu::hideButtons() {
    clickButton.setVisible(false);
    clickButton.setEnabled(false);

    backButton.setVisible(false);
    backButton.setEnabled(false);

    inventoryButton.setVisible(false);
    inventoryButton.setEnabled(false);

    marketButton.setVisible(false);
    marketButton.setEnabled(false);

    storeButton.setVisible(false);
    storeButton.setEnabled(false);

    netsButton.setVisible(false);
    netsButton.setEnabled(false);

    statisticsButton.setVisible(false);
    statisticsButton.setEnabled(false);

    usersettingsButton.setVisible(false);
    usersettingsButton.setEnabled(false);

    locationButton.setVisible(false);
    locationButton.setEnabled(false);

    displayedButtons = false;
}

void GameMenu::profileFunction() {
    this->hide();
    game->userProfileMenu.display();
}

void GameMenu::logOutFunction() {
    game->gameMenu.popUpInventoryTable->setVisible(false);
    game->netsMenu.foldNets();
    game->updateTimePlayed();
    game->userTimestamp = QDateTime();
    game->activeUser = -1;
    game->activeLocation = -1;
    backFunction();
}

void GameMenu::backFunction() {
    this->hide();
    game->mainMenu.display();
}

void GameMenu::inventoryFunction() {
    updateInfo();
    switch (game->inventoryType) {
    case InventoryType::POPUP:
        popUpInventoryTable->setWindowTitle(game->str.fishingTime + ": " + game->str.inventory);
        popUpInventoryTable->setFont(game->font());
        popUpInventoryTable->setVisible(true);
        popUpInventoryTable->setEnabled(true);
        popUpInventoryTable->display();
        break;
    case InventoryType::BUILTIN:
        this->hide();
        game->inventoryMenu.display();
        break;
    }
}

void GameMenu::marketFunction() {
    this->hide();
    game->marketMenu.display();
}

void GameMenu::storeFunction() {
    this->hide();
    game->storeMenu.display();
}

void GameMenu::netsFunction() {
    this->hide();
    game->netsMenu.display();
}

void GameMenu::statisticsFunction() {
    this->hide();
    game->statisticsMenu.display();
}

void GameMenu::usersettingsFunction() {
    this->hide();
    game->usersettingsMenu.display();
}

void GameMenu::locationFunction() {
    this->hide();
    game->locationMenu.display();
}

void GameMenu::updateInfo() {
    if (game->activeUser != -1) {
        popUpInventoryTable->updateInventoryTables();
        infoLabel.setText(game->str.mainLabelText.arg(
            game->users[game->activeUser].getUsername(),
            QString::number(game->users[game->activeUser].getLevel()),
            QString::number(game->users[game->activeUser].getRemainingForNextLevel()),
            QString::number(game->users[game->activeUser].getNeededForNextLevel()),
            QString::number(game->users[game->activeUser].getCoins()),
            QString::number(game->users[game->activeUser].getClicks())
        ));
    }
    if (game->activeLocation != -1) {
        QStringList fishList;
        for (int i = 0; i < game->locations[game->activeLocation].getFishCount(); ++i) {
            fishList.push_back(
                game->str.getItemName(game->locations[game->activeLocation].getFish(i)));
        }
        fishLabel.setText(game->str.fishLabelText.arg(
            game->str.locations[game->locations[game->activeLocation].getId()],
            fishList.join(", ")
        ));
    }
}

InventoryMenu &GameMenu::getPopUpInventoryTable() {
    return *popUpInventoryTable;
}

void GameMenu::hide() {
    this->pre_hide();

    game->setMouseTracking(false);

    infoLabel.setVisible(false);

    fishLabel.setVisible(false);

    profileButton.setVisible(false);
    profileButton.setEnabled(false);

    logOutButton.setVisible(false);
    logOutButton.setEnabled(false);

    hideButtons();

    displayed = false;
}

GameMenu::~GameMenu() {

}
