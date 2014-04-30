#include "popup.h"
#include "dialogbase.h"

#include <QUrl>
#include <QDesktopWidget>
#include <QApplication>
#include <QRect>
#include <QDebug>
#include <QWebView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QPropertyAnimation>
#include <QDesktopServices>


Popup::Popup(QObject *parent) :
    QObject(parent)
{
}

Popup::~Popup()
{
}

void Popup::showCentralPop(QWidget *parent, const QUrl &url)
{
    if(parent == NULL) {
        parent = new QWidget();
    }

    CentralPop *centralPop = new CentralPop(parent);
    centralPop->pop(url);
}

void Popup::showCornerPop(QWidget *parent, const QUrl &url)
{
    if (parent == NULL) {
        parent = new QWidget();
    }

    CornerPop *cornerPop = new CornerPop(parent);
    cornerPop->pop(url);
}


// class:: CentralPop
CentralPop::CentralPop(QWidget *parent) :
    DialogBase(parent)
{
    m_view = new QWebView(this->contentView);
    m_view->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);

    connect(m_view, SIGNAL(linkClicked(QUrl)), this, SLOT(openLink(QUrl)));
}

CentralPop::~CentralPop()
{
    delete m_view;
}

void CentralPop::pop(const QUrl &url)
{
    m_view->load(url);

    this->show();
    this->move((QApplication::desktop()->width() - this->width()) / 2,
               (QApplication::desktop()->height() - this->height()) / 2);

}

void CentralPop::openLink(const QUrl &url)
{
    QDesktopServices::openUrl(url);
}



// class: HintPop
CornerPop::CornerPop(QWidget *parent) :
    QWidget(parent),
    m_drag(false),
    m_popAnimation(0)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::ToolTip );

    m_popAnimation = new QPropertyAnimation(this, "geometry", this);

    m_closeBtn = new QPushButton(QString(""), this);
    m_closeBtn->setFlat(false);
    m_titleLbl = new QLabel(QString("News Notice"), this);
    m_titleLbl->setAlignment(Qt::AlignLeft | Qt::AlignBottom);

    QSpacerItem *topSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding);
    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->addWidget(m_titleLbl);
    topLayout->addSpacerItem(topSpacer);
    topLayout->addWidget(m_closeBtn);

    m_view = new QWebView(this);
    m_view->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);

    QVBoxLayout *wholeLayout = new QVBoxLayout(this);
    wholeLayout->addLayout(topLayout);
    wholeLayout->addWidget(m_view);

    this->resize(320, 200);

    // set stylesheet
    m_closeBtn->setObjectName("m_closeBtn");
    m_closeBtn->setStyleSheet("QPushButton#m_closeBtn{border-image:url(:/res/popCloseBtnNormal.png);width:11px; height:10px;} \
                              QPushButton#m_closeBtn:hover{border-image:url(:/res/popCloseBtnHover.png);width:11px; height:10px;}");
    m_titleLbl->setObjectName("m_titleLbl");
    m_titleLbl->setStyleSheet("QLabel {color: rgb(96, 96, 96); font-size: 14px; font-weight: bold}");

    // initial connect
    connect(m_closeBtn, SIGNAL(clicked()), this, SLOT(btnClicked()));
    connect(m_view, SIGNAL(linkClicked(QUrl)), this, SLOT(openLink(QUrl)));
}

CornerPop::~CornerPop()
{
    delete m_popAnimation;
    delete m_closeBtn;
    delete m_titleLbl;
    delete m_view;
}

void CornerPop::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        m_drag = true;
        m_position = e->globalPos() - this->pos();
        e->accept();
    }
}

void CornerPop::mouseMoveEvent(QMouseEvent *e)
{
    if (m_drag && (e->buttons() && Qt::LeftButton))
    {
        this->move(e->globalPos() - m_position);
        e->accept();
    }
}

void CornerPop::mouseReleaseEvent(QMouseEvent *e)
{
    m_drag = false;
}

void CornerPop::btnClicked()
{
    this->close();
}

void CornerPop::openLink(const QUrl &url)
{
    QDesktopServices::openUrl(url);
}

void CornerPop::pop(const QUrl &url)
{
    m_view->load(url);
    this->show();

    QRect rect = QApplication::desktop()->availableGeometry(-1);
    int x = rect.width() - this->width();

    if(!m_popAnimation)
    {
        m_popAnimation = new QPropertyAnimation(this, "geometry", this);
    }

    // set animation
    m_popAnimation->setDuration(1000);
    m_popAnimation->setStartValue(QRect(x, rect.height(), width(), height()));
    m_popAnimation->setEndValue(QRect(x, rect.height() - this->height(), width(), height()));
    m_popAnimation->start();
}
