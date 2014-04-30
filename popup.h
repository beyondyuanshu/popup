#ifndef POPUP_H
#define POPUP_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QWebView>
#include <QPushButton>
#include <QLabel>
#include <QPoint>
#include "dialogbase.h"

class DialogBase;
class QPropertyAnimation;

class Popup : public QObject
{
    Q_OBJECT
public:
    explicit Popup(QObject *parent = 0);
    ~Popup();

signals:

public:
    static void showCentralPop(QWidget *parent, const QUrl &url);
    static void showCornerPop(QWidget *parent, const QUrl &url);

public slots:

private:

};


// class:: CentralPop
class CentralPop : public DialogBase
{
    Q_OBJECT
public:
    explicit CentralPop(QWidget *parent = 0);
    ~CentralPop();

signals:

public:
    void pop(const QUrl &url);

public slots:
    void openLink(const QUrl &url);

private:
    QWebView *m_view;


};



// class:: CorenerPop
class CornerPop : public QWidget
{
    Q_OBJECT
public:
    explicit CornerPop(QWidget *parent = 0);
    ~CornerPop();

signals:

public:
    void pop(const QUrl &url);

public slots:
    void btnClicked();
    void openLink(const QUrl &url);

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private:
    bool m_drag;
    QPoint m_position;

    QPropertyAnimation *m_popAnimation;

    QWebView *m_view;

    QPushButton *m_closeBtn;
    QLabel *m_titleLbl;
};

#endif // POPUP_H
