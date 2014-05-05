#ifndef CWEBPAGE_H
#define CWEBPAGE_H

#include <QWebPage>

class CWebPage : public QWebPage
{
    Q_OBJECT

public:
    CWebPage(QObject *parent = 0);

protected:
    QString userAgentForUrl(const QUrl &url) const;
    bool acceptNavigationRequest(QWebFrame *frame, const QNetworkRequest &request, NavigationType type);

};

#endif // CWEBPAGE_H
