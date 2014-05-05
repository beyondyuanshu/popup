#include "cwebpage.h"
#include <cwebview.h>

#include <QDebug>
#include <QNetworkRequest>
#include <QWebElement>
#include <QWebFrame>
#include <QDesktopServices>

CWebPage::CWebPage(QObject *parent)
    : QWebPage(parent)
{
}

QString CWebPage::userAgentForUrl(const QUrl &url) const
{
    return "Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; Trident/5.0)";
}

bool CWebPage::acceptNavigationRequest(QWebFrame *frame, const QNetworkRequest &request, NavigationType type)
{
   return QWebPage::acceptNavigationRequest(frame, request, type);
}


