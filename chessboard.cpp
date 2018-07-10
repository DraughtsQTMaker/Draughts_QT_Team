#include "Chessboard.h"
#include <QDebug>

extern QHash<QByteArray, QPair<double, int> > blackHashTable;

//构造函数
Chessboard::Chessboard(QWidget *parent,int chessboardType,int layerNumberOfSearch) :
    QLabel(parent)
{
    this->chessboardType = chessboardType;
    this->layerNumber = layerNumberOfSearch;

    //初始化chessLabelList
    this->initializeChessLabelList();

    //创建布局管理器，并根据棋盘类型把棋子添加到相应位置上
    this->mainLayout = new QGridLayout(this);
    this->mainLayout->setSpacing(1);
    for(int n =0; n<chessLabelList.size();n++){
      int row = n / chessboardType;
      int col = n % chessboardType;
      this->mainLayout->addWidget(chessLabelList[n], row,col);
    }


    this->robotFirstButton = new QPushButton(this);
    this->robotFirstButton->resize(40,20);
    this->robotFirstButton->setText("Robot First");

    this->manFirstButton = new QPushButton(this);
    this->manFirstButton->resize(40,20);
    this->manFirstButton->setText("Man First");

    this->beginConsecutiveEatingButton = new QPushButton(this);
    this->beginConsecutiveEatingButton->resize(40,20);
    this->beginConsecutiveEatingButton->setText("Begin Consecutive Eating");

    this->repealConsecutiveEatingButton = new QPushButton(this);
    this->repealConsecutiveEatingButton->resize(40,20);
    this->repealConsecutiveEatingButton->setText("Repeal Consecutive Eating");


    mainLayout->addWidget(this->robotFirstButton, this->chessboardType,0,1,this->chessboardType/2);
    mainLayout->addWidget(this->manFirstButton, this->chessboardType,this->chessboardType/2,1,this->chessboardType/2);

    mainLayout->addWidget(this->beginConsecutiveEatingButton,this->chessboardType+1,0,1,this->chessboardType/2);
    mainLayout->addWidget(this->repealConsecutiveEatingButton,this->chessboardType+1,this->chessboardType/2,1,this->chessboardType/2);

    connect(this->robotFirstButton, SIGNAL(clicked()), this, SLOT(robotAction()));
    connect(this->manFirstButton, SIGNAL(clicked()), this,SLOT(manAction()));

    connect(this->beginConsecutiveEatingButton,SIGNAL(clicked()), this, SLOT(beginConsecutiveEating()));
    connect(this->repealConsecutiveEatingButton, SIGNAL(clicked()), this, SLOT(repealConsecutiveEating()));

    this->pathLabel = new QLabel();
    this->pathLabel->setStyleSheet("background-color:rgb(255,248,220)");
    mainLayout->addWidget(this->pathLabel, this->chessboardType+2,0,1,this->chessboardType);

}


//初始化chessLabelList
void Chessboard::initializeChessLabelList(){
    this->chessLabelList.clear();
    QString blackPieceImage = chessImageFileNames[0];
    QString redPieceImage = chessImageFileNames[4];


    //根据this->chessboardType来生成合理的chessLabelList
    if(this->chessboardType == 10){
        int k =0;

        //这个for循环用来生成50个Label，并在给定的Label上画出棋子，形成初始棋盘状态
        for(int i =0;i<=9;i++){
            for(int j=0; j<=9; j++){

                this->chessLabelList << new ChessLabel(this);
                //labelArray[k]->setText(i+","+j);
                int tempInt = i * this->chessboardType / 2 + j /2 + 1;
                QString tempRow = QString::number(i);
                QString tempCol = QString::number(j);
                QString tempString = tempRow + "," + tempCol;
                //通过HTML语言来设置Label上字体的颜色
                tempString = "<font color=blue>" + tempString +"</font>";
                ChessLabel * currentLabel = this->chessLabelList[k++];
                currentLabel->setText(tempString);
                currentLabel->setMargin(0);
                currentLabel->setFont(QFont("Timers" , 7 ,  QFont::Bold));

                //
                currentLabel->setAlignment(Qt::AlignBottom);


                currentLabel->setPosition(i,j);

                //Change Background Color
                if(i % 2 ==0){
                    if(j % 2 ==0){
                        //light
                        currentLabel->setStyleSheet("background-color:rgb(255,248,220)");
                        currentLabel->setText("");
                        currentLabel->setDormant();
                        currentLabel->setDisabled(true);


                    }else{
                        //dark
                         if(i<4){
                            //currentLabel->setStyleSheet("image:url("+blackPieceImage+")");
                            currentLabel->setChessType(1);
                         }else if(i>5){
                            //currentLabel->setStyleSheet("image:url("+redPieceImage+")");
                            currentLabel->setChessType(-1);
                         }else{

                         }


                    }

                }else{
                    if(j % 2 !=0){
                        //light
                        currentLabel->setStyleSheet("background-color:rgb(255,248,220)");
                        currentLabel->setText("");
                        currentLabel->setDormant();
                        currentLabel->setDisabled(true);
                    }else{
                        //dark
                        if(i<4){
                           //currentLabel->setStyleSheet("image:url("+blackPieceImage+")");
                           currentLabel->setChessType(1);
                        }else if(i>5){
                           //currentLabel->setStyleSheet("image:url("+redPieceImage+")");
                           currentLabel->setChessType(-1);
                        }else{

                        }
                    }

                }

            }
        }

    //如果是8*8棋盘
    }else if(this->chessboardType == 8){

        int k =0;

        //这个for循环用来生成64个Label，并在给定的Label上画出棋子，形成初始棋盘状态
        for(int i =0;i<=7;i++){
            for(int j=0; j<=7; j++){

                this->chessLabelList << new ChessLabel(this);
                //labelArray[k]->setText(i+","+j);
                QString tempRow = QString::number(i);
                QString tempCol = QString::number(j);
                QString tempString = tempRow + "," + tempCol;
                //通过HTML语言来设置Label上字体的颜色
                tempString = "<font color=blue>" + tempString +"</font>";
                ChessLabel * currentLabel = this->chessLabelList[k++];
//                qDebug()<<k;
                currentLabel->setText(tempString);
                currentLabel->setMargin(0);
                currentLabel->setFont(QFont("Timers" , 7 ,  QFont::Bold));

                //设置对其方式
                currentLabel->setAlignment(Qt::AlignBottom);

                //设置该棋子标签的位置
                currentLabel->setPosition(i,j);

                //Change Background Color
                if(i % 2 ==0){//偶数行时
                    if(j % 2 ==0){//偶数列不是合法棋位
                        //light
                        currentLabel->setStyleSheet("background-color:rgb(255,248,220)");
                        currentLabel->setText("");
                        currentLabel->setDormant();
                        currentLabel->setDisabled(true);


                    }else{
                        //dark
                         if(i<3){
                            //currentLabel->setStyleSheet("image:url("+blackPieceImage+")");
                            currentLabel->setChessType(1);
                         }else if(i>4){
                            //currentLabel->setStyleSheet("image:url("+redPieceImage+")");
                            currentLabel->setChessType(-1);
                         }else{

                         }


                    }

                }else{//奇数行时，
                    if(j % 2 !=0){//奇数列为不合法棋位，把其disabled掉
                        //light
                        currentLabel->setStyleSheet("background-color:rgb(255,248,220)");
                        currentLabel->setText("");
                        currentLabel->setDormant();
                        currentLabel->setDisabled(true);
                    }else{
                        //dark
                        if(i<3){
                           //currentLabel->setStyleSheet("image:url("+blackPieceImage+")");
                           currentLabel->setChessType(1);
                        }else if(i>4){
                           //currentLabel->setStyleSheet("image:url("+redPieceImage+")");
                           currentLabel->setChessType(-1);
                        }else{

                        }
                    }

                }

            }
        }


    }
}

