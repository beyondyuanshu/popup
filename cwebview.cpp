#include "cwebview.h"

#include <QMouseEvent>
#include <QWebElement>
#include <QWebHitTestResult>
#include <QAction>
#include <QDesktopServices>
#include <QDebug>

CWebView::CWebView(QWidget *parent)
    : QWebView(parent),
      mHandler(NULL)
{
    setAcceptDrops(false);
    setPage(new CWebPage());

    connect(this, SIGNAL(linkClicked(const QUrl &)), this, SLOT(clickedUrl(const QUrl &)));
}

void CWebView::mousePressEvent(QMouseEvent *event)
{
    if (mHandler != NULL)
    {
        if (mHandler->mousePressEvent(this, event))
            return;
    }
    lastClickedPoint = event->pos();
    QWebView::mousePressEvent(event);
}

void CWebView::mouseMoveEvent(QMouseEvent *event) {
    if(mHandler != NULL)
    {
        if(mHandler->mouseMoveEvent(this, event))
        {
            return;
        }
    }
    QWebView::mouseMoveEvent(event);
}

void CWebView::mouseReleaseEvent(QMouseEvent *event) {
    if(mHandler != NULL)
    {
        if(mHandler->mouseReleaseEvent(this, event))
        {
            return;
        }
    }
    lastClickedPoint = event->pos();
    QWebView::mouseReleaseEvent(event);
}

QWebPage::WebAction CWebView::getUrlAction(const QUrl &url) const
{
    QWebElement elem = this->page()->mainFrame()->hitTestContent(lastClickedPoint).linkElement();
    qDebug() << elem.toOuterXml();
    if(elem.attribute("target") == "_blank")
    {
        qDebug() << "_blank";
        return QWebPage::OpenLinkInNewWindow;
    }

    return QWebPage::OpenLink;
}

void CWebView::clickedUrl(const QUrl &url)
{
    qDebug() << url;
    if (QWebPage::OpenLink == getUrlAction(url))
    {
        QDesktopServices::openUrl(url);
    }
    else if (QWebPage::OpenLinkInNewWindow == getUrlAction(url))
    {
        // do sth.
        this->load(url);

    }
}


// CWebPage
QString CWebPage::userAgentForUrl(const QUrl &url) const
{
    return "Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; Trident/5.0)";
}
