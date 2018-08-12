#ifndef WKBUTTON_H
#define WKBUTTON_H

#include <QWidget>

#ifdef MSC
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif
class QDESIGNER_WIDGET_EXPORT WKButton: public QWidget
#else
class WKButton : public QWidget
#endif
{
    Q_OBJECT


//    Q_PROPERTY(double BorderRadius READ getBorderRadius WRITE setBorderRadius)
//    Q_PROPERTY(double BorderWidth READ getBorderWidth WRITE setBorderWidth)
//    Q_PROPERTY(QColor BorderColor READ getBorderColor WRITE setBorderColor)
//    Q_PROPERTY(QColor BGPressColor READ getBGPressColor WRITE setBGPressColor)
//    Q_PROPERTY(QColor BGReleaseColor READ getBGReleaseColor WRITE setBGReleaseColor)
//    Q_PROPERTY(WKButton::ColorModel BGColorModel READ getColorModel WRITE setBGColorModel)
//    Q_PROPERTY(QString SubScriptText READ getSubScriptText WRITE setSubScriptText)
//    Q_PROPERTY(QColor SubScriptColor READ getSubScriptColor WRITE setSubScriptColor)
//    Q_PROPERTY(QFont SubScriptFont READ getSubScriptFont WRITE setSubScriptFont)
//    Q_PROPERTY(WKButton::TextAlignModel SubScriptAlign READ getSubScriptAlign WRITE setSubScriptAlign)
//    Q_PROPERTY(QString ContentText READ getContentText WRITE setContentText)
//    Q_PROPERTY(QColor ContentColor READ getContentColor WRITE setContentColor)
//    Q_PROPERTY(QFont ContentFont READ getContentFont WRITE setContentFont)
//    Q_PROPERTY(WKButton::TextAlignModel ContentAlign READ getContentAlign WRITE setContentAlign)

public:
    explicit WKButton(QWidget *parent = 0);
    ~WKButton();

    //颜色显示类型
    enum ColorModel
    {
        ColorMode_Normal,//松开状态的颜色为RColor；按下状态的颜色为PColor
        ColorMode_Replace,//松开状态的颜色为按键上半部分是RColor，按键下半部分为PColor；按下状态的颜色为按键上半部分是PColor，按键下半部分为RColor
        ColorMode_Shade,//松开状态的颜色为RColor到PColor的渐变色；按下状态的颜色为按键上半部分是PColor到RColor的渐变色
    };
    Q_ENUM(ColorModel)
    //文本对其类型
    enum TextAlignModel
    {
        TextAlign_Top_Left,
        TextAlign_Top_Center,
        TextAlign_Top_Right,
        TextAlign_Center_Left,
        TextAlign_Center_Center,
        TextAlign_Center_Right,
        TextAlign_Bottom_Left,
        TextAlign_Bottom_Center,
        TextAlign_Bottom_Right,
    };
    Q_ENUM(TextAlignModel)


    double getBorderRadius() const { return m_BorderRadius; }
    void setBorderRadius(double radius);
    double getBorderWidth() const { return m_BorderWidth; }
    void setBorderWidth(double width);
    QColor getBorderColor() const { return m_BorderColor; }
    void SetBorderColor(QColor color);
    QColor getBGPressColor() const { return m_BGPressColor; }
    void SetBGPressColor(QColor color);
    QColor getBGReleaseColor() const { return m_BGReleaseColor; }
    void setBGReleaseColor(QColor color);
    ColorModel getColorModel() const{ return m_ColorModel; }
    void setColorModel(ColorModel model);
    QString getSubScriptText() const { return m_SubScriptText; }
    void setSubScriptText(QString str);
    QColor getSubScriptColor() const { return m_SubScriptColor; }
    void setSubScriptColor(QColor color);
    QFont getSubScriptFont() const { return m_SubScriptFont; }
    void setSubScriptFont(QFont font);
    TextAlignModel getSubScriptAlign() const { return m_SubScriptAlign; }
    void setSubScriptAlign(TextAlignModel align);
    QString getContentText() const { return m_ContentText; }
    void setContentText(QString str);
    QColor getContentColor() const { return m_ContentColor; }
    void setContentColor(QColor color);
    QFont getContentFont() const { return m_ContentFont; }
    void setContentFont(QFont font);
    TextAlignModel getContentAlign() const { return m_ContentAlign; }
    void setContentAlign(TextAlignModel align);

signals:

public slots:

protected:
    virtual void paintEvent(QPaintEvent *);
    void drawBg(QPainter* painter);
    void drawText(QPainter* painter);

    virtual QSize minimumSizeHint() const { return QSize(32,32); }

private:
    double m_BorderRadius;
    double m_BorderWidth;
    QColor m_BorderColor;
    QColor m_BGPressColor;
    QColor m_BGReleaseColor;
    ColorModel m_ColorModel;
    QString m_SubScriptText;
    QColor m_SubScriptColor;
    QFont m_SubScriptFont;
    TextAlignModel m_SubScriptAlign;
    QString m_ContentText;
    QColor m_ContentColor;
    QFont m_ContentFont;
    TextAlignModel m_ContentAlign;
    QPixmap m_BGImage;

    bool isPressed;
};

#endif // WKBUTTON_H
