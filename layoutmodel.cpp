#include <QVectorIterator>
#include "layoutmodel.h"
#include "evdev-lst-layouts.h"

Layout::Layout(QString code, QString desc)
{
    m_code = code;
    m_desc = desc;
}

Layout::~Layout() { }

LayoutModel::LayoutModel(QObject *parent) : QAbstractListModel(parent)
{
    QStringList elements = QString(qgetenv("XKB_DEFAULT_LAYOUT")).split(',');
    foreach (QString element, elements) {
        for (int i = 0; i < ARRAY_SIZE(evdev_lst_layouts); ++i) {
            const struct layout *layout = &evdev_lst_layouts[i];
            if (element == QString(layout->code)) {
                addLayout(QString(layout->code), QString(layout->description));
            }
        }
    }
}

LayoutModel::~LayoutModel()
{
    QVectorIterator<QSharedPointer<Layout>> iter(m_layouts);
    while (iter.hasNext()) {
        qDebug() << iter.next().get()->code();
    }
}

int LayoutModel::rowCount(const QModelIndex &parent) const
{
    return m_layouts.size();
}

QVariant LayoutModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return {};
    }

    const int row = index.row();
    switch (role) {
    case Qt::DisplayRole:
        return m_layouts.at(row)->desc() + " [" + m_layouts.at(row)->code() + "]";
    }
    return {};
}

void LayoutModel::update(void)
{
    QModelIndex topLeft = createIndex(0, 0);
    emit dataChanged(topLeft, topLeft, { Qt::DisplayRole });
}

void LayoutModel::addLayout(QString code, QString desc)
{
    m_layouts.append(QSharedPointer<Layout>(new Layout(code, desc)));
    update();
}

void LayoutModel::deleteLayout(int index)
{
    if (index < 0 || index >= m_layouts.size()) {
        return;
    }
    m_layouts.remove(index);
    update();
}
