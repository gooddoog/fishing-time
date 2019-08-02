#ifndef INCLUDE_DICTIONARY_H_
#define INCLUDE_DICTIONARY_H_
#include <QVector>
#include <QMap>

enum class Language {
    English,
    Russian
};

class Dictionary {
public:
    const QVector <QString> languages;
    const QVector <QString> itemIds;
    const QMap <QString, const QString*> itemNames;
    const QString fishingTime = "Fishing time";
    static constexpr int DICTIONARY_START = __LINE__;
    const QString
            autoSavePeriod,
            back,
            basicNet,
            bream,
            buy,
            carp,
            changePassword,
            click,
            clicksCount,
            confirmPassword,
            confirmPasswordWarning,
            console,
            deleteAccount,
            deleteAccountConfirmation,
            demoMode,
            demoModeWarning,
            dialog,
            empty,
            emptyLoginWarning,
            emptyPasswordWarning,
            exit,
            exitConfirmation,
            fishLabelText,
            id,
            ide,
            incorrectPassword,
            information,
            invalidOldPasswordWarning,
            invalidValue,
            inventory,
            language,
            logError,
            logIn,
            logInfo,
            logOut,
            logWarning,
            mainLabelText,
            mainMenuText,
            market,
            min,
            name,
            netSlot,
            nets,
            netsDescription,
            newPassword,
            newPasswordConfirmation,
            newUserCreatedText,
            oka,
            oldPassword,
            password,
            passwordIsChanged,
            perch,
            pike,
            price,
            quantity,
            quantityShouldBeANumber,
            quantityShouldBeMoreThanZero,
            roach,
            selectItemFromList,
            sellerText,
            settings,
            signUp,
            signupMenuText,
            start,
            statistics,
            store,
            thisUserAlreadyExistsText,
            userSettings,
            userSettingsText,
            username,
            volga,
            warning,
            youDontHaveEnoughCoins,
            youDontHaveEnoughItems;
    static constexpr int DICTIONARY_END = __LINE__;
    Dictionary();
    void setLanguage(Language l);
    const QString &getItemName(const QString &id) const;
};
#endif  // INCLUDE_DICTIONARY_H_
