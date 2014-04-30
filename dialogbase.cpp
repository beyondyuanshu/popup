#include "dialogbase.h"

#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QSpacerItem>

DialogBase::DialogBase(QWidget *parent) :
    QWidget(parent),
    m_drag(false)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Window | Qt::ToolTip);
    //this->setAttribute(Qt::WA_TranslucentBackground);

    m_closeBtn = new QPushButton(QString(""), this);
//    m_closeBtn->setFlat(true);
    m_titleLbl = new QLabel(QString("News..."), this);
    m_titleLbl->setAlignment(Qt::AlignLeft | Qt::AlignBottom);

    QSpacerItem *topSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding);
    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->addWidget(m_titleLbl);
    topLayout->addSpacerItem(topSpacer);
    topLayout->addWidget(m_closeBtn);

    contentView = new QWidget(this);
    QGridLayout *viewLayout = new QGridLayout();
    viewLayout->addWidget(contentView);

    QVBoxLayout *wholeLayout = new QVBoxLayout(this);
    wholeLayout->addLayout(topLayout);
    wholeLayout->addLayout(viewLayout);

    this->resize(600, 400);

    // set sytle
    m_closeBtn->setObjectName("m_closeBtn");
    m_closeBtn->setStyleSheet("QPushButton#m_closeBtn{border-image:url(:/res/popCloseBtnNormal.png);width:15px; height:13px;} \
                              QPushButton#m_closeBtn:hover{border-image:url(:/res/popCloseBtnHover.png);width:15px; height:13px;}");
    m_titleLbl->setObjectName("m_titleLbl");
    m_titleLbl->setStyleSheet("QLabel {color: rgb(96, 96, 96); font-size: 14px; font-weight: bold}");

    connect(m_closeBtn, SIGNAL(clicked()), this, SLOT(close()));
}

void DialogBase::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        m_drag = true;
        m_position = e->globalPos() - this->pos();
        e->accept();
    }
}

void DialogBase::mouseMoveEvent(QMouseEvent *e)
{
    if (m_drag && (e->buttons() && Qt::LeftButton))
    {
        this->move(e->globalPos() - m_position);
        e->accept();
    }
}

void DialogBase::mouseReleaseEvent(QMouseEvent *e)
{
    m_drag = false;
}

void DialogBase::setTitle(const QString &title)
{
    m_titleLbl->setText(title);
}

void DialogBase::btnClicked()
{
    this->close();
}
