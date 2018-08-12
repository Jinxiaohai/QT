#include "wkbutton.h"
#include <QPainter>

WKButton::WKButton(QWidget *parent) :
    QWidget(parent)
{
    m_BorderRadius = 10;
    m_BorderWidth = 2;
    m_BorderColor = QColor(180, 180, 180);
    m_BGPressColor = QColor(80, 80, 80);
    m_BGReleaseColor = QColor(30, 30, 30);
    m_ColorModel = ColorMode_Normal;

    m_SubScriptText = QString("1");
    m_SubScriptAlign = TextAlign_Top_Left;

    m_ContentText = QString("中文测试MSCCreater");
    m_ContentAlign = TextAlign_Center_Center;

}

WKButton::~WKButton()
{
}

void WKButton::setBorderRadius(double radius)
{
    if(radius != m_BorderRadius)
    {
        m_BorderRadius = radius;
        update();
    }
}

void WKButton::setBorderWidth(double width)
{
    if(width != m_BorderWidth)
    {
        m_BorderWidth = width;
        update();
    }
}

void WKButton::SetBorderColor(QColor color)
{
    if(color != m_BorderColor)
    {
        m_BorderColor = color;
        update();
    }
}

void WKButton::SetBGPressColor(QColor color)
{
    if(color != m_BGPressColor)
    {
        m_BGPressColor = color;
        update();
    }
}

void WKButton::setBGReleaseColor(QColor color)
{
    if(color != m_BGReleaseColor)
    {
        m_BGReleaseColor = color;
        update();
    }
}

void WKButton::setColorModel(WKButton::ColorModel model)
{
    if(model != m_ColorModel)
    {
        m_ColorModel = model;
        update();
    }
}

void WKButton::setSubScriptText(QString str)
{
    m_SubScriptText = str;
    update();
}

void WKButton::setSubScriptColor(QColor color)
{
    if(color != m_SubScriptColor)
    {
        m_SubScriptColor = color;
        update();
    }
}

void WKButton::setSubScriptFont(QFont font)
{
    if(font != m_SubScriptFont)
    {
        m_SubScriptFont = font;
        update();
    }
}

void WKButton::setSubScriptAlign(WKButton::TextAlignModel align)
{
    if(align != m_SubScriptAlign)
    {
        m_SubScriptAlign = align;
        update();
    }
}

void WKButton::setContentText(QString str)
{
    m_ContentText = str;
    update();
}

void WKButton::setContentColor(QColor color)
{
    if(color != m_ContentColor)
    {
        m_ContentColor = color;
        update();
    }
}

void WKButton::setContentFont(QFont font)
{
    if(font != m_ContentFont)
    {
        m_ContentFont = font;
        update();
    }
}

void WKButton::setContentAlign(WKButton::TextAlignModel align)
{
    if(align != m_ContentAlign)
    {
        m_ContentAlign = align;
        update();
    }
}

void WKButton::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景
    drawBg(&painter);
    //绘制文字
    drawText(&painter);
}

