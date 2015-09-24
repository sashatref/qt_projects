#pragma once

#include <QTableView>
#include "../CustomWidgets_pch.h"

/*!
 * \brief TableView в котором реализована возможность задания картинки заднего фона
 */

class WIDGET_EXPORT MyTableView : public QTableView
{
    Q_OBJECT
    Q_PROPERTY(double backgroundOpacity READ getBackGroundOpacity WRITE setBackgroundOpacity)
    Q_PROPERTY(QPixmap backgroundPixmap READ getBackgroundPixmap WRITE setBackgroundPixmap)
    Q_PROPERTY(int verticalPadding READ getVericalPadding WRITE setVerticalPadding)
    Q_PROPERTY(int horizontalPadding READ getHorizontalPadding WRITE setHorizontalPadding)
public:

    /*!
     * \brief задает прозрачность фона
     * \param value значение необходимо задавать в интервале 0..1
     */
    void setBackgroundOpacity(double value);

    /*!
     * \brief получает значение прозрачности фона
     */
    double getBackGroundOpacity() const;

    /*!
     * \brief устанавливает изображение которое будет установлено фоном для таблицы
     */
    void setBackgroundPixmap(QPixmap value);

    /*!
     * \brief получает изображение которое установлено фоном для таблицы
     */
    QPixmap getBackgroundPixmap() const;

    /*!
     * \brief устанавливает оступ для фонового изображения от верхней и нижней границы таблицы
     * задается в пикселях
     */
    void setVerticalPadding(int value);

    /*!
     * \brief получает значение отступов для фонового изображения от верхней и нижней границы таблицы
     */
    int getVericalPadding() const;

    /*!
     * \brief устанавливает отступ для фонового изображение от левой и правой видимой части таблицы
     * задается в пикселях
     */
    void setHorizontalPadding(int value);

    /*!
     * \brief получает отспуп для фонового изображение от левой и правой видимой части таблицы
     */
    int getHorizontalPadding() const;

    MyTableView(QWidget *parent = 0);

protected:
    /*!
     * \brief реализована отрисовка фонового изображения с заданной прозрачностью и отступами
     */
    void paintEvent(QPaintEvent *event);
public slots:
    /*!
     * \brief принудительное обновление фонового изображения при скролинге таблицы
     */
    void sliderMoved();

private:
    QPixmap m_backgroundImage;
    double m_imageOpacity;
    int m_verticalPadding;
    int m_horizontalPadding;
};
