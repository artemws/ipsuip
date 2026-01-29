#include "MainWindowController.h"
#include <QFileDialog>
#include <QDebug>
#include <QDir>

MainWindowController::MainWindowController(QObject *parent)
    : QObject(parent)
    , m_downloadPath(QDir::homePath() + "/Downloads")
    , m_progressValue(0.0)
{
}

void MainWindowController::setDownloadPath(const QString &path)
{
    if (m_downloadPath != path) {
        m_downloadPath = path;
        emit downloadPathChanged();
    }
}

void MainWindowController::setProgressValue(double value)
{
    if (m_progressValue != value) {
        m_progressValue = value;
        emit progressValueChanged();
    }
}

void MainWindowController::chooseCountries()
{
    // Здесь будет открытие диалога выбора стран
    // Временно - просто добавим тестовые данные
    updateSelectedCountries({"Russia", "China", "USA"});
}

void MainWindowController::chooseMainlands()
{
    // Здесь будет открытие диалога выбора материков
    // Временно - просто добавим тестовые данные
    updateSelectedMainlands({"Europe", "Asia"});
}

void MainWindowController::selectDirectory()
{
    QString directory = QFileDialog::getExistingDirectory(nullptr,
                                                          tr("Выберите директорию для загрузки"),
                                                          m_downloadPath,
                                                          QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (!directory.isEmpty()) {
        setDownloadPath(directory);
    }
}

void MainWindowController::startDownload()
{
    if (m_selectedCountries.isEmpty() && m_selectedMainlands.isEmpty()) {
        emit errorOccurred("Выберите хотя бы одну страну или материк");
        return;
    }

    if (m_downloadPath.isEmpty()) {
        emit errorOccurred("Выберите директорию для загрузки");
        return;
    }

    emit downloadStarted();

    try {
        // Получаем коды стран и материков
        QStringList countryCodes = getCountryCodes(m_selectedCountries);
        QStringList mainlandCodes = getMainlandCodes(m_selectedMainlands);

        // Создаем обратные отображения
        std::map<std::string, std::string> cc = ipsuip::map_code_revers(ipsuip::country_code_data);
        std::map<std::string, std::string> mc = ipsuip::map_code_revers(ipsuip::mainland_code_data);

        // Рассчитываем прогресс
        size_t sum = 100 / (countryCodes.size() + mainlandCodes.size());
        double progress = 0.0;

        // Обрабатываем выбранные страны
        for (const auto& countryCode : countryCodes) {
            qDebug() << "Processing country:" << countryCode;
            std::cout << countryCode.toStdString() << std::endl;
            if (cc.find(countryCode.toStdString()) != cc.end()) {
                std::cout << cc[countryCode.toStdString()] << std::endl;
            }

            // Имитация прогресса
            progress += sum;
            setProgressValue(progress);
            
            // Здесь должен быть вызов реальной функции обработки
            ipsuip::run_init(cc[countryCode.toStdString()],
                             m_downloadPath.toStdString(),
                             ipsuip::map_code(ipsuip::country_code_data),
                             ipsuip::TYPEPARSING::COUNTRY);
        }

        // Обрабатываем выбранные материки
        for (const auto& mainlandCode : mainlandCodes) {
            qDebug() << "Processing mainland:" << mainlandCode;
            std::cout << mainlandCode.toStdString() << std::endl;
            if (mc.find(mainlandCode.toStdString()) != mc.end()) {
                std::cout << mc[mainlandCode.toStdString()] << std::endl;
            }

            // Имитация прогресса
            progress += sum;
            setProgressValue(progress);
            
            // Здесь должен быть вызов реальной функции обработки
            ipsuip::run_init(mc[mainlandCode.toStdString()],
                             m_downloadPath.toStdString(),
                             ipsuip::map_code(ipsuip::mainland_code_data),
                             ipsuip::TYPEPARSING::CONTINENT);
        }

        setProgressValue(100.0);
        emit downloadCompleted();

    } catch (const std::exception& e) {
        emit errorOccurred(QString("Ошибка при обработке: %1").arg(e.what()));
    }
}

void MainWindowController::updateSelectedCountries(const QStringList &countries)
{
    if (m_selectedCountries != countries) {
        m_selectedCountries = countries;
        emit selectedCountriesChanged();
    }
}

void MainWindowController::updateSelectedMainlands(const QStringList &mainlands)
{
    if (m_selectedMainlands != mainlands) {
        m_selectedMainlands = mainlands;
        emit selectedMainlandsChanged();
    }
}

void MainWindowController::processSelectedCountries()
{
    // Здесь может быть дополнительная обработка выбранных стран
    qDebug() << "Processing selected countries:" << m_selectedCountries;
}

void MainWindowController::processSelectedMainlands()
{
    // Здесь может быть дополнительная обработка выбранных материков
    qDebug() << "Processing selected mainlands:" << m_selectedMainlands;
}

QStringList MainWindowController::getCountryCodes(const QStringList &countryNames)
{
    QStringList codes;
    std::map<std::string, std::string> cc = ipsuip::map_code_revers(ipsuip::country_code_data);
    
    for (const auto& countryName : countryNames) {
        auto it = std::find_if(ipsuip::country_code_data.begin(), ipsuip::country_code_data.end(),
            [&countryName](const std::string& item) {
                return item == countryName.toStdString();
            });
        
        if (it != ipsuip::country_code_data.end()) {
            // Следующий элемент - это код страны
            auto codeIt = it + 1;
            if (codeIt != ipsuip::country_code_data.end()) {
                codes.append(QString::fromStdString(*codeIt));
            }
        }
    }
    
    return codes;
}

QStringList MainWindowController::getMainlandCodes(const QStringList &mainlandNames)
{
    QStringList codes;
    std::map<std::string, std::string> mc = ipsuip::map_code_revers(ipsuip::mainland_code_data);
    
    for (const auto& mainlandName : mainlandNames) {
        auto it = std::find_if(ipsuip::mainland_code_data.begin(), ipsuip::mainland_code_data.end(),
            [&mainlandName](const std::string& item) {
                return item == mainlandName.toStdString();
            });
        
        if (it != ipsuip::mainland_code_data.end()) {
            // Следующий элемент - это код материка
            auto codeIt = it + 1;
            if (codeIt != ipsuip::mainland_code_data.end()) {
                codes.append(QString::fromStdString(*codeIt));
            }
        }
    }
    
    return codes;
}