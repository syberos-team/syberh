#ifndef NAMEVALUEITEM_H
#define NAMEVALUEITEM_H


#include "environmentfwd.h"
#include <QStringList>
#include <QVariantList>
#include <QVector>

namespace Utils {

class NameValueItem
{
public:
    enum Operation : char { SetEnabled, Unset, Prepend, Append, SetDisabled };
    NameValueItem() = default;
    NameValueItem(const QString &key, const QString &value, Operation operation = SetEnabled)
        : name(key)
        , value(value)
        , operation(operation)
    {}

    void apply(NameValueDictionary *dictionary) const { apply(dictionary, operation); }

    static void sort(NameValueItems *list);
    static NameValueItems fromStringList(const QStringList &list);
    static QStringList toStringList(const NameValueItems &list);
    static NameValueItems itemsFromVariantList(const QVariantList &list);
    static QVariantList toVariantList(const NameValueItems &list);
    static NameValueItem itemFromVariantList(const QVariantList &list);
    static QVariantList toVariantList(const NameValueItem &item);

    friend bool operator==(const NameValueItem &first, const NameValueItem &second)
    {
        return first.operation == second.operation && first.name == second.name
               && first.value == second.value;
    }

    friend bool operator!=(const NameValueItem &first, const NameValueItem &second)
    {
        return !(first == second);
    }

public:
    QString name;
    QString value;
    Operation operation = Unset;

private:
    void apply(NameValueDictionary *dictionary, Operation op) const;
};

QDebug operator<<(QDebug debug, const NameValueItem &i);

} // namespace Utils


#endif // NAMEVALUEITEM_H