QList<QPair<int,int> > Chessboard::createFourConnerPosition(QPair<int,int> chessPosition){
    QList<QPair<int,int> > targetPositionList;

    int row = chessPosition.first;
    int col = chessPosition.second;
    //生成4个角的位置
    QPair<int,int> tempPosition;
    //左上角
    tempPosition.first = row-1;
    tempPosition.second = col-1;
    if(this->positionIsLegal(tempPosition))//生成的位置合法的话
        targetPositionList << tempPosition;

    //右上角
    tempPosition.first = row-1;
    tempPosition.second = col+1;
    if(this->positionIsLegal(tempPosition))//生成的位置合法的话
        targetPositionList << tempPosition;

    //左下角
    tempPosition.first = row+1;
    tempPosition.second = col-1;
    if(this->positionIsLegal(tempPosition))//生成的位置合法的话
        targetPositionList << tempPosition;

    //右下角
    tempPosition.first = row+1;
    tempPosition.second = col+1;
    if(this->positionIsLegal(tempPosition))//生成的位置合法的话
        targetPositionList << tempPosition;


    return targetPositionList;

}



//创建四个角方向的单位向量
QList<QPair<int,int> > Chessboard::createFourUnitVectorForConner(){
    QList<QPair<int,int> > fourUnitVector;

    QPair<int,int> tempPair;
    tempPair.first = 1;
    tempPair.second = 1;
    fourUnitVector << tempPair;

    tempPair.first = 1; tempPair.second = -1;
    fourUnitVector << tempPair;

    tempPair.first = -1; tempPair.second = -1;
    fourUnitVector << tempPair;


    tempPair.first = -1; tempPair.second = 1;
    fourUnitVector << tempPair;

    return fourUnitVector;
}


//判断当前落子位置是否超过棋盘边界
bool Chessboard::positionIsLegal(QPair<int, int> chessPosition){
    bool legal = true;
    if(this->chessboardType == 10){//10*10棋盘的越界检查
        if(chessPosition.first >9 || chessPosition.first <0)
            legal = false;

        if(chessPosition.second >9 || chessPosition.second <0)
            legal = false;

    }else if(this->chessboardType == 8){//8*8棋盘的越界检查
        if(chessPosition.first >7 || chessPosition.first <0)
            legal = false;

        if(chessPosition.second >7 || chessPosition.second <0)
            legal = false;

    }


    return legal;
}



//设置所有chessLabel不可点击
void Chessboard::setAllChessLabelDisabled(){
    for(ChessLabel * currentChessLabel: this->chessLabelList)
        currentChessLabel->setDisabled(true);
}

//设置所有空棋位可以点击
void Chessboard::setAllEmptyPositionEnabled(){
    for(ChessLabel *currentLabel : this->chessLabelList)
        if(currentLabel->getChessType() == 0)
            currentLabel->setDisabled(false);
}


//刷新棋盘
void Chessboard::refreshChessBoard(){
    //遍历chessLabelList中的每一个标签
    for(ChessLabel *currentChessLabel:this->chessLabelList){
        //只处理非Dormant的ChessLabel, Dormant的ChessLabel是不合法棋位
        if(!currentChessLabel->isDormant()){



           //设置chessLabel上要显示的棋子图片
           if(currentChessLabel->getChessType() == 1){
               currentChessLabel->setStyleSheet("image:url("+chessImageFileNames[0]+")");
           }else if(currentChessLabel->getChessType() == 2){
               currentChessLabel->setStyleSheet("image:url("+chessImageFileNames[2]+")");
           }else if(currentChessLabel->getChessType() == -1){
               currentChessLabel->setStyleSheet("image:url("+chessImageFileNames[4]+")");
           }else if(currentChessLabel->getChessType() == -2){
               currentChessLabel->setStyleSheet("image:url("+chessImageFileNames[6]+")");
           }else{
               currentChessLabel->setStyleSheet("image:url("+chessImageFileNames[9]+")");
               currentChessLabel->setDisabled(false);//空棋位肯定可以点击
           }

           //设置哪方棋子不可以点击：根据全局变量 redGuiPieceAvailable的值
           if(!redGuiPieceAvailable){
                if(currentChessLabel->getChessType() == -1 || currentChessLabel->getChessType() == -2)
                    currentChessLabel->setDisabled(true);
            }else{//红方棋子可点击，那就意味着黑方棋子不可点击
                if(currentChessLabel->getChessType() == 1 || currentChessLabel->getChessType() == 2)
                    currentChessLabel->setDisabled(true);
            }




        }else{//不合法棋位都是不可以点击的
            currentChessLabel->setDisabled(true);
        }


       //重新布局这些chessLabel
       this->mainLayout->addWidget(currentChessLabel,currentChessLabel->getPosition().first,currentChessLabel->getPosition().second);

    }
    //重新显示chessboard
    this->show();

}



