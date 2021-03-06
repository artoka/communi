/*
* Copyright (C) 2008-2011 J-P Nurmi jpnurmi@gmail.com
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*/

#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>
#include <QColor>
#include <QList>
#include <QSwipeGesture>

class TabWidget : public QTabWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor alertColor READ alertColor WRITE setAlertColor)
    Q_PROPERTY(QColor highlightColor READ highlightColor WRITE setHighlightColor)

public:
    TabWidget(QWidget* parent = 0);

    QColor alertColor() const;
    void setAlertColor(const QColor& color);

    QColor highlightColor() const;
    void setHighlightColor(const QColor& color);

    bool hasTabAlert(int index);
    void setTabAlert(int index, bool alert);

    bool hasTabHighlight(int index) const;
    void setTabHighlight(int index, bool highlight);

    void registerSwipeGestures(Qt::Orientation orientation);
    void unregisterSwipeGestures();

public slots:
    void moveToNextTab();
    void moveToPrevTab();
    void setTabBarVisible(bool visible);

signals:
    void newTabRequested();
    void alertStatusChanged(bool active);
    void highlightStatusChanged(bool active);

protected:
    bool event(QEvent* event);
    bool handleSwipeGesture(QSwipeGesture* gesture, QSwipeGesture::SwipeDirection direction);
    void tabInserted(int index);
    void tabRemoved(int index);

private slots:
    void tabChanged(int index);
    void alertTimeout();

private:
    struct TabWidgetData
    {
        int previous;
        QColor alertColor;
        QColor highlightColor;
        QList<int> alertIndexes;
        QList<int> highlightIndexes;
        Qt::Orientation swipeOrientation;
    } d;
};

#endif // TABWIDGET_H
