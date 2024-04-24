#pragma once
#include <QWidget>

QT_BEGIN_NAMESPACE
class QListView;
class QPushButton;
class QComboBox;
QT_END_NAMESPACE

class LayoutModel;

class Window : public QWidget
{
public:
    Window(QWidget *parent = nullptr);

private slots:
    void addSelectedLayout(void);
    void deleteSelectedLayout(void);

private:
    LayoutModel *m_model;
    QListView *m_view;
    QComboBox *m_combobox;
    QPushButton *m_add;
    QPushButton *m_delete;
};