//当给定一个棋子后，搜索当前棋盘上该棋子下一步可以走的合法棋位（这个函数要基于西洋跳棋的走法规则来写）（这并不存在连吃情况的判断，只包含一步跳吃、单步移动）
//如果一步跳吃的位置存在，那么单步移动的情况就可以不考虑了
void Chessboard::searchAvaliablePositionToMove(int chessType, QPair<int,int> chessPosition){



    //首先找到所有的空棋位,并把所有的空棋位设定为Disabled

    for(ChessLabel *currentChessLabel : this->chessLabelList)
        if(currentChessLabel->getChessType() == 0)
            currentChessLabel->setDisabled(true);




    if(chessType == 1){//如果当前走棋的是黑方普通子
       //黑方在上，其规则是：如果黑方四周有红子，并且可以吃掉该红子，则一定要往可以吃掉的方向走，那么其他空棋位就是Disabled。否则黑普通子只能往下方走
       //所以，1）我们先检查该黑子临近的四周是否有红子。
              /*如果有，则把这些红子位置给记录下来*/
                /*检查每个红子，黑子->红子方向上的下一个紧邻位置是否为空棋位，如果为空棋位，则设定该空棋位为not Disabled*/
              /*如果临近四周没有红子，则只需判断该黑子左右下方临近是否为空棋位，如果是把其设定为not Disabled*/



       QList<QPair<int,int> > targetPositionList = this->createFourConnerPosition(chessPosition);



       //判断各个位置是否为红子
       for(QPair<int,int> currentPosition : targetPositionList){
           int n = this->chessboardType * currentPosition.first + currentPosition.second;
           QPair<int,int> tempPosition;
           //如果该位置是红子
           if(this->chessLabelList[n]->getChessType() == -1 || this->chessLabelList[n]->getChessType() == -2){
               //形成黑子->红子方向上的下一个位置(取直线中点算法的逆运用）
               tempPosition.first = 2*currentPosition.first - chessPosition.first;
               //如果该新位置的行标合法，则生成列标
               if(tempPosition.first >=0 && tempPosition.first<=this->chessboardType-1){
                   tempPosition.second = 2*currentPosition.second - chessPosition.second;
                   //如果列标也合法，即该新位置合法，则在该位置为空棋位的情况下，把其设置为激活状态
                   if(tempPosition.second >=0 && tempPosition.second <=this->chessboardType-1){
                      int k = this->chessboardType * tempPosition.first + tempPosition.second;
                      if(this->chessLabelList[k]->getChessType() == 0){
                        //这证明已经找到了可以跳吃的位置了，把该位置记录下来
                        this->chessLabelList[k]->setDisabled(false);
                        this->chessLabelList[k]->setStyleSheet("image:url("+chessImageFileNames[10]+")");
                      }
                   }
               }
           }

           //如果该位置是空棋位，则只有下方的空棋位是激活的
           if(this->chessLabelList[n]->getChessType() == 0){
               if(currentPosition.first > chessPosition.first){
                int k = currentPosition.first *(this->chessboardType) + currentPosition.second;
                this->chessLabelList[k]->setDisabled(false);
                this->chessLabelList[k]->setStyleSheet("image:url("+chessImageFileNames[10]+")");
               }
           }

       }





    }else if(chessType == 2){ //如果当前走棋的是黑方王子
        QList<QPair<int,int> > fourUnitVector = this->createFourUnitVectorForConner();

        for(QPair<int,int> currentUnitVector : fourUnitVector){
            QList<QPair<int,int> > tempPositionList; //当前棋子某个对角线方向上的所有棋位
            QPair<int,int> tempPosition = chessPosition;
            tempPosition.first +=  currentUnitVector.first;
            tempPosition.second +=  currentUnitVector.second;

            //把合法的位置记录下来
            while(this->positionIsLegal(tempPosition)){

                tempPositionList << tempPosition;

                tempPosition.first +=  currentUnitVector.first;
                tempPosition.second += currentUnitVector.second;
            }
            if(tempPositionList.size()==0)
                continue;



            //首先从tempPositionList中找到含有当前方的第一个棋子在tempPositionList中的位置
            int theFirstPositionOfOur = -1;
            for(QPair<int,int> currentPosition : tempPositionList){
                int k = (this->chessboardType) * currentPosition.first + currentPosition.second;
                int type = this->chessLabelList[k]->getChessType();

                if(type == 2 || type == 1){//找到我方第一个棋子
                    theFirstPositionOfOur = tempPositionList.indexOf(currentPosition,0);
                    break;
                }
            }

            //如果theFirstPositionOfOur 为-1,证明该方向上没有我方棋子；否则，截取tempPositionList的子List
            QList<QPair<int,int> > newTempPositionList;
            if(theFirstPositionOfOur != -1)
                for(int i = 0; i<theFirstPositionOfOur; i++)
                    newTempPositionList << tempPositionList[i];
            else
                newTempPositionList = tempPositionList;



            //目前newTempPositionList中只含有空棋位、对方棋子
            //在里面找到第一个对方棋子位置
            int theFirstPositionOfOpponent = -1;
            for(QPair<int,int> currentPosition : newTempPositionList){
                int k = (this->chessboardType) * currentPosition.first + currentPosition.second;
                int type = this->chessLabelList[k]->getChessType();

                if(type == -1 || type == -2){//找到对方第一个棋子
                    theFirstPositionOfOpponent = newTempPositionList.indexOf(currentPosition,0);
                    break;
                }
            }

            //如果找到了对方第一个棋子,则寻找对方第二个棋子；否则，该当前list中的孔位置都是可点击的
            if(theFirstPositionOfOpponent >=0){
                //当前点击的棋子与对方第一个棋子之间的空棋位都是可以点击的
                for(int i = 0 ; i<theFirstPositionOfOpponent; i++){
                    QPair<int,int> currentPosition = newTempPositionList[i];
                    int k = this->chessboardType * currentPosition.first + currentPosition.second;
                    this->chessLabelList[k]->setDisabled(false);
                    this->chessLabelList[k]->setStyleSheet("image:url("+chessImageFileNames[10]+")");
                }

                int theSecondPositionOfOpponent = -1;
                int i = theFirstPositionOfOpponent+1;
                while( i<newTempPositionList.size()){
                    QPair<int,int> currentPosition = newTempPositionList[i];
                    int k = this->chessboardType * currentPosition.first+currentPosition.second;
                    int type = this->chessLabelList[k]->getChessType();

                    if(type == -1 || type == -2){//找到对方第二个棋子
                        theSecondPositionOfOpponent = i;
                        break;
                    }
                    i++;
                }

                //如果没有找到第二个对方棋子,则从第一个对方棋子位置下一个位置，到结尾的所有空棋位都是可点击的
                if(theSecondPositionOfOpponent == -1){
                    int j = theFirstPositionOfOpponent +1;
                    while(j<newTempPositionList.size()){
                        QPair<int,int> currentPosition = newTempPositionList[j];
                        int k = this->chessboardType * currentPosition.first + currentPosition.second;
                        this->chessLabelList[k]->setDisabled(false);
                        this->chessLabelList[k]->setStyleSheet("image:url("+chessImageFileNames[10]+")");
                        j++;
                    }
                }else{//否则，第一个与第二个之间的空棋位可点击
                    int j = theFirstPositionOfOpponent +1;
                    while(j<theSecondPositionOfOpponent){
                        QPair<int,int> currentPosition = newTempPositionList[j];
                        int k = currentPosition.first * (this->chessboardType)+currentPosition.second;
                        this->chessLabelList[k]->setDisabled(false);
                        this->chessLabelList[k]->setStyleSheet("image:url("+chessImageFileNames[10]+")");
                        j++;
                    }
                }

            }else{

                for(QPair<int,int> currentPosition : newTempPositionList){
                    int k = currentPosition.first*(this->chessboardType)+currentPosition.second;
                    this->chessLabelList[k]->setDisabled(false);
                    this->chessLabelList[k]->setStyleSheet("image:url("+chessImageFileNames[10]+")");
                }
            }

        }//End 最外层For循环


    }else if(chessType == -1){//如果当前走棋的是红方普通子

        QList<QPair<int,int> > targetPositionList = this->createFourConnerPosition(chessPosition);

        //判断各个位置是否为黑子
        for(QPair<int,int> currentPosition : targetPositionList){
//            //qDebug()<<"xxxxxxxx";
            int n = currentPosition.first *(this->chessboardType) + currentPosition.second;
//            //qDebug()<<n;
            QPair<int,int> tempPosition;
            //如果该位置是黑子
            if(this->chessLabelList[n]->getChessType() == 1 || this->chessLabelList[n]->getChessType() == 2){
                //形成红子->黑子方向上的下一个位置(取直线中点算法的逆运用）
                tempPosition.first = 2*currentPosition.first - chessPosition.first;
                //如果该新位置的行标合法，则生成列标
                if(tempPosition.first >=0 && tempPosition.first <= (this->chessboardType-1)){
                    tempPosition.second = 2*currentPosition.second - chessPosition.second;
                    //如果列标也合法，即该新位置合法，则在该位置为空棋位的情况下，把其设置为激活状态
                    if(tempPosition.second >=0 && tempPosition.second <= (this->chessboardType-1)){
                       int k = tempPosition.first *(this->chessboardType) + tempPosition.second;
                       if(this->chessLabelList[k]->getChessType() == 0){
                           this->chessLabelList[k]->setDisabled(false);
                           this->chessLabelList[k]->setStyleSheet("image:url("+chessImageFileNames[10]+")");
                       }

                    }
                }
            }
            //如果该位置是空棋位，则只有上方的空棋位是激活的
            if(this->chessLabelList[n]->getChessType() == 0){
                if(currentPosition.first < chessPosition.first){
                 int k = currentPosition.first *(this->chessboardType) + currentPosition.second;
                 this->chessLabelList[k]->setDisabled(false);
                 this->chessLabelList[k]->setStyleSheet("image:url("+chessImageFileNames[10]+")");
                }
            }

        }

    }else if(chessType == -2){//如果当前走棋的是红方王子
        QList<QPair<int,int> > fourUnitVector = this->createFourUnitVectorForConner();

        for(QPair<int,int> currentUnitVector : fourUnitVector){
            QList<QPair<int,int> > tempPositionList; //当前棋子某个对角线方向上的所有棋位
            QPair<int,int> tempPosition = chessPosition;
            tempPosition.first +=  currentUnitVector.first;
            tempPosition.second +=  currentUnitVector.second;

            //把合法的位置记录下来
            while(this->positionIsLegal(tempPosition)){

                tempPositionList << tempPosition;
                //qDebug() <<tempPosition.first <<"\t"<<tempPosition.second;
                tempPosition.first +=  currentUnitVector.first;
                tempPosition.second += currentUnitVector.second;
            }

            if(tempPositionList.size()==0)//如果当前方向上没有搜索到合适的位置，则搜索下一个对角线
                continue;

            //首先从tempPositionList中找到含有当前方的第一个棋子在tempPositionList中的位置
            int theFirstPositionOfOur = -1;
            for(QPair<int,int> currentPosition : tempPositionList){
                int k = currentPosition.first*(this->chessboardType)+currentPosition.second;
                int type = this->chessLabelList[k]->getChessType();

                if(type == -2 || type == -1){//找到我方第一个棋子
                    theFirstPositionOfOur = tempPositionList.indexOf(currentPosition,0);
                    break;
                }
            }

            //如果theFirstPositionOfOur 为-1,证明该方向上没有我方棋子；否则，截取tempPositionList的子List
            QList<QPair<int,int> > newTempPositionList;
            if(theFirstPositionOfOur != -1)
                for(int i = 0; i<theFirstPositionOfOur; i++)
                    newTempPositionList << tempPositionList[i];
            else
                newTempPositionList = tempPositionList;


            //目前newTempPositionList中只含有空棋位、对方棋子
            //在里面找到第一个对方棋子位置
            int theFirstPositionOfOpponent = -1;
            for(QPair<int,int> currentPosition : newTempPositionList){
                int k = currentPosition.first*(this->chessboardType)+currentPosition.second;
                int type = this->chessLabelList[k]->getChessType();

                if(type == 1 || type == 2){//找到对方第一个棋子
                    theFirstPositionOfOpponent = newTempPositionList.indexOf(currentPosition,0);
                    break;
                }
            }

            //如果找到了对方第一个棋子,则寻找对方第二个棋子；否则，该当前list中的孔位置都是可点击的
            if(theFirstPositionOfOpponent >=0){
                //当前点击的棋子与对方第一个棋子之间的空棋位都是可以点击的
                for(int i = 0 ; i<theFirstPositionOfOpponent; i++){
                    QPair<int,int> currentPosition = newTempPositionList[i];
                    int k = currentPosition.first*(this->chessboardType)+currentPosition.second;
                    this->chessLabelList[k]->setDisabled(false);
                    this->chessLabelList[k]->setStyleSheet("image:url("+chessImageFileNames[10]+")");
                }



                int theSecondPositionOfOpponent = -1;
                int i = theFirstPositionOfOpponent+1;
                while( i<newTempPositionList.size()){
                    QPair<int,int> currentPosition = newTempPositionList[i];
                    int k = currentPosition.first*(this->chessboardType)+currentPosition.second;
                    int type = this->chessLabelList[k]->getChessType();

                    if(type == 1 || type == 2){//找到对方第二个棋子
                        theSecondPositionOfOpponent = i;
                        break;
                    }
                    i++;
                }

                //如果没有找到第二个对方棋子,则从第一个对方棋子位置下一个位置，到结尾的所有空棋位都是可点击的
                if(theSecondPositionOfOpponent == -1){
                    int j = theFirstPositionOfOpponent +1;
                    while(j<newTempPositionList.size()){
                        QPair<int,int> currentPosition = newTempPositionList[j];
                        int k = currentPosition.first*(this->chessboardType)+currentPosition.second;
                        this->chessLabelList[k]->setDisabled(false);
                        this->chessLabelList[k]->setStyleSheet("image:url("+chessImageFileNames[10]+")");
                        j++;
                    }
                }else{//否则，第一个与第二个之间的空棋位可点击
                    int j = theFirstPositionOfOpponent +1;
                    while(j<theSecondPositionOfOpponent){
                        QPair<int,int> currentPosition = newTempPositionList[j];
                        int k = currentPosition.first*(this->chessboardType)+currentPosition.second;
                        this->chessLabelList[k]->setDisabled(false);
                        this->chessLabelList[k]->setStyleSheet("image:url("+chessImageFileNames[10]+")");
                        j++;
                    }
                }

            }else{

                for(QPair<int,int> currentPosition : newTempPositionList){
                    int k = currentPosition.first*(this->chessboardType)+currentPosition.second;
                    this->chessLabelList[k]->setDisabled(false);
                    this->chessLabelList[k]->setStyleSheet("image:url("+chessImageFileNames[10]+")");
                }
            }

        }//End 最外层For循环

    }//End Else-if


}//End of ChessBoard::searchAvaliablePositionToMove(int chessType, QPair<int,int> chessPosition)

