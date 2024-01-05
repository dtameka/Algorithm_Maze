#ifndef MYGRAPHICVIEW_H
#define MYGRAPHICVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QGraphicsTextItem>
#include <QPixmap>
#include <QImage>
#include "s21_maze.h"

static const int maze_view_width_and_hight = 542;
static const int text_hight = 40;
static const int letter_width = 10;

class MazeView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MazeView(QWidget *parent = 0);
    ~MazeView();

public slots:
    void DrawMaze(s21::Maze *maze);

private:
    void deleteItemsFromGroup(QGraphicsItemGroup *group);
    void AddText(s21::Maze *maze);
    void AddBoders(void);
    void AddMaze(s21::Maze *maze);
    void AddPath(s21::Maze *maze);
    QGraphicsScene      *scene;
    QGraphicsItemGroup  *group_1;
    QGraphicsItemGroup  *group_2;
    QGraphicsItemGroup  *group_3;
    s21::Maze *my_maze_;

};

#endif // MYGRAPHICVIEW_H
