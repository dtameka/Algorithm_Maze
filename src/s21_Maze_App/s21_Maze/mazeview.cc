#include "mazeview.h"

MazeView::MazeView(QWidget *parent)
    : QGraphicsView(parent)
{
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setAlignment(Qt::AlignCenter);
    this->setSizePolicy(QSizePolicy::Preferred , QSizePolicy::Preferred);

    this->setMinimumHeight(maze_view_width_and_hight);
    this->setMinimumWidth(maze_view_width_and_hight);
    this->setMaximumHeight(maze_view_width_and_hight);
    this->setMaximumWidth(maze_view_width_and_hight);

    scene = new QGraphicsScene();
    this->setScene(scene);
    group_1 = new QGraphicsItemGroup();
    scene->addItem(group_1);
    group_2 = new QGraphicsItemGroup();
    scene->addItem(group_2);
    group_3 = new QGraphicsItemGroup();
    scene->addItem(group_3);
    scene->setBackgroundBrush(QColor(200, 200, 200, 255));
}

MazeView:: ~MazeView() {
    this->deleteItemsFromGroup(group_1);
    this->deleteItemsFromGroup(group_2);
}

void MazeView::deleteItemsFromGroup(QGraphicsItemGroup *group)
{
    foreach( QGraphicsItem *item, scene->items(group->boundingRect())) {
       if(item->group() == group ) {
          delete item;
       }
    }
}

void MazeView::DrawMaze(s21::Maze *maze) {
    this->deleteItemsFromGroup(group_1);
    this->deleteItemsFromGroup(group_2);
    this->deleteItemsFromGroup(group_3);
    scene->setBackgroundBrush(QColor(127, 127, 127, 255));
    scene->setSceneRect(0,0,maze_view_width_and_hight,maze_view_width_and_hight);
    QPen penBlack(Qt::black);
    QPen penRed(Qt::red);
    QPen penGreen(Qt::green);
    QPen penBlue(Qt::blue);
    penGreen.setWidth(2);
    penBlue.setWidth(2);
    AddText(maze);
    AddBoders();
    AddMaze(maze);
    AddPath(maze);
}

void MazeView::AddText(s21::Maze *maze) {
    float column_width = (float)(maze_view_width_and_hight - text_hight) / (float) maze->maze->columns_number;
    float row_hight = (float)(maze_view_width_and_hight - text_hight) / (float) maze->maze->rows_number;
    for (int i = 0; i < maze->maze->columns_number; ++i) {
        char number[3];
        sprintf(number, "%d", i + 1);
        number[2] = '\0';
        QGraphicsTextItem *text_1 = scene->addText((const char*)number);
        int shift = 0;
        if (i % 2 == 0 && maze->maze->columns_number > 20) shift = 12;
        text_1->setPos(text_hight - letter_width +(int) (column_width * ((float)i + 0.5)), shift);
        group_3->addToGroup(text_1);
    }
    for (int i = 0; i < maze->maze->rows_number; ++i) {
        char number[3];
        sprintf(number, "%d", i + 1);
        number[2] = '\0';
        QGraphicsTextItem *text_1 = scene->addText((const char*)number);
        text_1->setPos(0 ,text_hight - letter_width + (int) (row_hight * ((float)i + 0.5)));
        group_3->addToGroup(text_1);
    }
}

void MazeView::AddBoders(void) {
    QPen penBlack(Qt::black);
    penBlack.setWidth(2);
    int max_width_and_hight =  maze_view_width_and_hight - 3;
    group_1->addToGroup(scene->addLine(text_hight, text_hight, text_hight, max_width_and_hight, penBlack));
    group_1->addToGroup(scene->addLine(text_hight, text_hight, max_width_and_hight, text_hight, penBlack));
    group_1->addToGroup(scene->addLine(max_width_and_hight, text_hight, max_width_and_hight, max_width_and_hight, penBlack));
    group_1->addToGroup(scene->addLine(text_hight, max_width_and_hight, max_width_and_hight, max_width_and_hight, penBlack));
}

void MazeView::AddMaze(s21::Maze *maze) {
    QPen penBlack(Qt::black);
    penBlack.setWidth(2);
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    float column_width = (float)(maze_view_width_and_hight - text_hight) / (float)maze->maze->columns_number;
    float row_hight = (float)(maze_view_width_and_hight - text_hight) / (float)maze->maze->rows_number;
    for (int i = 0; i < maze->maze->rows_number; i++) {
        for (int j = 0; j < maze->maze->columns_number; j++) {
            if (maze->maze->rows_right_boder[i][j] == 1) {
                x1 = text_hight + (int)((float)(j + 1) * column_width);
                y1 = text_hight + (int)((float)i * row_hight);
                x2 = text_hight + (int)((float)(j + 1) * column_width);
                y2 = text_hight + (int)((float)(i + 1) * row_hight);
                group_1->addToGroup(scene->addLine(x1, y1, x2, y2, penBlack));
            }
            if (maze->maze->columns_bottom_boder[i][j] == 1) {
                x1 = text_hight + (int)((float)j * column_width);
                y1 = text_hight + (int)((float)(i + 1) * row_hight);
                x2 = text_hight + (int)((float)(j + 1) * column_width);
                y2 = text_hight + (int)((float)(i + 1) * row_hight);
                group_1->addToGroup(scene->addLine( x1, y1, x2, y2, penBlack));
            }
        }
    }
}

void MazeView::AddPath(s21::Maze *maze) {
    QPen penRed(Qt::red);
    QPen penGreen(Qt::green);
    penGreen.setWidth(3);
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    float column_width = (float)(maze_view_width_and_hight - text_hight) / (float)maze->maze->columns_number;
    float row_hight = (float)(maze_view_width_and_hight - text_hight) / (float)maze->maze->rows_number;
   for (int i = 0; i < maze->maze->answer_lenth - 1; ++i) {
        x1 = text_hight + (int)((float)(maze->maze->answer[i][0] + 0.5) * column_width);
        y1 = text_hight + (int)((float)(maze->maze->answer[i][1] + 0.5) * row_hight);
        x2 = text_hight + (int)((float)(maze->maze->answer[i + 1][0] + 0.5) * column_width);
        y2 = text_hight + (int)((float)(maze->maze->answer[i + 1][1] + 0.5) * row_hight);
        group_2->addToGroup(scene->addLine( x1, y1, x2, y2, penGreen));
    }
}