//显示当前可以落子的位置
void Chessboard::showPossiblePositionCanMoveTo(){
    for(ChessLabel *currentLabel:this->chessLabelList)
       this->mainLayout->addWidget(currentLabel,currentLabel->getPosition().first,currentLabel->getPosition().second);

    this->show();
}




//普通子是否可以吃子
bool Chessboard::canNormalPieceEatOpponent(int chessType, QPair<int,int> chessPosition){
    bool canEat = false;
    QList<QPair<int,int> > targetPositionList = this->createFourConnerPosition(chessPosition);


    if(chessType == 1){
        //判断四个角各个位置是否为红子
        for(QPair<int,int> currentPosition : targetPositionList){
           int n = currentPosition.first *(this->chessboardType) + currentPosition.second;
           QPair<int,int> tempPosition;
           //如果该位置是红子
           if(this->chessLabelList[n]->getChessType() == -1 || this->chessLabelList[n]->getChessType() == -2){
               //形成黑子->红子方向上的下一个位置(取直线中点算法的逆运用）
               tempPosition.first = 2*currentPosition.first - chessPosition.first;
               //如果该新位置的行标合法，则生成列标
               if(tempPosition.first >=0 && tempPosition.first<=this->chessboardType-1){
                   tempPosition.second = 2*currentPosition.second - chessPosition.second;
                   //如果列标也合法，即该新位置合法，则在该位置为空棋位的情况下，把其设置为激活状态
                   if(tempPosition.second >=0 && tempPosition.second <=this->chessboardType-1){
                      int k = tempPosition.first *(this->chessboardType) + tempPosition.second;
                      if(this->chessLabelList[k]->getChessType() == 0){
                        //证明找到了可以吃子的地方
                          canEat = true;
                          break;
                      }
                   }
               }
           }

        }


    }else if(chessType == -1){//如果当前走棋的是红方普通子



        //判断各个位置是否为黑子
        for(QPair<int,int> currentPosition : targetPositionList){
            int n = currentPosition.first *(this->chessboardType) + currentPosition.second;
            QPair<int,int> tempPosition;
            //如果该位置是黑子
            if(this->chessLabelList[n]->getChessType() == 1 || this->chessLabelList[n]->getChessType() == 2){
                //形成红子->黑子方向上的下一个位置(取直线中点算法的逆运用）
                tempPosition.first = 2*currentPosition.first - chessPosition.first;
                //如果该新位置的行标合法，则生成列标
                if(tempPosition.first >=0 && tempPosition.first<=this->chessboardType-1){
                    tempPosition.second = 2*currentPosition.second - chessPosition.second;
                    //如果列标也合法，即该新位置合法，则在该位置为空棋位的情况下，把其设置为激活状态
                    if(tempPosition.second >=0 && tempPosition.second <=this->chessboardType-1){
                       int k = tempPosition.first *(this->chessboardType) + tempPosition.second;
                       if(this->chessLabelList[k]->getChessType() == 0){
                          canEat = true;
                          break;
                       }

                    }
                }
            }

        }

    }

    return canEat;

}



