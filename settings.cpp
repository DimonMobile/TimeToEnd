#include "settings.h"
#include <QSettings>

Settings* Settings::m_instance = nullptr;

QTime Settings::startTime() const
{
    return m_startTime;
}

void Settings::setStartTime(const QTime &startTime)
{
    m_startTime = startTime;
}

double Settings::lengthTime() const
{
    return m_lengthTime;
}

void Settings::setLengthTime(const double &lengthTime)
{
    m_lengthTime = lengthTime;
}

bool Settings::autoInit() const
{
    return m_autoInit;
}

void Settings::setAutoInit(bool autoInit)
{
    m_autoInit = autoInit;
}

int Settings::salary() const
{
    return m_salary;
}

void Settings::setSalary(int salary)
{
    m_salary = salary;
}

double Settings::tax() const
{
    return m_tax;
}

void Settings::setTax(double tax)
{
    m_tax = tax;
}

int Settings::monthTime() const
{
    return m_monthTime;
}

void Settings::setMonthTime(const int &monthTime)
{
    m_monthTime = monthTime;
}

ColorTableModel *Settings::colorTableModel()
{
    return m_colorTableModel;
}

Settings::Settings()
{
    m_colorTableModel = new ColorTableModel;
}

Settings::~Settings()
{
    delete m_colorTableModel;
}

Settings *Settings::Instance()
{
    if (!m_instance)
        m_instance = new Settings();
    return m_instance;
}

void Settings::load()
{
    QSettings set;
    set.beginGroup("Settings");
    m_autoInit = set.value("autoInit", false).toBool();
    if (m_autoInit)
        m_startTime = QTime::currentTime();
    else
        m_startTime = set.value("startTime", QTime::currentTime()).toTime();
    m_lengthTime = set.value("lengthTime", 6).toDouble();
    m_salary = set.value("salary", 0).toInt();
    m_tax = set.value("tax", 0).toDouble();
    m_monthTime = set.value("monthTime").toInt();
    int arLen = set.beginReadArray("colors");
    for(int i = 0 ; i < arLen; ++i)
    {
        set.setArrayIndex(i);
        m_colorTableModel->autoAt(i) = set.value("isAuto").toBool();
        m_colorTableModel->colorAt(i) = set.value("color").value<QColor>();
    }
    set.endArray();
    set.endGroup();
}

void Settings::save()
{
    QSettings set;
    set.beginGroup("Settings");
    set.setValue("autoInit", m_autoInit);
    set.setValue("startTime", m_startTime);
    set.setValue("lengthTime", m_lengthTime);
    set.setValue("salary", m_salary);
    set.setValue("tax", m_tax);
    set.setValue("monthTime", m_monthTime);
    set.beginWriteArray("colors", m_colorTableModel->colorSize());
    for(int i = 0 ; i < m_colorTableModel->colorSize(); ++i)
    {
        set.setArrayIndex(i);
        set.setValue("isAuto", m_colorTableModel->autoAt(i));
        set.setValue("color", m_colorTableModel->colorAt(i));
    }
    set.endArray();
    set.endGroup();
}
