#include "mytableview.h"
#include <QPainter>
#include <QScrollBar>

MyTableView::MyTableView(QWidget *parent) :
    QTableView(parent)
{
    m_imageOpacity = 0.5;
    m_backgroundImage = QPixmap();
    m_verticalPadding = 0;
    m_horizontalPadding = 0;

    connect(horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(sliderMoved()));
}

void MyTableView::paintEvent(QPaintEvent *event)
{
    QTableView::paintEvent(event);

    if(m_backgroundImage.isNull()) {return;}

    QPainter painter(viewport());
    painter.setOpacity(m_imageOpacity);

    QImage img = m_backgroundImage.scaled(viewport()->size() - QSize(m_horizontalPadding * 2, m_verticalPadding * 2), Qt::KeepAspectRatio).toImage();
    painter.drawImage(m_horizontalPadding, viewport()->height() - img.height() - m_verticalPadding, img);
}

void MyTableView::sliderMoved()
{
    viewport()->update();
}

void MyTableView::setBackgroundOpacity(double value)
{
    m_imageOpacity = value;
    update();
}

double MyTableView::getBackGroundOpacity() const
{
    return m_imageOpacity;
}

void MyTableView::setBackgroundPixmap(QPixmap value)
{
    m_backgroundImage = value;
}

QPixmap MyTableView::getBackgroundPixmap() const
{
    return m_backgroundImage;
}

void MyTableView::setVerticalPadding(int value)
{
    m_verticalPadding = value;
}

int MyTableView::getVericalPadding() const
{
    return m_verticalPadding;
}

void MyTableView::setHorizontalPadding(int value)
{
    m_horizontalPadding = value;
}

int MyTableView::getHorizontalPadding() const
{
    return m_horizontalPadding;
}
