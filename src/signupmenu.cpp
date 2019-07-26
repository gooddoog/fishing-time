#include <QMessageBox>
#include "signupmenu.h"
#include "game.h"

SignupMenu::SignupMenu(Game *game, QGridLayout *grid) :
        game(game),
        grid(grid) {
    grid->addWidget(&signupLabel, 0, 0, 1, 3);
    signupLabel.setWordWrap(true);
    signupLabel.setVisible(false);
    signupLabel.setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

    grid->addWidget(&loginText, 1, 0);
    loginText.setVisible(false);
    loginText.setEnabled(false);
    QObject::connect(&loginText, &QLineEdit::returnPressed, [this]() { signUpFunction(); });

    grid->addWidget(&passwordText, 2, 0);
    passwordText.setEchoMode(QLineEdit::Password);
    passwordText.setVisible(false);
    passwordText.setEnabled(false);
    QObject::connect(&passwordText, &QLineEdit::returnPressed, [this]() { signUpFunction(); });

    connect(&signUpButton, SIGNAL(released()), this, SLOT(signUpFunction()));
    grid->addWidget(&signUpButton, 1, 1);
    signUpButton.setVisible(false);
    signUpButton.setEnabled(false);

    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
    grid->addWidget(&backButton, 3, 1);
    backButton.setVisible(false);
    backButton.setEnabled(false);
}

void SignupMenu::display() {
    signupLabel.setText(game->str.signupMenuText);
    signupLabel.setVisible(true);

    loginText.setText(game->str.enterYourLoginHereText);
    loginText.setVisible(true);
    loginText.setEnabled(true);

    passwordText.setText("Password");
    passwordText.setVisible(true);
    passwordText.setEnabled(true);

    signUpButton.setText(game->str.signUp);
    signUpButton.setVisible(true);
    signUpButton.setEnabled(true);

    backButton.setText(game->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);
}

void SignupMenu::backFunction() {
    this->hide();
    game->loginMenu.display();
}

void SignupMenu::signUpFunction() {
    if (loginText.text() == "") {
        QMessageBox::warning(game, game->str.warning, game->str.emptyLoginWarning);
        return;
    }
    for (int i = 0; i < game->users.size(); ++i) {
        if (game->users[i].getUsername() == loginText.text()) {
            QMessageBox::warning(game, game->str.warning, game->str.thisUserAlreadyExistsText);
            return;
        }
    }
    game->users.push_back(User(loginText.text(), passwordText.text()));
    QMessageBox::information(game, game->str.information,
                             game->str.newUserCreatedText.arg(loginText.text()));
    this->hide();
    game->loginMenu.display();
}

void SignupMenu::hide() {
    signupLabel.setVisible(false);

    loginText.setVisible(false);
    loginText.setEnabled(false);

    passwordText.setVisible(false);
    passwordText.setEnabled(false);

    signUpButton.setVisible(false);
    signUpButton.setEnabled(false);

    backButton.setVisible(false);
    backButton.setEnabled(false);
}

SignupMenu::~SignupMenu() {
    
}
