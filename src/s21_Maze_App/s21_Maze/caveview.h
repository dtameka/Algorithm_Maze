#ifndef CAVEVIEW_H
#define CAVEVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QGraphicsTextItem>
#include "s21_cave.h"


static const int cave_view_width_and_hight = 542;
static const int cave_text_hight = 40;
static const int cave_letter_width = 10;

class CaveView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit CaveView(QWidget *parent = nullptr);
    ~CaveView();

public slots:
    void DrawCave(s21::Cave *cave);

private:
    void deleteItemsFromGroup(QGraphicsItemGroup *group);
    void AddText(s21::Cave *cave);
    void AddBoders(void);
    void AddCave(s21::Cave *cave);
    QGraphicsScene      *scene;
    QGraphicsItemGroup  *group_1;
    QGraphicsItemGroup  *group_2;
    QGraphicsItemGroup  *group_3;



};

#endif // CAVEVIEW_H
