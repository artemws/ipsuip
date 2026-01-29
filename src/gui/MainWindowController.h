#pragma once

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVector>
#include "functions.h"

class MainWindowController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString downloadPath READ downloadPath WRITE setDownloadPath NOTIFY downloadPathChanged)
    Q_PROPERTY(QStringList selectedCountries READ selectedCountries NOTIFY selectedCountriesChanged)
    Q_PROPERTY(QStringList selectedMainlands READ selectedMainlands NOTIFY selectedMainlandsChanged)
    Q_PROPERTY(double progressValue READ progressValue WRITE setProgressValue NOTIFY progressValueChanged)

public:
    explicit MainWindowController(QObject *parent = nullptr);

    // Геттеры и сеттеры для свойств
    QString downloadPath() const { return m_downloadPath; }
    void setDownloadPath(const QString &path);

    QStringList selectedCountries() const { return m_selectedCountries; }
    QStringList selectedMainlands() const { return m_selectedMainlands; }
    double progressValue() const { return m_progressValue; }
    void setProgressValue(double value);

    // Методы для QML
    Q_INVOKABLE void chooseCountries();
    Q_INVOKABLE void chooseMainlands();
    Q_INVOKABLE void selectDirectory();
    Q_INVOKABLE void startDownload();

    // Методы для обновления данных из диалогов
    void updateSelectedCountries(const QStringList &countries);
    void updateSelectedMainlands(const QStringList &mainlands);

signals:
    void downloadPathChanged();
    void selectedCountriesChanged();
    void selectedMainlandsChanged();
    void progressValueChanged();
    void downloadStarted();
    void downloadCompleted();
    void errorOccurred(const QString &message);

private:
    QString m_downloadPath;
    QStringList m_selectedCountries;
    QStringList m_selectedMainlands;
    double m_progressValue;

    // Вспомогательные методы
    void processSelectedCountries();
    void processSelectedMainlands();
    QStringList getCountryCodes(const QStringList &countryNames);
    QStringList getMainlandCodes(const QStringList &mainlandNames);
};
