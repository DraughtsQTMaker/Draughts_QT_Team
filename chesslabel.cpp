#include "chesslabel.h"

ChessLabel::ChessLabel(QWidget *parent):
    QLabel(parent)
{
    this->dormant = false;  //默认情况下该棋子标签不是合法棋位
    this->chessType = 0;    //默认情况下该棋子标签上并不存储棋子
}

ChessLabel::~ChessLabel(){

}

//Get Set 方法
void ChessLabel::setChessType(int type){
    this->chessType = type;
}
int ChessLabel::getChessType(){
    return this->chessType;
}


void ChessLabel::setDormant(){
    this->dormant = true;
}
bool ChessLabel::isDormant(){
    return this->dormant;
}

void ChessLabel::setPosition(int rowNumber, int colNumber){
    this->rowNumber = rowNumber;
    this->colNumber = colNumber;
}

QPair<int,int> ChessLabel::getPosition(){
    QPair<int,int> position;
    position.first = this->rowNumber;
    position.second = this->colNumber;
    return position;
}


//鼠标事件操作
void ChessLabel::mousePressEvent(QMouseEvent *){

    if(this->chessType == 1)
        this->setStyleSheet("image:url("+chessImageFileNames[1]+")");
    else if(this->chessType == 2)
        this->setStyleSheet("image:url("+chessImageFileNames[3]+")");
    else if(this->chessType == -1)
        this->setStyleSheet("image:url("+chessImageFileNames[5]+")");
    else if(this->chessType == -2)
        this->setStyleSheet("image:url("+chessImageFileNames[7]+")");
    else{
        this->setStyleSheet("image:url("+chessImageFileNames[8]+")");
    }
}


void ChessLabel::mouseReleaseEvent(QMouseEvent *event){
    if(this->chessType == 1)
        this->setStyleSheet("image:url("+chessImageFileNames[0]+")");
    else if(this->chessType == 2)
        this->setStyleSheet("image:url("+chessImageFileNames[2]+")");
    else if(this->chessType == -1)
        this->setStyleSheet("image:url("+chessImageFileNames[4]+")");
    else if(this->chessType == -2)
        this->setStyleSheet("image:url("+chessImageFileNames[6]+")");
    else{
        this->setStyleSheet("image:url("+chessImageFileNames[9]+")");
    }

    //记录点击的棋位
    if(!clickedPositionList.contains(this->getPosition())){//如果该棋位没被点击过，则把其加入到全局变量：clickedPositionListListList中
         clickedPositionList << this->getPosition();
    }

    //事件传递：传递给该ChessLabel的父控件
    event->ignore();

}