void Chessboard::getCurrentChessStatusFromChessLabelList(){

    int walkToBottomCounter = 0;    //即：黑子计数器
    int walkToTopCounter = 0;   //即：红子计数器
    bool chessColorIsBlack = true;
    bool isKing = true;
    bool existed = true;    //如果chessLabel类型非0，那么该棋子肯定是存在的
    int rowNumber = 0;
    int colNumber = 0;


    if(this->chessboardType == 10){//10*10棋盘，一方有20个棋子
        this->chessStatus.nCountRed = 20;
        this->chessStatus.nCountBlack = 20;
    }else if(this->chessboardType == 8){//8*8棋盘，一方有12个棋子
        this->chessStatus.nCountRed = 12;
        this->chessStatus.nCountBlack = 12;
    }


    for(ChessLabel* currentLabel : this->chessLabelList){
       //判断当前ChessLabel是否休眠
       if(!currentLabel->isDormant()){

           //获得当前Label代表的棋子信息
           if(currentLabel->getChessType() == 1){//当为黑色棋子时，对应后台的上部棋子（即也是：后台的黑子）

               rowNumber = currentLabel->getPosition().first;
               colNumber = currentLabel->getPosition().second;

               SingleChessPiece currentChessPiece(rowNumber,colNumber,!isKing,chessColorIsBlack,existed);
               this->chessStatus.blackPieceList[walkToBottomCounter++] = currentChessPiece;



           }else if(currentLabel->getChessType() == 2){
//               existed = true;
//               isKing = true;
               rowNumber = currentLabel->getPosition().first;
               colNumber = currentLabel->getPosition().second;

               SingleChessPiece currentChessPiece(rowNumber,colNumber,isKing,chessColorIsBlack,existed);
               this->chessStatus.blackPieceList[walkToBottomCounter++] = currentChessPiece;

           }else if(currentLabel->getChessType() == -1){
//               existed = true;
//               isKing = false;
               rowNumber = currentLabel->getPosition().first;
               colNumber = currentLabel->getPosition().second;

               SingleChessPiece currentChessPiece(rowNumber,colNumber,!isKing,!chessColorIsBlack,existed);
               this->chessStatus.redPieceList[walkToTopCounter++] = currentChessPiece;
           }else if(currentLabel->getChessType() == -2){
//               existed = true;
//               isKing = true;
               rowNumber = currentLabel->getPosition().first;
               colNumber = currentLabel->getPosition().second;

               SingleChessPiece currentChessPiece(rowNumber,colNumber,isKing,!chessColorIsBlack,existed);
               this->chessStatus.redPieceList[walkToTopCounter++] = currentChessPiece;
           }else{

          }


       }
    }


    //把CheckerState中的List中空置的单元填充上
    if(walkToBottomCounter <= 19){
        for(int i = walkToBottomCounter; i<20;i++){

            existed = false;
            isKing = false;
            rowNumber = 0;
            colNumber = 0;
            SingleChessPiece currentChessPiece(rowNumber,colNumber,isKing,chessColorIsBlack,existed);
            this->chessStatus.blackPieceList[i] = currentChessPiece;
        }
    }

    if(walkToTopCounter <= 19){
        for(int i = walkToTopCounter; i<20;i++){
//            chessColor = true;
            existed = false;
            isKing = false;
            rowNumber = 0;
            colNumber = 0;
            SingleChessPiece currentChessPiece(rowNumber,colNumber,isKing,!chessColorIsBlack,existed);
            this->chessStatus.redPieceList[i] = currentChessPiece;
        }
    }
    for(int i = 0;i < walkToTopCounter / 2;++i){
        qSwap(chessStatus.redPieceList[i],chessStatus.redPieceList[19-i]);
    }


}


