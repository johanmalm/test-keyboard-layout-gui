#include <QComboBox>
#include <QDebug>
#include <QPushButton>
#include <QtWidgets>
#include "evdev-lst-layouts.h"
#include "window.h"
#include "layoutmodel.h"

Window::Window(QWidget *parent) : QWidget(parent)
{
    m_model = new LayoutModel(this);
    m_view = new QListView;
    m_view->setModel(m_model);

    m_combobox = new QComboBox(this);
    m_add = new QPushButton("Add", this);
    m_delete = new QPushButton("Delete", this);

    auto *layout = new QVBoxLayout(this);
    layout->addWidget(m_view);
    layout->addWidget(m_combobox);
    layout->addWidget(m_add);
    layout->addWidget(m_delete);

    connect(m_add, &QPushButton::pressed, this, &Window::addSelectedLayout);
    connect(m_delete, &QPushButton::pressed, this, &Window::deleteSelectedLayout);

    for (int i = 0; i < ARRAY_SIZE(evdev_lst_layouts); ++i) {
        const struct layout *layout = &evdev_lst_layouts[i];
        m_combobox->addItem(QString(layout->description));
    }
}

void Window::addSelectedLayout(void)
{
    const char *description = m_combobox->currentText().toLatin1().data();
    for (int i = 0; i < ARRAY_SIZE(evdev_lst_layouts); ++i) {
        const struct layout *layout = &evdev_lst_layouts[i];
        if (!strcmp(description, layout->description)) {
            m_model->addLayout(QString(layout->code), QString(layout->description));
        }
    }
}

void Window::deleteSelectedLayout(void)
{
    m_model->deleteLayout(m_view->currentIndex().row());
}
