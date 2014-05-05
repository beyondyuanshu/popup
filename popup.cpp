#include "popup.h"
#include "cwebview.h"

#include <QLabel>
#include <QToolBar>
#include <QRect>
#include <QPoint>
#include <QWebFrame>
#include <QWebPage>
#include <QWebView>
#include <QAction>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QApplication>
#include <QPropertyAnimation>
#include <QUrl>
#include <QDesktopWidget>
#include <QDesktopServices>
#include <QDebug>

Popup::Popup(QObject *parent) :
    QObject(parent)
{
}

Popup::~Popup()
{
}

void Popup::showCentralPop(QWidget *parent, const QUrl &url)
{
    CentralPop *centralPop = new CentralPop(parent);
    centralPop->pop(url);
}

void Popup::showCornerPop(QWidget *parent, const QUrl &url)
{
    CornerPop *cornerPop = new CornerPop(parent);
    cornerPop->pop(url);
}


// class: PopBase
PopBase::PopBase(QWidget *parent) :
    QWidget(parent),
    m_drag(false),
    m_navigationBar(0),
    m_goBackAction(0),
    m_goForwardAction(0),
    m_reloadAction(0),
    m_webView(0),
    m_popAnimation(0),
    bUseAnimation(false)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Window | Qt::ToolTip);
    //this->setContextMenuPolicy(Qt::NoContextMenu);

    m_closeBtn = new QPushButton(QString(""), this);
    m_titleLbl = new QLabel(QString("News..."), this);
    m_titleLbl->setAlignment(Qt::AlignLeft | Qt::AlignBottom);

    connect(m_closeBtn, SIGNAL(clicked()), this, SLOT(close()));

    QSpacerItem *topSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding);
    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->addWidget(m_titleLbl);
    topLayout->addSpacerItem(topSpacer);
    topLayout->addWidget(m_closeBtn);

    m_goBackAction = new QAction(this);
    m_goBackAction->setIcon(QIcon(QLatin1String(":/res/arrow_left_green_1.png")));
    connect(m_goBackAction, SIGNAL(triggered()), this, SLOT(slot_navigation()));

    m_goForwardAction = new QAction(this);
    m_goForwardAction->setIcon(QIcon(QLatin1String(":/res/arrow_right_green_1.png")));
    connect(m_goForwardAction, SIGNAL(triggered()), this, SLOT(slot_navigation()));

    m_reloadAction = new QAction(this);
    m_reloadAction->setIcon(QIcon(QLatin1String(":/res/nav_refresh_green.png")));
    connect(m_reloadAction, SIGNAL(triggered()), this, SLOT(slot_navigation()));

    m_navigationBar = new QToolBar(this);
    m_navigationBar->addAction(m_goBackAction);
    m_navigationBar->addAction(m_goForwardAction);
    m_navigationBar->addAction(m_reloadAction);

    m_webView = new CWebView(this);
    m_webView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    connect(m_webView, SIGNAL(loadFinished(bool)), this, SLOT(slot_loadFinished(bool)));

    QVBoxLayout *wholeLayout = new QVBoxLayout(this);
    wholeLayout->setMargin(4);
    wholeLayout->addLayout(topLayout);
    wholeLayout->addWidget(m_navigationBar);
    wholeLayout->addWidget(m_webView);

    this->resize(600, 400);

    // set sytle
    m_closeBtn->setObjectName("m_closeBtn");
    m_closeBtn->setStyleSheet("QPushButton#m_closeBtn{border-image:url(:/res/popCloseBtnNormal.png);width:15px; height:13px;} \
                              QPushButton#m_closeBtn:hover{border-image:url(:/res/popCloseBtnHover.png);width:15px; height:13px;}");
                              m_titleLbl->setObjectName("m_titleLbl");
            m_titleLbl->setStyleSheet("QLabel {color: rgb(96, 96, 96); font-size: 14px; font-weight: bold}");
}

void PopBase::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        m_drag = true;
        m_position = e->globalPos() - this->pos();
        e->accept();
    }
}

void PopBase::mouseMoveEvent(QMouseEvent *e)
{
    if (m_drag && (e->buttons() && Qt::LeftButton))
    {
        this->move(e->globalPos() - m_position);
        e->accept();
    }
}

void PopBase::mouseReleaseEvent(QMouseEvent *e)
{
    m_drag = false;
}

void PopBase::setTitle(const QString &title)
{
    m_titleLbl->setText(title);
}

void PopBase::slot_btnClicked()
{
    this->close();
}

void PopBase::slot_navigation()
{
    QAction *action = dynamic_cast<QAction *>(sender());

    if (NULL == action)
    {
        return;
    }
    if (m_goBackAction == action)
    {
        this->m_webView->back();
    }
    else if (m_goForwardAction == action)
    {
        this->m_webView->forward();
    }
    else if (m_reloadAction == action)
    {
        this->m_webView->reload();
    }
}

void PopBase::slot_loadFinished(bool bOK)
{
    if (bOK)
    {
        this->show();
    }
    else
    {
        qDebug() << "Url loade error!";
    }
}

void PopBase::loadUrl(const QUrl &url)
{
    m_webView->load(url);
}


// class: CentralPop
CentralPop::CentralPop(QWidget *parent) :
    PopBase(parent)
{
}

CentralPop::~CentralPop()
{
}

void CentralPop::pop(const QUrl &url)
{
    loadUrl(url);
    this->move((QApplication::desktop()->width() - this->width()) / 2,
               (QApplication::desktop()->height() - this->height()) / 2);
}


// class: CornerPop
CornerPop::CornerPop(QWidget *parent) :
    PopBase(parent),
    m_popAnimation(0)
{
    m_popAnimation = new QPropertyAnimation(this, "geometry", this);
    this->resize(320, 200);
}

CornerPop::~CornerPop()
{
}

void CornerPop::pop(const QUrl &url)
{
    loadUrl(url);
}

void CornerPop::slot_loadFinished(bool bOK)
{
    if (bOK)
    {
        QRect rect = QApplication::desktop()->availableGeometry(-1);
        int x = rect.width() - this->width();

        if(!m_popAnimation)
        {
            m_popAnimation = new QPropertyAnimation(this, "geometry", this);
        }

        this->show();
        // set animation
        m_popAnimation->setDuration(1000);
        m_popAnimation->setStartValue(QRect(x, rect.height(), width(), height()));
        m_popAnimation->setEndValue(QRect(x, rect.height() - this->height(), width(), height()));
        m_popAnimation->start();
    }
    else
    {
        qDebug() << "Url error!";
    }
}
