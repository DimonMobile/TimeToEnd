#ifndef SETTINGS_H
#define SETTINGS_H

#include <QTime>
#include "colortablemodel.h"

class Settings
{
private:
    ColorTableModel *m_colorTableModel;
    QTime m_startTime;
    double m_lengthTime;
    bool  m_autoInit;
    int m_salary;
    double m_tax;
    int m_monthTime;
    static Settings *m_instance;
protected:
    Settings();
    ~Settings();
public:
    static Settings *Instance();
    void load();
    void save();
    QTime startTime() const;
    void setStartTime(const QTime &startTime);
    double lengthTime() const;
    void setLengthTime(const double &lengthTime);
    bool autoInit() const;
    void setAutoInit(bool autoInit);
    int salary() const;
    void setSalary(int salary);
    double tax() const;
    void setTax(double tax);
    int monthTime() const;
    void setMonthTime(const int &monthTime);
    ColorTableModel *colorTableModel();
};

#endif // SETTINGS_H