void Chessboard::updateChessLabelListFromChessStatus(){
    QList<QPair<int,int> > occupiedPosition;
    QPair<int,int> currentOccupiedPosition;
    //首先检查chessStatus中的blackPieceList
    for(SingleChessPiece currentPiece : this->chessStatus.blackPieceList){
        if(currentPiece.isExisted()){
            //获得当前棋子的颜色、类型、位置信息
            bool isKing = currentPiece.isKing();
            int rowNumber = currentPiece.getRow();
            int colNumber = currentPiece.getCol();

            //用来记录占用的位置
            currentOccupiedPosition.first = rowNumber;
            currentOccupiedPosition.second = colNumber;
            occupiedPosition << currentOccupiedPosition;

            if(isKing){
                this->chessLabelList[rowNumber*(this->chessboardType)+colNumber]->setChessType(2);
            }else{
                this->chessLabelList[rowNumber*(this->chessboardType)+colNumber]->setChessType(1);
            }
        }
    }



    //其次检查chessStauts中的redPieceList
    for(SingleChessPiece currentPiece : this->chessStatus.redPieceList){
        if(currentPiece.isExisted()){
            //获得当前棋子的颜色、类型、位置信息
            bool isKing = currentPiece.isKing();
            int rowNumber = currentPiece.getRow();
            int colNumber = currentPiece.getCol();

            //用来记录占用的位置
            currentOccupiedPosition.first = rowNumber;
            currentOccupiedPosition.second = colNumber;
            occupiedPosition << currentOccupiedPosition;

            if(isKing){
                this->chessLabelList[rowNumber*(this->chessboardType)+colNumber]->setChessType(-2);
            }else{
                this->chessLabelList[rowNumber*(this->chessboardType)+colNumber]->setChessType(-1);
            }
        }
    }





    //最后，把棋盘所有没有被占据的位置找出来，并把他们的type设为0
    for(int row = 0; row< this->chessboardType; row++)
        for(int col = 0; col < this->chessboardType; col++){
            QPair<int,int> currentPosition;
            currentPosition.first = row;
            currentPosition.second = col;

            //如果该位置没有被占据的话
            if(!occupiedPosition.contains(currentPosition))
                this->chessLabelList[row*(this->chessboardType) + col]->setChessType(0);
        }


}





//Chessboard的鼠标事件
void Chessboard::mouseReleaseEvent(QMouseEvent *){
    //首先判断全局变量clickedPositionList表的长度
    int length = clickedPositionList.size();

    //寻找可以落子的棋位
    if(length == 1){//如果当前只点击了一个位置
        //获得点击的第一个位置的棋子类型，第一次点击的位置
        QPair<int,int> tempPosition = clickedPositionList[0];
        int tempType = this->chessLabelList[tempPosition.first *(this->chessboardType)+ tempPosition.second]->getChessType();


        //如果点击的位置并不是空棋位,则寻找当前点击棋子可以落子的位置，并把不符合规则的空棋位Disable掉
        if(tempType != 0 ){
            this->searchAvaliablePositionToMove(tempType,tempPosition);
            this->showPossiblePositionCanMoveTo();
        }else{  //当前点击的是空棋位，则不做任何处理
            //必须先点击棋子，再点击可落子位置，所以，如果第一次点击的是空棋位，则第一次点击失效，这时只需要把clickedPositionList清空即可
            clickedPositionList.clear();
        }

    }



    //实现移动棋子
    if(length>=2){//如果至少已经点击了两个不同的位置，则移动棋子，最后把该clickedPositionList清空

        if(this->chessLabelList[clickedPositionList[0].first *(this->chessboardType)+ clickedPositionList[0].second]->getChessType() == 0)//如果第一次点击的是空棋位
        {
        }else{
//            //获得点击的第一个位置的棋子类型，第一次点击的位置
//            int tempType = this->chessLabelList[clickedPositionList[0].first *(this->chessboardType)+ clickedPositionList[0].second]->getChessType();
//            QPair<int,int> tempPosition = clickedPositionList[0];


            //如果点击的第2个位置是空棋位，则修改棋盘，并刷新棋盘
            if(this->chessLabelList[clickedPositionList[1].first *(this->chessboardType) + clickedPositionList[1].second]->getChessType()== 0){
                int p =clickedPositionList[0].first *(this->chessboardType) + clickedPositionList[0].second;
                int theFirstType = this->chessLabelList[p]->getChessType();



                qDebug()<< "人起子位置：("<<clickedPositionList[0].first <<",\t" << clickedPositionList[0].second <<")";
                qDebug()<< "人落子位置：("<<clickedPositionList[1].first << ",\t" << clickedPositionList[1].second <<")";




                //吃子----------------------开始吃子--------------------------//
                //如果第一次点击的是非王子

                if( theFirstType % 2 != 0){

                        QPair<int,int> middlePosition;
                        middlePosition.first =  (clickedPositionList[0].first + clickedPositionList[1].first)/2;
                        middlePosition.second = (clickedPositionList[0].second + clickedPositionList[1].second)/2;
                        //修改middlePosition位置的Label为空

                        this->chessLabelList[middlePosition.first*(this->chessboardType) + middlePosition.second]->setChessType(0);


                }else{//如果第一次点击的是王子，则直接修改与王子落子临近的那个位置

                    QPair<int,int> beginPosition = clickedPositionList[0];
                    QPair<int,int> targetPosition = clickedPositionList[1];

                    QPair<int,int> unitVector;
                    unitVector.first = (targetPosition.first-beginPosition.first)/qAbs(targetPosition.first-beginPosition.first);
                    unitVector.second = (targetPosition.second-beginPosition.second)/qAbs(targetPosition.second-beginPosition.second);

                    //从终点到起点搜索，把路径上的棋子label置为空
                    unitVector.first *= (-1);
                    unitVector.second *=(-1);
                    QPair<int,int> tempPosition = targetPosition;

                    tempPosition.first += unitVector.first;
                    tempPosition.second += unitVector.second;

                    while(tempPosition != beginPosition){
                       if(this->chessLabelList[tempPosition.first*(this->chessboardType) + tempPosition.second]->getChessType() != 0){
                           this->chessLabelList[tempPosition.first*(this->chessboardType) + tempPosition.second]->setChessType(0);
                           break;//吃掉一个子后就结束吃子
                       }

                       tempPosition.first += unitVector.first;
                       tempPosition.second += unitVector.second;

                    }


                }//---------------------吃子结束----------------------------//


                //修改第一次点击的位置的棋位为空；设置第2个位置的棋子类型
                //
                this->chessLabelList[clickedPositionList[0].first *(this->chessboardType)+ clickedPositionList[0].second]->setChessType(0);
                //
                this->chessLabelList[clickedPositionList[1].first *(this->chessboardType)+ clickedPositionList[1].second]->setChessType(theFirstType);




                //----------------判断是否成王---------------//在连续跳吃的情况下，判断成王的标准是，一旦落到边界其不能再跳吃了
                if(theFirstType == 1){//黑方普通子
                    if(clickedPositionList[1].first == (this->chessboardType-1))
                        if(consecutiveEating == false)//如果单步走的情况下：落在了对方边界上，那么其成王
                            this->chessLabelList[clickedPositionList[1].first *(this->chessboardType)+ clickedPositionList[1].second]->setChessType(2);
                        else//如果在连续跳吃的情况下：其停留在了对方边界线上，并且在该位置并不可以继续吃对方子，那么其成王
                            if(!this->canNormalPieceEatOpponent(theFirstType,clickedPositionList[1]))
                                this->chessLabelList[clickedPositionList[1].first *(this->chessboardType)+ clickedPositionList[1].second]->setChessType(2);
                }else if(theFirstType == -1){
                    if(clickedPositionList[1].first == 0)
                        if(consecutiveEating == false)
                            this->chessLabelList[clickedPositionList[1].first *(this->chessboardType)+ clickedPositionList[1].second]->setChessType(-2);
                        else
                            if(!this->canNormalPieceEatOpponent(theFirstType,clickedPositionList[1]))
                                this->chessLabelList[clickedPositionList[1].first *(this->chessboardType)+ clickedPositionList[1].second]->setChessType(-2);
                }else{

                }//----------------判断是否成王结束------------------



                //移动完棋子之后，就可以把点击位置记录器清空了
                 clickedPositionList.clear();







                //Add Function:由于第一次点击棋子后，有一部分空棋位是Disabled，所以这里要把所有空棋位设置为enabled
                //这可以通过ChessBoard::中的setAllEmptyPositionBeEnabled()
                this->setAllEmptyPositionEnabled();
                //刷新棋盘
                this->refreshChessBoard();

                //------------------在机器方开始下之前，先判断当前手动下棋方是否取胜---------------//
                this->judge();

                //然后调用robot,来获得新的下棋结果
                if(consecutiveEating == false){//如果当前手动走棋方不具备连续跳吃条件

                   //qDebug() <<"The opponent begin to move...";
                   //qDebug()<<"Before Move, the previous chessStatus is:";
                   for(ChessLabel * currentChessLabel:this->chessLabelList){
                        if(currentChessLabel->getChessType() !=0){
                            //qDebug()<<currentChessLabel->getPosition().first <<"\t" << currentChessLabel->getPosition().second << "Type:" <<currentChessLabel->getChessType();
                        }
                   }

                   this->robotPlay();
                   this->refreshChessBoard();
                   //-------------------Robot下完棋后，再进行一次判断------------------------//
                   this->judge();
                }





            }else{//如果点击的第二个位置也是非空棋位，那么修改第一个点击位置作废，第二个位置当做第一个位置.并重新显示该最后点击棋子可以落子
                //的位置
                QPair<int,int> temp = clickedPositionList[1];
                int type = this->chessLabelList[temp.first*(this->chessboardType)+temp.second]->getChessType();
                clickedPositionList.clear();
                clickedPositionList << temp;

                this->searchAvaliablePositionToMove(type,temp);
                this->showPossiblePositionCanMoveTo();

            }
        }

    }

}





