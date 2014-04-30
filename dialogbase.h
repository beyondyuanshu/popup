#ifndef DIALOGBASE_H
#define DIALOGBASE_H

#include <QWidget>
#include <QMouseEvent>

class QLabel;
class QPushButton;

class DialogBase : public QWidget
{
    Q_OBJECT
public:
    explicit DialogBase(QWidget *parent = 0);

signals:

public:
    void setTitle(const QString &title);

public:
    QPushButton *m_closeBtn;
    QLabel *m_titleLbl;
    QWidget *contentView;

public slots:
    void btnClicked();

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private:
    bool m_drag;
    QPoint m_position;


};

#endif // DIALOGBASE_H
