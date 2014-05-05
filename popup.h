#ifndef POPUP_H
#define POPUP_H

#include <QObject>
#include <QWidget>
#include <QMouseEvent>

class QLabel;
class QPushButton;
class QToolBar;
class QAction;
class QWebView;
class QPoint;
class QPropertyAnimation;

class Popup : public QObject
{
    Q_OBJECT
public:
    explicit Popup(QObject *parent = 0);
    ~Popup();

public:
    static void showCentralPop(QWidget *parent, const QUrl &url);
    static void showCornerPop(QWidget *parent, const QUrl &url);
};


// class: PopBase
class PopBase : public QWidget
{
    Q_OBJECT
public:
    explicit PopBase(QWidget *parent = 0);

public:
    void setTitle(const QString &title);
    void loadUrl(const QUrl &url);

public:
    QPushButton *m_closeBtn;
    QLabel *m_titleLbl;

public slots:
    void slot_btnClicked();
    void slot_navigation();
    virtual void slot_loadFinished(bool bOK);

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private:
    bool m_drag;
    QPoint m_position;

    QToolBar *m_navigationBar;
    QAction *m_goBackAction;
    QAction *m_goForwardAction;
    QAction *m_reloadAction;

    QWebView *m_webView;
    QPropertyAnimation *m_popAnimation;
    bool bUseAnimation;
};


// class: CentralPop
class CentralPop : public PopBase
{
    Q_OBJECT
public:
    explicit CentralPop(QWidget *parent = 0);
    ~CentralPop();

public:
    void pop(const QUrl &url);
};


// class: CorenerPop
class CornerPop : public PopBase
{
    Q_OBJECT
public:
    explicit CornerPop(QWidget *parent = 0);
    ~CornerPop();

public:
    void pop(const QUrl &url);

public slots:
    void slot_loadFinished(bool bOK);

private:
    QPropertyAnimation *m_popAnimation;
};

#endif // POPUP_H
