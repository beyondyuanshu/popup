#ifndef CWEBVIEW_H
#define CWEBVIEW_H

#include <QWebView>

class QMouseEvent;
class QPoint;

class CWebPage;
class CWebViewHandler;

class CWebView : public QWebView
{
    Q_OBJECT

public:
    CWebView(QWidget *parent = 0);

public:
    QWebPage::WebAction getUrlAction(const QUrl &url) const;

public:
    CWebViewHandler *mHandler;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    //void contextMenuEvent(QContextMenuEvent *event);

private:
    QPoint lastClickedPoint;

private slots:
    void clickedUrl(const QUrl &url);

};


class CWebPage : public QWebPage
{
    QString userAgentForUrl(const QUrl &url) const;
};


class CWebViewHandler
{
public:
    virtual bool mousePressEvent(CWebView *webview, QMouseEvent *event) = 0;
    virtual bool mouseReleaseEvent(CWebView *webview, QMouseEvent *event) = 0;
    virtual bool mouseMoveEvent(CWebView *webview, QMouseEvent *event) = 0;
};

#endif // CWEBVIEW_H