int Chessboard::robotPlay(){
    if(gameOver)
        return -1;
    qDebug() << "----------------------------Start";

    this->robot = new Checker_AlphaBetaSearch(this->layerNumber);

    this->getCurrentChessStatusFromChessLabelList();
//    //打印当前的chessStatus
//    for(SingleChessPiece currentChessPiece : this->chessStatus.blackPieceList){
//        if(currentChessPiece.isExisted())
//            //qDebug() << currentChessPiece.getRow() <<" " << currentChessPiece.getCol() << "\t" <<currentChessPiece.isBlack();
//    }

//    this->util->getCurrentChessStatus(this->chessLabelList,&chessStatus);

    RETURN_VALUE *searchResult = this->robot->alphaBetaPruning(this->chessStatus,blackTurn,this->chessboardType,this->chessboardType);
    Checker_AlphaBetaSearch::totalStep++;
    //机器走棋后获得最终的棋盘状态
    ChessStatus theNewChessStatus = searchResult->chessStatusList[searchResult->step - 1];
    //显示走子的初始以及终止位置
    if(blackTurn == true)
        this->showPathOfBlackPiece(this->chessStatus, theNewChessStatus);
    else
        this->showPathOfRedPiece(this->chessStatus, theNewChessStatus);

    this->chessStatus = theNewChessStatus;
    //把NewChessStatus解析成ChessLabelList,利用本类中中的refreshChessLabelList();
//    this->refreshChessLabelList(theNewChessStatus);
    this->updateChessLabelListFromChessStatus();

    delete this->robot;
    qDebug() << "---------------------------End";

    return 1;
}





void Chessboard::showPathOfRedPiece(ChessStatus oldChessStatus, ChessStatus newChessStatus){//有Bug,只能显示走子棋子的终止位置不同于初始位置的情况，待改进
    std::vector<std::pair<int, int> > oldPositionList;
    std::vector<std::pair<int, int> > newPositionList;


    for (SingleChessPiece tempBlackPiece : oldChessStatus.redPieceList){
        if (tempBlackPiece.isExisted()){
            int row = tempBlackPiece.getRow();
            int col = tempBlackPiece.getCol();
            oldPositionList.push_back(std::make_pair(row, col));
        }
    }


    for (SingleChessPiece tempBlackPiece : newChessStatus.redPieceList){
        if (tempBlackPiece.isExisted()){
            int row = tempBlackPiece.getRow();
            int col = tempBlackPiece.getCol();
            newPositionList.push_back(std::make_pair(row, col));
        }
    }


    //寻找两个list中的不同元素（结合棋盘特性，和ChessStatus的特性，只需要O（n)
    for (int i = 0; i < oldPositionList.size();i++){
        if (oldPositionList[i] != newPositionList[i]){
            QString beginPosition = "(" + QString::number(oldPositionList[i].first) + "," + QString::number(oldPositionList[i].second)  + ")";
            int legalBeginPosition = oldPositionList[i].first * this->chessboardType / 2 + oldPositionList[i].second /2 + 1;
            QString legalBeginPositionString = QString::number(legalBeginPosition);

            qDebug() << "Begin Position: (" << oldPositionList[i].first << " , " << oldPositionList[i].second << ")" << "  ----->  ";
            qDebug() << "Target Position: (" << newPositionList[i].first << " , " << newPositionList[i].second << ")" <<endl;

            QString targetPosition = "(" + QString::number(newPositionList[i].first) + "," + QString::number(newPositionList[i].second)  + ")";
            int legalTargetPosition = newPositionList[i].first * this->chessboardType / 2 + newPositionList[i].second /2 + 1;
            QString legalTargetPositionString = QString::number(legalTargetPosition);
            this->pathLabel->setText(beginPosition + "----->" + targetPosition + "\t\t" + legalBeginPositionString + "----->" + legalTargetPositionString);
        }
    }

    //显示在Label上



}



