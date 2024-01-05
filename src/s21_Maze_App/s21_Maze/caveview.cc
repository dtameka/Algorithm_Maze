#include "caveview.h"

CaveView::CaveView(QWidget *parent) :
    QGraphicsView(parent)
{
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setAlignment(Qt::AlignCenter);
    this->setSizePolicy(QSizePolicy::Preferred , QSizePolicy::Preferred);

    this->setMinimumHeight(cave_view_width_and_hight);
    this->setMinimumWidth(cave_view_width_and_hight);
    this->setMaximumHeight(cave_view_width_and_hight);
    this->setMaximumWidth(cave_view_width_and_hight);

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

CaveView::~CaveView()
{

}

void CaveView::deleteItemsFromGroup(QGraphicsItemGroup *group)
{
    foreach( QGraphicsItem *item, scene->items(group->boundingRect())) {
       if(item->group() == group ) {
          delete item;
       }
    }
}

void CaveView::DrawCave(s21::Cave *cave)
{
        this->deleteItemsFromGroup(group_1);
        this->deleteItemsFromGroup(group_2);
        this->deleteItemsFromGroup(group_3);
        scene->setBackgroundBrush(QColor(127, 127, 127, 255));
        scene->setSceneRect(0,0,cave_view_width_and_hight,cave_view_width_and_hight);
        QPen penBlack(Qt::black);
        QPen penRed(Qt::red);
        QPen penGreen(Qt::green);
        QPen penBlue(Qt::blue);
        penGreen.setWidth(2);
        penBlue.setWidth(2);
        AddText(cave);
        AddBoders();
        AddCave(cave);
}

void CaveView::AddText(s21::Cave *cave) {
    float column_width = (float)(cave_view_width_and_hight - cave_text_hight) / (float) cave->cave->columns_number;
    float row_hight = (float)(cave_view_width_and_hight - cave_text_hight) / (float) cave->cave->rows_number;
    for (int i = 0; i < cave->cave->columns_number; ++i) {
        char number[3];
        sprintf(number, "%d", i + 1);
        number[2] = '\0';
        QGraphicsTextItem *text_1 = scene->addText((const char*)number);
        int shift = 0;
        if (i % 2 == 0 && cave->cave->columns_number > 20) shift = 12;
        text_1->setPos(cave_text_hight - cave_letter_width +(int) (column_width * ((float)i + 0.5)), shift);
        group_3->addToGroup(text_1);
    }
    for (int i = 0; i < cave->cave->rows_number; ++i) {
        char number[3];
        sprintf(number, "%d", i + 1);
        number[2] = '\0';
        QGraphicsTextItem *text_1 = scene->addText((const char*)number);
        text_1->setPos(0 ,cave_text_hight - cave_letter_width + (int) (row_hight * ((float)i + 0.5)));
        group_3->addToGroup(text_1);
    }
}

void CaveView::AddBoders(void) {
    QPen penBlack(Qt::black);
    penBlack.setWidth(2);
    int max_width_and_hight =  cave_view_width_and_hight - 3;
    group_1->addToGroup(scene->addLine(cave_text_hight, cave_text_hight, cave_text_hight, max_width_and_hight, penBlack));
    group_1->addToGroup(scene->addLine(cave_text_hight, cave_text_hight, max_width_and_hight, cave_text_hight, penBlack));
    group_1->addToGroup(scene->addLine(max_width_and_hight, cave_text_hight, max_width_and_hight, max_width_and_hight, penBlack));
    group_1->addToGroup(scene->addLine(cave_text_hight, max_width_and_hight, max_width_and_hight, max_width_and_hight, penBlack));
}


void CaveView::AddCave(s21::Cave *cave) {
    QPen penBlack(Qt::black);
    QBrush brushBlack(Qt::black);
    penBlack.setWidth(2);
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0, x3 = 0, y3 = 0, x4 = 0, y4 = 0;
    float column_width = (float)(cave_view_width_and_hight - cave_text_hight) / (float)cave->cave->columns_number;
    float row_hight = (float)(cave_view_width_and_hight - cave_text_hight) / (float)cave->cave->rows_number;
    for (int i = 0; i < cave->cave->rows_number; i++) {
        for (int j = 0; j < cave->cave->columns_number; j++) {
            if (cave->cave->current_state[i][j] == 0) {
                x1 = cave_text_hight + (int)((float)j * column_width);
                y1 = cave_text_hight + (int)((float)i * row_hight);

                x2 = cave_text_hight + (int)((float)(j) * column_width);
                y2 = cave_text_hight + (int)((float)(i + 1) * row_hight);

                x3 = cave_text_hight + (int)((float)(j + 1) * column_width);
                y3 = cave_text_hight + (int)((float)(i + 1) * row_hight);

                x4 = cave_text_hight + (int)((float)(j + 1) * column_width);
                y4 = cave_text_hight + (int)((float)i * row_hight);
                QPolygonF polly;
                polly << QPointF(x1, y1) << QPointF(x2, y2) << QPointF(x3, y3) << QPointF(x4, y4);
                group_1->addToGroup(scene->addPolygon(polly, penBlack, brushBlack));
            }
        }
    }
}
