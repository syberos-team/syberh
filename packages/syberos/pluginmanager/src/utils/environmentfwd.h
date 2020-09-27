#ifndef ENVIRONMENTFWD_H
#define ENVIRONMENTFWD_H

#include <QtGlobal>

QT_BEGIN_NAMESPACE
template<typename Type>
class QList;
class QTreeView;
QT_END_NAMESPACE

namespace Utils {
class NameValueDictionary;
class NameValueItem;
using NameValueItems = QVector<NameValueItem>;

class Environment;
using EnvironmentItem = NameValueItem;
using EnvironmentItems = NameValueItems;

class PreprocessorMacroDictionary;
using PreprocessorMacroItem = NameValueItem;
using PreprocessorMacroItems = NameValueItems;

class NameValueModel;
class EnvironmentModel;
} // namespace Utils


#endif // ENVIRONMENTFWD_H