void Chessboard::showPathOfBlackPiece(ChessStatus oldChessStatus, ChessStatus newChessStatus){//有Bug,只能显示走子棋子的终止位置不同于初始位置的情况，待改进
    std::vector<std::pair<int, int> > oldPositionList;
    std::vector<std::pair<int, int> > newPositionList;


    for (SingleChessPiece tempBlackPiece : oldChessStatus.blackPieceList){
        if (tempBlackPiece.isExisted()){
            int row = tempBlackPiece.getRow();
            int col = tempBlackPiece.getCol();
            oldPositionList.push_back(std::make_pair(row, col));
        }
    }


    for (SingleChessPiece tempBlackPiece : newChessStatus.blackPieceList){
        if (tempBlackPiece.isExisted()){
            int row = tempBlackPiece.getRow();
            int col = tempBlackPiece.getCol();
            newPositionList.push_back(std::make_pair(row, col));
        }
    }


    //寻找两个list中的不同元素（结合棋盘特性，和ChessStatus的特性，只需要O（n)
    for (int i = 0; i < oldPositionList.size();i++){
        if (oldPositionList[i] != newPositionList[i]){
            QString beginPosition = "(" + QString::number(oldPositionList[i].first) + "," + QString::number(oldPositionList[i].second)  + ")";
            int legalBeginPosition = oldPositionList[i].first * this->chessboardType / 2 + oldPositionList[i].second /2 + 1;
            QString legalBeginPositionString = QString::number(legalBeginPosition);

            qDebug() << "Begin Position: (" << oldPositionList[i].first << " , " << oldPositionList[i].second << ")" << "  ----->  ";
            qDebug() << "Target Position: (" << newPositionList[i].first << " , " << newPositionList[i].second << ")" <<endl;

            QString targetPosition = "(" + QString::number(newPositionList[i].first) + "," + QString::number(newPositionList[i].second)  + ")";
            int legalTargetPosition = newPositionList[i].first * this->chessboardType / 2 + newPositionList[i].second /2 + 1;
            QString legalTargetPositionString = QString::number(legalTargetPosition);
            this->pathLabel->setText(beginPosition + "----->" + targetPosition + "\t\t" + legalBeginPositionString + "----->" + legalTargetPositionString);
        }
    }

}


//SLOTS
void Chessboard::robotAction(){

    gameOver = false;
    //当机器先下时，
    blackTurn = true;
    //当机器为黑棋时，不可点击的是黑色棋子，所以红子可点击
    redGuiPieceAvailable = true;

    //初始化一个棋盘上需要的Chess Label List
    this->initializeChessLabelList();
    //并显示该棋盘
    this->refreshChessBoard();

    //生成一个robot对象（此时，robot对象为黑棋）
    this->robot = new Checker_AlphaBetaSearch(this->layerNumber);

    //根据chessLabelList生成ChessStatus对象
    this->getCurrentChessStatusFromChessLabelList();
    Checker_AlphaBetaSearch::totalStep = 0;
    RETURN_VALUE *searchResult = this->robot->alphaBetaPruning(this->chessStatus,blackTurn,this->chessboardType,this->chessboardType);
    Checker_AlphaBetaSearch::totalStep++;
    //机器走棋后获得最终的棋盘状态
    ChessStatus theNewChessStatus =  searchResult->chessStatusList[searchResult->step - 1];

    //显示走子的初始以及终止位置
    this->showPathOfBlackPiece(this->chessStatus, theNewChessStatus);

    this->chessStatus = theNewChessStatus;


    //把NewChessStatus解析成ChessLabelList,利用本类中中的refreshChessLabelList();
    this->updateChessLabelListFromChessStatus();

    //根据下棋结果，刷新棋盘
    this->refreshChessBoard();

    delete this->robot;

    qDebug() << "ddddddddddddddddddddd ";

}

//SLOTS
void Chessboard::manAction(){

    gameOver = false;
    //当人先下棋时,此时机器方应该是红子，所以blackTurn为False。人先下，所以人为黑子，所以可以点击的是黑子，红子不可点击
    blackTurn = false;
    redGuiPieceAvailable = false;

    //初始化一个棋盘上需要的Chess Label List
	Checker_CheckerState::setEvaluateBlack(false);
    this->initializeChessLabelList();
    //并显示该棋盘
    this->refreshChessBoard();

}

//SLOTS
void Chessboard::beginConsecutiveEating(){
    consecutiveEating = true;
    this->beginConsecutiveEatingButton->setDisabled(true);
    this->repealConsecutiveEatingButton->setDisabled(false);
}

//SLOTS
void Chessboard::repealConsecutiveEating(){

    if(consecutiveEating == true){
        //一旦撤销了连续跳吃，那么就应该把控制权返回给Robot
        consecutiveEating = false;

        //------------------在机器方开始下之前，先判断当前手动下棋方是否取胜---------------//
        this->judge();

        this->robotPlay();

        this->refreshChessBoard();
        //-------------------Robot下完棋后，再进行一次判断------------------------//
        this->judge();

        this->beginConsecutiveEatingButton->setDisabled(false);
        this->repealConsecutiveEatingButton->setDisabled(true);
    }
}



//判断棋盘局面输赢
void Chessboard::judge(){
    //遍历chessLabelList，记录前端黑方、红方剩余棋子的个数
    int existedBlackUiPieceCounter = 0;
    int existedRedUiPieceCounter = 0;
    for(ChessLabel *currentChessLabel : this->chessLabelList){
        int chessType = currentChessLabel->getChessType();
        if(chessType == 1 || chessType == 2)
            existedBlackUiPieceCounter++;
        else if(chessType == -1 || chessType == -2)
            existedRedUiPieceCounter++;
    }

    if(existedBlackUiPieceCounter == 0){
       QMessageBox::about(this,tr("Find Winner!"),tr("Red Win!!!"));
       //设置所有chessLabel为Disabled
       this->setAllChessLabelDisabled();
       gameOver = true;
    }

    if(existedRedUiPieceCounter == 0){
        QMessageBox::about(this,tr("Find Winner!"),tr("Black Win!!!"));
        //设置所有chessLabel为Disabled
        this->setAllChessLabelDisabled();
        gameOver = true;
    }
}



