void WKButton::drawBg(QPainter *painter)
{
    painter->save();

    //设置边框颜色及宽度
    QPen pen;
    pen.setColor(m_BorderColor);
    pen.setWidthF(m_BorderWidth);
    painter->setPen(pen);

    //绘制区域要减去边框宽度
    QRect rect;
    rect.setX(m_BorderWidth);
    rect.setY(m_BorderWidth);
    rect.setWidth(width() - m_BorderWidth * 2);
    rect.setHeight(height() - m_BorderWidth * 2);

    //如果背景图片存在则显示背景图片,否则显示背景色
    if (!m_BGImage.isNull()) {
        //等比例缩放绘制
        QPixmap img = m_BGImage.scaled(rect.width(), rect.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        painter->drawPixmap((this->rect().width() - img.width()) / 2, (this->rect().height() - img.height()) / 2, img);
    } else {
        if (m_ColorModel == ColorMode_Normal) {
            if (isPressed) {
                painter->setBrush(QBrush(m_BGPressColor));
            } else {
                painter->setBrush(QBrush(m_BGReleaseColor));
            }
        } else if (m_ColorModel == ColorMode_Replace) {
            QLinearGradient gradient(QPoint(0, 0), QPoint(0, height()));

            if (isPressed) {
                gradient.setColorAt(0.0, m_BGPressColor);
                gradient.setColorAt(0.49, m_BGPressColor);
                gradient.setColorAt(0.50, m_BGReleaseColor);
                gradient.setColorAt(1.0, m_BGReleaseColor);
            } else {
                gradient.setColorAt(0.0, m_BGReleaseColor);
                gradient.setColorAt(0.49, m_BGReleaseColor);
                gradient.setColorAt(0.50, m_BGPressColor);
                gradient.setColorAt(1.0, m_BGPressColor);
            }

            painter->setBrush(gradient);
        } else if (m_ColorModel == ColorMode_Shade) {
            QLinearGradient gradient(QPoint(0, 0), QPoint(0, height()));

            if (isPressed) {
                gradient.setColorAt(0.0, m_BGPressColor);
                gradient.setColorAt(1.0, m_BGReleaseColor);
            } else {
                gradient.setColorAt(0.0, m_BGReleaseColor);
                gradient.setColorAt(1.0, m_BGPressColor);
            }

            painter->setBrush(gradient);
        }

        painter->drawRoundedRect(rect, m_BorderRadius, m_BorderRadius);
    }

    painter->restore();
}

void WKButton::drawText(QPainter *painter)
{
    if (!m_BGImage.isNull()) {
        return;
    }

    painter->save();

    //如果要显示角标,则重新计算显示文字的区域
    if (!m_SubScriptText.isEmpty()) {
        int offset = 3;
        QRect rect;
        rect.setX(m_BorderWidth * offset);
        rect.setY(m_BorderWidth);
        rect.setWidth(width() - m_BorderWidth * offset * 2);
        rect.setHeight(height() - m_BorderWidth * 2);

        Qt::Alignment alignment = Qt::AlignCenter;
        if (m_SubScriptAlign == TextAlign_Top_Left) {
            alignment = Qt::AlignTop | Qt::AlignLeft;
        } else if (m_SubScriptAlign == TextAlign_Top_Center) {
            alignment = Qt::AlignTop | Qt::AlignHCenter;
        } else if (m_SubScriptAlign == TextAlign_Top_Right) {
            alignment = Qt::AlignTop | Qt::AlignRight;
        } else if (m_SubScriptAlign == TextAlign_Center_Left) {
            alignment = Qt::AlignLeft | Qt::AlignVCenter;
        } else if (m_SubScriptAlign == TextAlign_Center_Center) {
            alignment = Qt::AlignHCenter | Qt::AlignVCenter;
        } else if (m_SubScriptAlign == TextAlign_Center_Right) {
            alignment = Qt::AlignRight | Qt::AlignVCenter;
        } else if (m_SubScriptAlign == TextAlign_Bottom_Left) {
            alignment = Qt::AlignBottom | Qt::AlignLeft;
        } else if (m_SubScriptAlign == TextAlign_Bottom_Center) {
            alignment = Qt::AlignBottom | Qt::AlignHCenter;
        } else if (m_SubScriptAlign == TextAlign_Bottom_Right) {
            alignment = Qt::AlignBottom | Qt::AlignRight;
        }

        //绘制角标
        painter->setPen(m_SubScriptColor);
        painter->setFont(m_SubScriptFont);
        painter->drawText(rect, alignment, m_SubScriptText);
    }

    int offset = 5;
    QRect rect;
    rect.setX(m_BorderWidth * offset);
    rect.setY(m_BorderWidth);
    rect.setWidth(width() - m_BorderWidth * offset * 2);
    rect.setHeight(height() - m_BorderWidth * 2);

    Qt::Alignment alignment = Qt::AlignCenter;
    if (m_ContentAlign == TextAlign_Top_Left) {
        alignment = Qt::AlignTop | Qt::AlignLeft;
    } else if (m_ContentAlign == TextAlign_Top_Center) {
        alignment = Qt::AlignTop | Qt::AlignHCenter;
    } else if (m_ContentAlign == TextAlign_Top_Right) {
        alignment = Qt::AlignTop | Qt::AlignRight;
    } else if (m_ContentAlign == TextAlign_Center_Left) {
        alignment = Qt::AlignLeft | Qt::AlignVCenter;
    } else if (m_ContentAlign == TextAlign_Center_Center) {
        alignment = Qt::AlignHCenter | Qt::AlignVCenter;
    } else if (m_ContentAlign == TextAlign_Center_Right) {
        alignment = Qt::AlignRight | Qt::AlignVCenter;
    } else if (m_ContentAlign == TextAlign_Bottom_Left) {
        alignment = Qt::AlignBottom | Qt::AlignLeft;
    } else if (m_ContentAlign == TextAlign_Bottom_Center) {
        alignment = Qt::AlignBottom | Qt::AlignHCenter;
    } else if (m_ContentAlign == TextAlign_Bottom_Right) {
        alignment = Qt::AlignBottom | Qt::AlignRight;
    }

    painter->setPen(m_ContentColor);
    painter->setFont(m_ContentFont);
    painter->drawText(rect, alignment, m_ContentText);

    painter->restore();
}
