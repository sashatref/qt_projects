#include "richlabel.h"

#include <QPainter>

RichLabel::RichLabel(QWidget *parent) :
    QLabel(parent),
    m_stretchText(true),
    m_margins(QSize(0,0))
{
}

void RichLabel::setStretchText(bool value)
{
    m_stretchText = value;
    update();
}

void RichLabel::setMargins(QSize value)
{
    m_margins = value;
    update();
}


void RichLabel::paintEvent(QPaintEvent *event)
{
    if(m_stretchText)
    {
        QPainter painter(this);
        QFont tempFont = painter.font();

        int i = 1;
        tempFont.setPixelSize(i);
        while(QFontMetrics(tempFont).width(text()) < width() - m_margins.width() && i < height() - m_margins.height())
        {
            i++;
            tempFont.setPixelSize(i);
        }
        painter.setFont(tempFont);

        painter.drawText(0,
                         0,
                         width(),
                         height(),
                         Qt::AlignHCenter | Qt::AlignVCenter,
                         text());
    } else
    {
        QLabel::paintEvent(event);
    }
}


